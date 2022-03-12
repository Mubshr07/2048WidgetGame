#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include <stdio.h>
#include <QDateTime>
#include <QtGlobal>
#include <qrandom.h>
#include <QRandomGenerator>
#include <random>

#include <QTimer>
#include <QLabel>
#include <QMessageBox>


enum POSITION {
    IDLE,
    UP_Position,
    DOWN_Position,
    RIGHT_Position,
    LEFT_Position
};

#define SIZE_MATRIX 4

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *e);
    ~MainWindow();


public slots:
    void on_timer_trasition_Elapsed();
    void on_timer_SingleShot_Elapsed();


private slots:
    void on_actionName_Game_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    QString disable_LBL = "margin:2px; border: 1px solid rgb(170, 255, 255); background-color: rgb(162, 134, 157); font: 750 14pt 'MS Shell Dlg 2'; border-radius:8px;";
    QString enable_2_LBL = "margin:2px; border: 1px solid rgb(170, 255, 255); background-color:  rgb(170, 205, 205); font: 750 24pt 'MS Shell Dlg 2'; border-radius:8px; color: rgb(0, 0, 0);";
    QString enable_4_LBL = "margin:2px; border: 1px solid rgb(170, 255, 255); background-color:  rgb(170, 178, 255); font: 750 24pt 'MS Shell Dlg 2'; border-radius:8px; color: rgb(0, 0, 0);";
    QString enable_6_LBL = "margin:2px; border: 1px solid rgb(170, 255, 255); background-color:  rgb(170, 145, 255); font: 750 24pt 'MS Shell Dlg 2'; border-radius:8px; color: rgb(0, 0, 0);";
    QString enable_all_LBL = "margin:2px; border: 1px solid rgb(170, 255, 255); background-color:  rgb(230, 250, 170); font: 750 24pt 'MS Shell Dlg 2'; border-radius:8px; color: rgb(0, 0, 0);";


    QLabel *labelMatrix[SIZE_MATRIX][SIZE_MATRIX];


    QTimer *timer_trasition;
    QTimer *timer_SingleShot;
    bool waiting4trasitionComplete = false;

    void upArrowKeyPressed();
    void downArrowKeyPressed();
    void leftArrowKeyPressed();
    void rightArrowKeyPressed();
    void q_KeyPressed();

    int yourScore = 0;
    int currentWave = 0;
    int currentStep = 0;


    POSITION currentMovingPosition = IDLE;
    void addSameNumbersInPosition(POSITION posi);
    bool newRandomNumber();
    void updateNewMatrix();

    void gameOver();
    bool gameOverDetectionBool = false;

};
#endif // MAINWINDOW_H
