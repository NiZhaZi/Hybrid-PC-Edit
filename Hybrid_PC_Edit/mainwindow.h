#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// #include<bits/stdtr1c++.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Hybrid_PC_Edit; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void updateMainMotor();
    void updateSubMotor();
    void updateComboBox();

    void on_comboBox_Engine_activated(int index);

    void on_comboBox_Engine_currentIndexChanged(int index);

    void on_comboBox_Gearbox_currentIndexChanged(int index);

    void on_comboBox_Main_Motor_currentIndexChanged(int index);

    void on_comboBox_Sub_Motor_currentIndexChanged(int index);

    void on_pushButton_Copy_clicked();

private:
    Ui::Hybrid_PC_Edit *ui;
};
#endif // MAINWINDOW_H
