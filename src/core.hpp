#pragma once
#include <string>
#include <vector>

/**
 * Hybrid core logic extracted from the original Qt mainwindow.cpp and rewritten
 * without any Qt dependency. All indices (engine/gearbox/main/sub) follow the
 * same meaning as the original UI.
 *
 * engine:  0 = FWD, 1 = RWD, 2 = AWD
 * gearbox: 0 = E-CVT, 1 = DHT, 2 = Automatic, 3 = CVT, 4 = DCT, 5 = AMT, 6 = MT
 * main:    depends on engine/gearbox; see main_motor_options(...)
 * sub:     depends on engine/main/gearbox; see sub_motor_options(...)
 */
std::string build_pc(int engine, int gearbox, int main_motor, int sub_motor);

/** Compute the "Main Motor" combo options, preserving indices contract of the Qt code. */
std::vector<std::string> main_motor_options(int engine, int gearbox);

/**
 * Compute the "Sub Motor" combo options, preserving indices contract of the Qt code.
 * NOTE: For AWD (engine==2), the original code *does not* modify this combo.
 * To mirror that behavior, this function returns an empty vector when engine==2,
 * which the UI should interpret as "leave the items unchanged".
 */
std::vector<std::string> sub_motor_options(int engine, int gearbox, int main_motor);
