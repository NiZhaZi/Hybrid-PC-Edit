#include "core.hpp"
#include <sstream>

namespace {
inline void add(std::vector<std::string>& L, const std::string& s) { L.push_back(s); }
inline void nl(std::vector<std::string>& L) { L.emplace_back(""); }
static std::string join_lines(const std::vector<std::string>& L) {
    std::ostringstream oss;
    for (size_t i = 0; i < L.size(); ++i) {
        if (i) oss << '\n';
        oss << L[i];
    }
    return oss.str();
}
} // namespace

std::string build_pc(int a, int b, int c, int d)
{
    std::vector<std::string> L;

    // Dash and navigator
    // add(L, "// Dash and navigator functions, cancel comment them to use them.");
    // add(L, "// \"digidash_screen_logic\": \"auto_play_dash_screen\",");
    // add(L, "// \"dash_battery_display\": \"dash_battery_display\",");
    // add(L, "// \"dash_fuel_display\": \"dash_fuel_display\",");
    // add(L, "// \"dash_awd_display\": \"dash_awd_display\",");
    // add(L, "// \"dash_rpm_display\": \"dash_rpm_display\",");
    // add(L, "// \"dash_power_display\": \"dash_power_display\",");
    // add(L, "// \"navi_screen\": \"navi_screen\",");
    // nl(L);

    add(L, "\"Camso_SpeedLimiter\": \"Camso_SpeedLimiter\",");
    add(L, "\"Camso_DSE\": \"Hybrid_DSE_01\",");

    add(L, "\"Version_AVAS\": \"\", // Version_Legacy Version_Beta");
    add(L, "\"Sound_Forward\": \"Forward_AVAS_Sound_2\", // 1 - 5");
    add(L, "\"Sound_Reverse\": \"Reverse_AVAS_Sound_2\", // 1 - 5");

    switch (a) {
        case 0: { // FWD
            if ((b == 0 || b == 1) || (b != 0 && b != 1 && c == 1)) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_FWD\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_FWD\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_FWD\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_FWD\",");
                nl(L);
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_80NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_120NM\",");
                add(L, "\"Front_Torque_Table\": \"Front_Torque_Table_220NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_320NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_450NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_560NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_680NM\",");
                nl(L);
            } else if (b != 0 && b != 1 && c == 0) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_Parallel\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_Parallel\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_Parallel_FWD\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_Parallel\",");
            }
            break;
        }
        case 1: { // RWD
            if ((b == 0 || b == 1) || (b != 0 && b != 1 && c == 1)) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_RWD\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_RWD\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_RWD\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_RWD\",");
                nl(L);
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_100NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_200NM\",");
                add(L, "\"Rear_Torque_Table\": \"Rear_Torque_Table_300NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_460NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_580NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_720NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_830NM\",");
                nl(L);
            } else if (b != 0 && b != 1 && c == 0) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_Parallel\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_Parallel\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_Parallel_RWD\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_Parallel\",");
            }
            break;
        }
        case 2: { // AWD
            if (b == 0 || b == 1) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_AWD_hybrid_gearbox\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_AWD_hybrid_gearbox\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_AWD\",");
                add(L, "\"Camso_differential_center\": \"Camso_differential_center_hybrid_gearbox\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_AWD_hybrid_gearbox\",");
                nl(L);
                add(L, "// \"AWD_Torque_Table\": \"AWD_Torque_Table_80NM\",");
                add(L, "\"AWD_Torque_Table\": \"AWD_Torque_Table_120NM\",");
                add(L, "// \"AWD_Torque_Table\": \"AWD_Torque_Table_220NM\",");
                nl(L);
            } else if (c == 0) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_AWD_hybrid_gearbox\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_AWD_hybrid_gearbox\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_AWD\",");
                add(L, "\"Camso_differential_center\": \"Camso_differential_center_hybrid_gearbox\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_AWD_hybrid_gearbox\",");
                nl(L);
                add(L, "// \"AWD_Torque_Table\": \"AWD_Torque_Table_80NM\",");
                add(L, "\"AWD_Torque_Table\": \"AWD_Torque_Table_120NM\",");
                add(L, "// \"AWD_Torque_Table\": \"AWD_Torque_Table_220NM\",");
                nl(L);
            } else if (c == 1) {
                add(L, "\"Camso_TC\": \"Hybrid_TC_AWD\",");
                add(L, "\"Camso_ESC\": \"Hybrid_ESC_AWD\",");
                add(L, "\"Camso_TransferCase\": \"Camso_TransferCase_AWD\",");
                add(L, "\"Hybrid_Configure\": \"Hybrid_Configure_AWD\",");
                nl(L);
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_80NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_120NM\",");
                add(L, "\"Front_Torque_Table\": \"Front_Torque_Table_220NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_320NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_450NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_560NM\",");
                add(L, "// \"Front_Torque_Table\": \"Front_Torque_Table_680NM\",");
                nl(L);
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_100NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_200NM\",");
                add(L, "\"Rear_Torque_Table\": \"Rear_Torque_Table_300NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_460NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_580NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_720NM\",");
                add(L, "// \"Rear_Torque_Table\": \"Rear_Torque_Table_830NM\",");
                nl(L);
            }
            break;
        }
    }

    switch (d) {
        case 0: {
            if (a == 0) {
                if ((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)) {
                    add(L, "");
                } else {
                    add(L, "\"Rear_ElectricMotor\": \"Rear_Single_ElectricMotor\",");
                    add(L, "// \"Rear_Single_Motors_Table\": \"Rear_Single_Motors_Table_65NM\",");
                    add(L, "\"Rear_Single_Motors_Table\": \"Rear_Single_Motors_Table_95NM\",");
                }
            } else if (a == 1) {
                if ((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)) {
                    add(L, "");
                } else {
                    add(L, "\"Front_ElectricMotor\": \"Front_Single_ElectricMotor\",");
                    add(L, "// \"Front_Single_Motors_Table\": \"Front_Single_Motors_Table_65NM\",");
                    add(L, "\"Front_Single_Motors_Table\": \"Front_Single_Motors_Table_95NM\",");
                }
            }
            break;
        }
        case 1: {
            if (a == 0) {
                if ((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)) {
                    add(L, "\"Rear_ElectricMotor\": \"Rear_Single_ElectricMotor\",");
                    add(L, "// \"Rear_Single_Motors_Table\": \"Rear_Single_Motors_Table_65NM\",");
                    add(L, "\"Rear_Single_Motors_Table\": \"Rear_Single_Motors_Table_95NM\",");
                } else {
                    add(L, "\"Rear_ElectricMotor\": \"Rear_Dual_ElectricMotor\",");
                    add(L, "// \"Rear_Dual_Motors_Table\": \"Rear_Dual_Motors_Table_65NM\",");
                    add(L, "\"Rear_Dual_Motors_Table\": \"Rear_Dual_Motors_Table_95NM\",");
                }
            } else if (a == 1) {
                if ((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)) {
                    add(L, "\"Front_ElectricMotor\": \"Front_Single_ElectricMotor\",");
                    add(L, "// \"Front_Single_Motors_Table\": \"Front_Single_Motors_Table_65NM\",");
                    add(L, "\"Front_Single_Motors_Table\": \"Front_Single_Motors_Table_95NM\",");
                } else {
                    add(L, "\"Front_ElectricMotor\": \"Front_Dual_ElectricMotor\",");
                    add(L, "// \"Front_Dual_Motors_Table\": \"Front_Dual_Motors_Table_65NM\",");
                    add(L, "\"Front_Dual_Motors_Table\": \"Front_Dual_Motors_Table_95NM\",");
                }
            }
            break;
        }
        case 2: {
            if (a == 0) {
                add(L, "\"Rear_ElectricMotor\": \"Rear_Dual_ElectricMotor\",");
                add(L, "// \"Rear_Dual_Motors_Table\": \"Rear_Dual_Motors_Table_65NM\",");
                add(L, "\"Rear_Dual_Motors_Table\": \"Rear_Dual_Motors_Table_95NM\",");
            } else if (a == 1) {
                add(L, "\"Front_ElectricMotor\": \"Front_Dual_ElectricMotor\",");
                add(L, "// \"Front_Dual_Motors_Table\": \"Front_Dual_Motors_Table_65NM\",");
                add(L, "\"Front_Dual_Motors_Table\": \"Front_Dual_Motors_Table_95NM\",");
            }
            break;
        }
    }

    switch (b) {
        case 0: add(L, "\"Camso_Transmission\": \"E-CVT_Gearbox_E_Transmission\","); break;
        case 1: add(L, "\"Camso_Transmission\": \"DHT_Gearbox_E_Transmission\","); break;
        case 2: add(L, "\"Camso_Transmission\": \"Automatic_Gearbox_E_Transmission\","); break;
        case 3: add(L, "\"Camso_Transmission\": \"CVT_Gearbox_E_Transmission\","); break;
        case 4: add(L, "\"Camso_Transmission\": \"DCT_Gearbox_E_Transmission\","); break;
        case 5: add(L, "\"Camso_Transmission\": \"AMT_Gearbox_E_Transmission\","); break;
        case 6: add(L, "\"Camso_Transmission\": \"MT_Gearbox_E_Transmission\","); break;
    }

    nl(L);
    add(L, "// Drive modes options.");
    add(L, "\"auto\": \"auto_mode\",");
    add(L, "\"hybrid\": \"hybrid_mode\",");
    add(L, "\"electric\": \"electric_mode\",");
    add(L, "\"fuel\": \"fuel_mode\",");

    nl(L);
    // add(L, "// Optional functions, cancel comment them to use them.");
    // add(L, "// \"Dynamic_System\": \"Dynamic_System\",");
    // add(L, "// \"Dynamic_awd\": \"Dynamic_awd\",");
    // add(L, "// \"Dynamic_lsd\": \"Dynamic_lsd\",");
    // add(L, "// \"Rear_Wheel_Steering\": \"Rear_Wheel_Steering\",");
    // add(L, "// \"Suspension_Lift\": \"Suspension_Lift\",");

    return join_lines(L);
}

std::vector<std::string> main_motor_options(int engine, int gearbox)
{
    std::vector<std::string> items;
    if (engine == 0) { // Front engine (FWD)
        if (gearbox == 0 || gearbox == 1) {
            items.push_back("Front Main Motor");
        } else {
            items.push_back("No Main Motor");
            items.push_back("Front Main Motor");
        }
    } else if (engine == 1) { // Rear engine (RWD)
        if (gearbox == 0 || gearbox == 1) {
            items.push_back("Rear Main Motor");
        } else {
            items.push_back("No Main Motor");
            items.push_back("Rear Main Motor");
        }
    } else if (engine == 2) { // AWD
        if (gearbox == 0 || gearbox == 1) {
            items.push_back("Single Main Motor");
        } else {
            items.push_back("Single Main Motor");
            items.push_back("Front Motor and Rear Motor");
        }
    }
    return items;
}

std::vector<std::string> sub_motor_options(int engine, int gearbox, int main_motor)
{
    // AWD: keep unchanged (mirror original behavior).
    if (engine == 2) return {};

    std::vector<std::string> items;
    if (engine != 2) {
        if (main_motor == 0 && (gearbox != 0 && gearbox != 1)) {
            if (engine == 0) {
                items.push_back("Rear Single Motor");
                items.push_back("Rear Dual Motor");
            } else { // engine == 1
                items.push_back("Front Single Motor");
                items.push_back("Front Dual Motor");
            }
        } else {
            if (engine == 0) {
                items.push_back("No Sub Motor");
                items.push_back("Rear Single Motor");
                items.push_back("Rear Dual Motor");
            } else {
                items.push_back("No Sub Motor");
                items.push_back("Front Single Motor");
                items.push_back("Front Dual Motor");
            }
        }
    }
    return items;
}
