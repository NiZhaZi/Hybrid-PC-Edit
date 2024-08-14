#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QClipboard>
#include <QApplication>

// #include<bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hybrid_PC_Edit)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int engine = -1, gearbox = -1, mainMotor = -1, subMotor = -1;
std::string PC = "";

void clearPC(){
    PC = "";
}

void PCn(){
    PC += "\n";
}

void updatePC(int a, int b, int c, int d){ // engine, gearbox, mainMotor, subMotor
    clearPC();
    PC += "\"digidash_screen_logic\": \"digidash_screen_logic_bng_cus\",";
    PCn();
    PC += "\"digidash_cells_top_left0\": \"digidash_cells_top_left0_evVolume\",";
    PCn();

    PC += "\"Camso_DSE\": \"Hybrid_DSE_01\",";
    PCn();

    switch(a){
        case 0:
            if((b == 0 || b == 1) || (b != 0 && b != 1 && c == 1)){
                PC += "\"Camso_TC\": \"Hybrid_TC_FWD\",";
                PCn();
                PC += "\"Camso_ESC\": \"Hybrid_ESC_FWD\",";
                PCn();
                PC += "\"Camso_TransferCase\": \"Camso_TransferCase_FWD\",";
                PCn();
                PC += "\"Hybrid_Configure\": \"Hybrid_Configure_FWD\",";
                PCn();
                PC += "\"Front_Torque_Table\": \"Front_Torque_Table_220NM\",";
                PCn();
            }
            else if(b != 0 && b != 1 && c == 0){
                PC += "\"Camso_TC\": \"Hybrid_TC_Parallel\",";
                PCn();
                PC += "\"Camso_ESC\": \"Hybrid_ESC_Parallel\",";
                PCn();
                PC += "\"Camso_TransferCase\": \"Camso_TransferCase_Parallel_FWD\",";
                PCn();
                PC += "\"Hybrid_Configure\": \"Hybrid_Configure_Parallel\",";
                PCn();
            }
            break;
        case 1:
            if((b == 0 || b == 1) || (b != 0 && b != 1 && c == 1)){
                PC += "\"Camso_TC\": \"Hybrid_TC_RWD\",";
                PCn();
                PC += "\"Camso_ESC\": \"Hybrid_ESC_RWD\",";
                PCn();
                PC += "\"Camso_TransferCase\": \"Camso_TransferCase_RWD\",";
                PCn();
                PC += "\"Hybrid_Configure\": \"Hybrid_Configure_RWD\",";
                PCn();
                PC += "\"Rear_Torque_Table\": \"Rear_Torque_Table_300NM\",";
                PCn();
            }
            else if(b != 0 && b != 1 && c == 0){
                PC += "\"Camso_TC\": \"Hybrid_TC_Parallel\",";
                PCn();
                PC += "\"Camso_ESC\": \"Hybrid_ESC_Parallel\",";
                PCn();
                PC += "\"Camso_TransferCase\": \"Camso_TransferCase_Parallel_RWD\",";
                PCn();
                PC += "\"Hybrid_Configure\": \"Hybrid_Configure_Parallel\",";
                PCn();
            }
            break;
        case 2:
            if(b == 0 || b == 1){
                PC += "\"Camso_TC\": \"Hybrid_TC_AWD_hybrid_gearbox\",";
                PCn();
                PC += "\"Camso_ESC\": \"Hybrid_ESC_AWD_hybrid_gearbox\",";
                PCn();
                PC += "\"Camso_TransferCase\": \"Camso_TransferCase_AWD\",";
                PCn();
                PC += "\"Camso_differential_center\": \"Camso_differential_center_hybrid_gearbox\",";
                PCn();
                PC += "\"Hybrid_Configure\": \"Hybrid_Configure_AWD_hybrid_gearbox\",";
                PCn();
                PC += "\"AWD_Torque_Table\": \"AWD_Torque_Table_120NM\",";
                PCn();
            }
            else{
                PC += "\"Camso_TC\": \"Hybrid_TC_AWD\",";
                PCn();
                PC += "\"Camso_ESC\": \"Hybrid_ESC_AWD\",";
                PCn();
                PC += "\"Camso_TransferCase\": \"Camso_TransferCase_AWD\",";
                PCn();
                PC += "\"Hybrid_Configure\": \"Hybrid_Configure_AWD\",";
                PCn();
                PC += "\"Front_Torque_Table\": \"Front_Torque_Table_220NM\",";
                PCn();
                PC += "\"Rear_Torque_Table\": \"Rear_Torque_Table_300NM\",";
                PCn();
            }
            break;
    }

    switch(d){
        case 0:
            if(a == 0){
                if((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)){
                    PC += "";
                }
                else{
                    PC += "\"Rear_ElectricMotor\": \"Rear_Single_ElectricMotor\",";
                    PCn();
                }
            }
            else if(a == 1){
                if((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)){
                    PC += "";
                }
                else{
                    PC += "\"Front_ElectricMotor\": \"Front_Single_ElectricMotor\",";
                    PCn();
                }
            }
            break;
        case 1:
            if(a == 0){
                if((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)){
                    PC += "\"Rear_ElectricMotor\": \"Rear_Single_ElectricMotor\",";
                    PCn();
                }
                else{
                    PC += "\"Rear_ElectricMotor\": \"Rear_Dual_ElectricMotor\",";
                    PCn();
                }
            }
            else if(a == 1){
                if((b == 0 || b == 1) || (b != 0 && b != 1 && c != 0)){
                    PC += "\"Front_ElectricMotor\": \"Front_Single_ElectricMotor\",";
                    PCn();
                }
                else{
                    PC += "\"Front_ElectricMotor\": \"Front_Dual_ElectricMotor\",";
                    PCn();
                }
            }
            break;
        case 2:
            if(a == 0){
                PC += "\"Rear_ElectricMotor\": \"Rear_Dual_ElectricMotor\",";
                PCn();
            }
            else if(a == 1){
                PC += "\"Front_ElectricMotor\": \"Front_Single_ElectricMotor\",";
                PCn();
            }
            break;
    }

    switch(b){
        case 0:
            PC += "\"Camso_Transmission\": \"E-CVT_Gearbox_E_Transmission\",";
            PCn();
            break;
        case 1:
            PC += "\"Camso_Transmission\": \"DHT_Gearbox_E_Transmission\",";
            PCn();
            break;
        case 2:
            PC += "\"Camso_Transmission\": \"Automatic_Gearbox_E_Transmission\",";
            PCn();
            break;
        case 3:
            PC += "\"Camso_Transmission\": \"CVT_Gearbox_E_Transmission\",";
            PCn();
            break;
        case 4:
            PC += "\"Camso_Transmission\": \"DCT_Gearbox_E_Transmission\",";
            PCn();
            break;
        case 5:
            PC += "\"Camso_Transmission\": \"AMT_Gearbox_E_Transmission\",";
            PCn();
            break;
        case 6:
            PC += "\"Camso_Transmission\": \"MT_Gearbox_E_Transmission\",";
            PCn();
            break;
    }

}

void MainWindow::updateMainMotor(){
    ui -> comboBox_Main_Motor -> clear();
    if(ui -> comboBox_Engine -> currentIndex() == 0){
        if((ui -> comboBox_Gearbox -> currentIndex() == 0) || (ui -> comboBox_Gearbox -> currentIndex() == 1)){
            ui -> comboBox_Main_Motor -> addItem("Front Main Motor");
        }
        else{
            ui -> comboBox_Main_Motor -> addItem("No Main Motor");
            ui -> comboBox_Main_Motor -> addItem("Front Main Motor");
        }
    }
    else if(ui -> comboBox_Engine -> currentIndex() == 1){
        if((ui -> comboBox_Gearbox -> currentIndex() == 0) || (ui -> comboBox_Gearbox -> currentIndex() == 1)){
            ui -> comboBox_Main_Motor -> addItem("Rear Main Motor");
        }
        else{
            ui -> comboBox_Main_Motor -> addItem("No Main Motor");
            ui -> comboBox_Main_Motor -> addItem("Rear Main Motor");
        }
    }
    else if(ui -> comboBox_Engine -> currentIndex() == 2){
        if((ui -> comboBox_Gearbox -> currentIndex() == 0) || (ui -> comboBox_Gearbox -> currentIndex() == 1)){
            ui -> comboBox_Main_Motor -> addItem("Single Main Motor");
        }
        else{
            ui -> comboBox_Main_Motor -> addItem("Front Motor and Rear Motor");
        }
    }
      
}

void MainWindow::updateSubMotor(){
    ui -> comboBox_Sub_Motor -> clear();
    if(ui -> comboBox_Engine -> currentIndex() != 2){
        if(ui -> comboBox_Main_Motor -> currentIndex() == 0 && ui -> comboBox_Gearbox -> currentIndex() != 0 && ui -> comboBox_Gearbox -> currentIndex() != 1){
            if(ui -> comboBox_Engine -> currentIndex() == 0){
                ui -> comboBox_Sub_Motor -> addItem("Rear Single Motor");
                ui -> comboBox_Sub_Motor -> addItem("Rear Dual Motor");
            }
            else{
                ui -> comboBox_Sub_Motor -> addItem("Front Single Motor");
                ui -> comboBox_Sub_Motor -> addItem("Front Dual Motor");
            }
        }
        else{
            if(ui -> comboBox_Engine -> currentIndex() == 0){
                ui -> comboBox_Sub_Motor -> addItem("No Sub Motor");
                ui -> comboBox_Sub_Motor -> addItem("Rear Single Motor");
                ui -> comboBox_Sub_Motor -> addItem("Rear Dual Motor");
            }
            else{
                ui -> comboBox_Sub_Motor -> addItem("No Sub Motor");
                ui -> comboBox_Sub_Motor -> addItem("Front Single Motor");
                ui -> comboBox_Sub_Motor -> addItem("Front Dual Motor");
            }
        }
    }

}

void MainWindow::updateComboBox(){
    engine = ui -> comboBox_Engine -> currentIndex();
    gearbox = ui -> comboBox_Gearbox -> currentIndex();
    mainMotor = ui -> comboBox_Main_Motor -> currentIndex();
    subMotor = ui -> comboBox_Sub_Motor -> currentIndex();
}

void MainWindow::on_comboBox_Engine_activated(int index)
{
}

void MainWindow::on_comboBox_Engine_currentIndexChanged(int index)
{
    updateComboBox();
    updateMainMotor();
    updateSubMotor();

    updatePC(engine, gearbox, mainMotor, subMotor);
    QString PCstr0 = QString::fromStdString(PC);
    ui -> textBrowser -> setText(PCstr0);
}

void MainWindow::on_comboBox_Gearbox_currentIndexChanged(int index)
{
    updateComboBox();
    updateMainMotor();
    updateSubMotor();

    updatePC(engine, gearbox, mainMotor, subMotor);
    QString PCstr0 = QString::fromStdString(PC);
    ui -> textBrowser -> setText(PCstr0);
}

void MainWindow::on_comboBox_Main_Motor_currentIndexChanged(int index)
{
    updateComboBox();
    updateSubMotor();

    updatePC(engine, gearbox, mainMotor, subMotor);
    QString PCstr0 = QString::fromStdString(PC);
    ui -> textBrowser -> setText(PCstr0);
}

void MainWindow::on_comboBox_Sub_Motor_currentIndexChanged(int index)
{
    updateComboBox();

    updatePC(engine, gearbox, mainMotor, subMotor);
    QString PCstr0 = QString::fromStdString(PC);
    ui -> textBrowser -> setText(PCstr0);
}


void MainWindow::on_pushButton_Copy_clicked()
{
    updatePC(engine, gearbox, mainMotor, subMotor);
    QString PCstr0 = QString::fromStdString(PC);
    QClipboard *clip = QApplication::clipboard();
    clip -> setText(PCstr0);
}

