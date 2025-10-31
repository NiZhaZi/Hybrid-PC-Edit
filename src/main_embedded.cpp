// main_embedded.cpp  (Dear ImGui rewrite)
// Single-OS-window UI, no extra "window-inside-window" look.
// Uses GLFW + OpenGL2 backend for simplicity (no external GL loader).

#include "core.hpp"   // build_pc, main_motor_options, sub_motor_options (existing logic)
// ^ These functions come from existing core.cpp and remain unchanged.

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

// ---- GLFW / OpenGL2 / ImGui includes ----
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"
#include "misc/cpp/imgui_stdlib.h" // std::string overloads for InputText*

// Helper: build a Combo from std::vector<std::string>
static bool ComboFromVector(const char* label, int* current_index, const std::vector<std::string>& items) {
    auto getter = [](void* vec, int idx, const char** out_text) -> bool {
        auto* v = static_cast<const std::vector<std::string>*>(vec);
        if (idx < 0 || idx >= (int)v->size()) return false;
        *out_text = (*v)[idx].c_str();
        return true;
    };
    return ImGui::Combo(label, current_index, getter, (void*)&items, (int)items.size());
}

// Refresh helpers keep index when possible; fallback to 0 if out of range.
static void SetItemsKeepingIndex(std::vector<std::string>& dst, const std::vector<std::string>& src, int& index) {
    if (dst == src) return;           // nothing changed
    std::string cur = (index >= 0 && index < (int)dst.size()) ? dst[index] : std::string();
    dst = src;
    if (dst.empty()) { index = -1; return; }
    auto it = std::find(dst.begin(), dst.end(), cur);
    index = (it != dst.end()) ? int(std::distance(dst.begin(), it)) : 0;
}

int main() {
    // --------------------- Create OS window ---------------------
    if (!glfwInit()) return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    const float kUiScale = 1.20f; // 20% larger UI
    const int kInitW = int(820 * kUiScale);
    const int kInitH = int(600 * kUiScale);
    GLFWwindow* window = glfwCreateWindow(kInitW, kInitH, "Hybrid PC Editor", nullptr, nullptr);
    if (!window) { glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // --------------------- ImGui setup ---------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // --- UI scale: bigger fonts + larger widgets ---
    // Increase default font size (default is ~13 px) and scale all style sizes.
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 18.0f;          // tweak to 16~20 if you want slightly smaller/larger
    io.Fonts->AddFontDefault(&font_cfg);  // add before backend creates the font texture

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(kUiScale);        // scale widgets, paddings, spacing, etc.

    // Keep existing theme call (e.g., dark)
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // --------------------- UI State ---------------------
    // Static option labels (same as original Tk UI)
    static const char* ENGINE_LBL[]  = {"FWD", "RWD", "AWD"};
    static const char* GEARBOX_LBL[] = {"E-CVT", "DHT", "Automatic", "CVT", "DCT", "AMT", "MT"};

    // Indices in the same meaning as original (a,b,c,d)
    int engine = 0, gearbox = 0, mainMotor = 0, subMotor = 0;

    // Dynamic options driven by core.cpp logic
    std::vector<std::string> mainOptions;
    std::vector<std::string> subOptions;

    auto refreshMain = [&](bool keep_index) {
        std::vector<std::string> fresh = main_motor_options(engine, gearbox);
        if (keep_index) SetItemsKeepingIndex(mainOptions, fresh, mainMotor);
        else { mainOptions = fresh; mainMotor = mainOptions.empty() ? -1 : 0; }
    };
    auto refreshSub = [&](bool keep_index) {
        std::vector<std::string> fresh = sub_motor_options(engine, gearbox, (mainMotor < 0 ? 0 : mainMotor));
        if (fresh.empty()) {
            // AWD case: keep previous list unchanged (mirror original Tk behavior).
            if (subOptions.empty()) { subMotor = -1; }
            else if (subMotor < 0 || subMotor >= (int)subOptions.size()) { subMotor = 0; }
            return;
        }
        if (keep_index) SetItemsKeepingIndex(subOptions, fresh, subMotor);
        else { subOptions = fresh; subMotor = subOptions.empty() ? -1 : 0; }
    };
    auto clampIndex = [](int& idx, int n) { if (n <= 0) idx = -1; else if (idx < 0 || idx >= n) idx = 0; };

    // Initial populate & text
    refreshMain(false);
    refreshSub(false);
    std::string configText = build_pc(engine, gearbox, (mainMotor < 0 ? 0 : mainMotor), (subMotor < 0 ? 0 : subMotor));

    bool copiedToast = false;
    float toastTimer = 0.0f;

    // --------------------- Main loop ---------------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Root window covering the main viewport's work area (no inner decorative window).
        ImGuiViewport* vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->WorkPos);
        ImGui::SetNextWindowSize(vp->WorkSize);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                 ImGuiWindowFlags_NoNavFocus;
        if (ImGui::Begin("##root", nullptr, flags)) {

            // --- Controls: one pair per row (label + combo) ---
            // Each combo sits on its own line. We keep the same change-handlers.
            ImGui::PushItemWidth(220.0f * kUiScale);

            // Row 1: Engine
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted("Engine:");
            ImGui::SameLine();
            if (ImGui::Combo("##engine", &engine, ENGINE_LBL, IM_ARRAYSIZE(ENGINE_LBL))) {
                // Changing engine affects both Main/Sub lists and the text
                refreshMain(false);
                refreshSub(false);
                clampIndex(mainMotor, (int)mainOptions.size());
                clampIndex(subMotor,  (int)subOptions.size());
                configText = build_pc(engine, gearbox, (mainMotor < 0 ? 0 : mainMotor), (subMotor < 0 ? 0 : subMotor));
            }

            ImGui::Spacing(); // visual gap between rows

            // Row 2: Gearbox
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted("Gearbox:");
            ImGui::SameLine();
            if (ImGui::Combo("##gearbox", &gearbox, GEARBOX_LBL, IM_ARRAYSIZE(GEARBOX_LBL))) {
                // Changing gearbox affects both Main/Sub lists and the text
                refreshMain(false);
                refreshSub(false);
                clampIndex(mainMotor, (int)mainOptions.size());
                clampIndex(subMotor,  (int)subOptions.size());
                configText = build_pc(engine, gearbox, (mainMotor < 0 ? 0 : mainMotor), (subMotor < 0 ? 0 : subMotor));
            }

            ImGui::Spacing();

            // Row 3: Main Motor
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted("Main Motor:");
            ImGui::SameLine();
            if (ComboFromVector("##main", &mainMotor, mainOptions)) {
                // Changing main motor can affect sub-motor list and the text
                refreshSub(false);
                clampIndex(subMotor, (int)subOptions.size());
                configText = build_pc(engine, gearbox, (mainMotor < 0 ? 0 : mainMotor), (subMotor < 0 ? 0 : subMotor));
            }

            ImGui::Spacing();

            // Row 4: Sub Motor
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted("Sub Motor:");
            ImGui::SameLine();
            // If AWD keeps list unchanged and it's empty initially, disable the combo.
            bool disableSub = subOptions.empty();
            if (disableSub) ImGui::BeginDisabled(true);
            if (ComboFromVector("##sub", &subMotor, subOptions)) {
                configText = build_pc(engine, gearbox, (mainMotor < 0 ? 0 : mainMotor), (subMotor < 0 ? 0 : subMotor));
            }
            if (disableSub) ImGui::EndDisabled();

            ImGui::PopItemWidth();

            ImGui::Separator();

            // --- Multiline output (read-only) ---
            // Fill remaining space minus a small area for the bottom button row.
            ImVec2 avail = ImGui::GetContentRegionAvail();
            float buttonRowH = 40.0f;
            ImVec2 textSize(avail.x, std::max(0.0f, avail.y - buttonRowH));
            ImGui::InputTextMultiline("##config_text", &configText, textSize,
                                      ImGuiInputTextFlags_ReadOnly);
            // Bottom row: right-aligned "Copy" button with a small inline toast
            ImGui::Dummy(ImVec2(avail.x - 90.0f, 0.0f)); ImGui::SameLine();
            if (ImGui::Button("Copy", ImVec2(90.0f, 0.0f))) {
                ImGui::SetClipboardText(configText.c_str());
                copiedToast = true;
                toastTimer = 1.2f; // seconds
            }
            ImGui::SameLine();
            if (copiedToast) {
                ImGui::TextUnformatted("Copied!");
                toastTimer -= ImGui::GetIO().DeltaTime;
                if (toastTimer <= 0.0f) copiedToast = false;
            }
        }
        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#ifdef _WIN32
#include <windows.h>
// Wrap WinMain to call your existing main(), so we don't need to refactor anything.
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main();
}
#endif
