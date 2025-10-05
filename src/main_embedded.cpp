#include "core.hpp"
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <iostream>

namespace py = pybind11;

// Expose a pure C++ module to the embedded Python so the Tkinter UI can call it.
PYBIND11_EMBEDDED_MODULE(hybrid_core, m) {
    m.def("build_pc", &build_pc, "Build configuration string",
          py::arg("engine"), py::arg("gearbox"), py::arg("main_motor"), py::arg("sub_motor"));
    m.def("main_motor_options", &main_motor_options, "Main motor options",
          py::arg("engine"), py::arg("gearbox"));
    m.def("sub_motor_options", &sub_motor_options, "Sub motor options",
          py::arg("engine"), py::arg("gearbox"), py::arg("main_motor"));
}

// The Tkinter UI script embedded as a raw Python string.
static const char* PY_UI = R"PY(
import sys
try:
    import tkinter as tk
    from tkinter import ttk, messagebox
except Exception as e:
    print("ERROR: Tkinter is not available in this Python installation:", e, file=sys.stderr)
    raise

import hybrid_core as core

ENGINE = ["FWD", "RWD", "AWD"]
GEARBOX = ["E-CVT", "DHT", "Automatic", "CVT", "DCT", "AMT", "MT"]

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Hybrid PC Editor (Tk)")
        self.geometry("820x600")

        # Controls frame
        frm = ttk.Frame(self, padding=10)
        frm.pack(side=tk.TOP, fill=tk.X)

        # Engine
        ttk.Label(frm, text="Engine:").grid(row=0, column=0, sticky="w", padx=(0,6))
        self.engine_cb = ttk.Combobox(frm, values=ENGINE, state="readonly", width=20)
        self.engine_cb.grid(row=0, column=1, padx=6, pady=4)
        self.engine_cb.current(0)

        # Gearbox
        ttk.Label(frm, text="Gearbox:").grid(row=0, column=2, sticky="w", padx=(12,6))
        self.gear_cb = ttk.Combobox(frm, values=GEARBOX, state="readonly", width=20)
        self.gear_cb.grid(row=0, column=3, padx=6, pady=4)
        self.gear_cb.current(0)

        # Main Motor
        ttk.Label(frm, text="Main Motor:").grid(row=1, column=0, sticky="w", padx=(0,6))
        self.main_cb = ttk.Combobox(frm, values=[], state="readonly", width=20)
        self.main_cb.grid(row=1, column=1, padx=6, pady=4)

        # Sub Motor
        ttk.Label(frm, text="Sub Motor:").grid(row=1, column=2, sticky="w", padx=(12,6))
        self.sub_cb = ttk.Combobox(frm, values=[], state="readonly", width=20)
        self.sub_cb.grid(row=1, column=3, padx=6, pady=4)

        # Text output
        self.text = tk.Text(self, wrap="none", height=26)
        self.text.pack(side=tk.TOP, fill=tk.BOTH, expand=True, padx=10, pady=(4,10))

        # Buttons
        btns = ttk.Frame(self, padding=(10,0,10,10))
        btns.pack(side=tk.BOTTOM, fill=tk.X)
        self.copy_btn = ttk.Button(btns, text="Copy", command=self.copy_to_clipboard)
        self.copy_btn.pack(side=tk.RIGHT)

        # Wire events
        self.engine_cb.bind("<<ComboboxSelected>>", self.on_engine_or_gearbox)
        self.gear_cb.bind("<<ComboboxSelected>>", self.on_engine_or_gearbox)
        self.main_cb.bind("<<ComboboxSelected>>", self.on_main_motor)
        self.sub_cb.bind("<<ComboboxSelected>>", self.on_any_change)

        # Initial populate/render
        self.refresh_main_options(keep_index=False)
        self.refresh_sub_options(keep_index=False)
        self.render_text()

    def get_indices(self):
        a = self.engine_cb.current()
        b = self.gear_cb.current()
        c = self.main_cb.current()
        d = self.sub_cb.current()
        # Guard against -1 when combobox is empty
        a = 0 if a is None or a < 0 else a
        b = 0 if b is None or b < 0 else b
        c = 0 if c is None or c < 0 else c
        d = 0 if d is None or d < 0 else d
        return a,b,c,d

    def on_engine_or_gearbox(self, _evt=None):
        # Changing engine or gearbox can affect both Main/Sub lists.
        self.refresh_main_options(keep_index=False)
        self.refresh_sub_options(keep_index=False)
        self.render_text()

    def on_main_motor(self, _evt=None):
        # Changing main motor can affect sub-motor list.
        self.refresh_sub_options(keep_index=False)
        self.render_text()

    def on_any_change(self, _evt=None):
        self.render_text()

    def refresh_main_options(self, keep_index=True):
        a = self.engine_cb.current()
        b = self.gear_cb.current()
        new_items = core.main_motor_options(a, b)
        self._set_combo_items(self.main_cb, new_items, keep_index=keep_index)

    def refresh_sub_options(self, keep_index=True):
        a = self.engine_cb.current()
        b = self.gear_cb.current()
        c = self.main_cb.current()
        new_items = core.sub_motor_options(a, b, c)
        if new_items:
            self._set_combo_items(self.sub_cb, new_items, keep_index=keep_index)
        else:
            # AWD case: leave items unchanged by design.
            if self.sub_cb.current() < 0 and self.sub_cb['values']:
                self.sub_cb.current(0)

    def _set_combo_items(self, cb, items, keep_index=True):
        old_items = list(cb['values'])
        old_idx = cb.current()
        if items != old_items:
            cb['values'] = items
            if keep_index and 0 <= old_idx < len(items):
                cb.current(old_idx)
            else:
                cb.current(0)

    def render_text(self):
        a,b,c,d = self.get_indices()
        try:
            text = core.build_pc(a,b,c,d)
        except Exception as e:
            text = f"[Error building text: {e}]"
        self.text.delete("1.0", tk.END)
        self.text.insert("1.0", text)

    def copy_to_clipboard(self):
        txt = self.text.get("1.0", tk.END)
        self.clipboard_clear()
        self.clipboard_append(txt)
        self.update()
        messagebox.showinfo("Copied", "Configuration text copied to clipboard.")

def main():
    app = App()
    app.mainloop()

if __name__ == "__main__":
    main()
)PY";

int main(int argc, char** argv) {
    try {
        py::scoped_interpreter guard{}; // Start the Python interpreter.
        // Make current working directory importable.
        py::module_::import("sys").attr("path").attr("insert")(0, ".");
        py::exec(PY_UI);
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
