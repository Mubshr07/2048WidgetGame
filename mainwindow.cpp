#include "mainwindow.h"
#include "ui_mainwindow.h"

uint matrix[SIZE_MATRIX][SIZE_MATRIX];
bool isMatrixEnable[SIZE_MATRIX][SIZE_MATRIX];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(580, 640);
    this->setWindowTitle("Welcome to 2048Game");

    timer_trasition = new QTimer(this);
    timer_trasition->setInterval(10);
    connect(timer_trasition, SIGNAL(timeout()), this, SLOT(on_timer_trasition_Elapsed()));

    timer_SingleShot = new QTimer(this);
    timer_SingleShot->setSingleShot(true);
    connect(timer_SingleShot, SIGNAL(timeout()), this, SLOT(on_timer_SingleShot_Elapsed()));
    timer_SingleShot->start(300);

}



MainWindow::~MainWindow()
{
    delete ui;
}

// -----------------  Detecting KeyBoard Inputs ----------------
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(waiting4trasitionComplete) return;

    switch (e->key()) {
    case Qt::Key_Up: upArrowKeyPressed(); break;
    case Qt::Key_Down: downArrowKeyPressed(); break;
    case Qt::Key_Left: leftArrowKeyPressed(); break;
    case Qt::Key_Right: rightArrowKeyPressed(); break;
    case Qt::Key_Q: q_KeyPressed(); break;
    }
}
void MainWindow::q_KeyPressed(){
    qDebug() << "Q for Quit";
    QApplication::exit();
}

// ------------ Arrow Keys Method to Initialize sequence -------
void MainWindow::upArrowKeyPressed(){
    qDebug() << "UP";
    for(int i=0; i<SIZE_MATRIX; i++){
        for(int j=0; j<SIZE_MATRIX; j++) {  isMatrixEnable[i][j] = true; }
    }
    currentMovingPosition = UP_Position;
    waiting4trasitionComplete = true;
    currentWave = 1;
    currentStep = 0;
    timer_trasition->start();
}
void MainWindow::downArrowKeyPressed(){
    qDebug() << "DOWN";
    for(int i=0; i<SIZE_MATRIX; i++){
        for(int j=0; j<SIZE_MATRIX; j++) {  isMatrixEnable[i][j] = true; }
    }
    currentMovingPosition = DOWN_Position;
    waiting4trasitionComplete = true;
    currentWave = (SIZE_MATRIX-1);
    currentStep = 0;
    timer_trasition->start();
}
void MainWindow::leftArrowKeyPressed(){
    qDebug() << "LEFT";
    for(int i=0; i<SIZE_MATRIX; i++){
        for(int j=0; j<SIZE_MATRIX; j++) {  isMatrixEnable[i][j] = true; }
    }
    currentMovingPosition = LEFT_Position;
    waiting4trasitionComplete = true;
    currentWave = 1; //(SIZE_MATRIX-1);
    currentStep = 0;
    timer_trasition->start();

}
void MainWindow::rightArrowKeyPressed(){
    qDebug() << "RIGHT";
    for(int i=0; i<SIZE_MATRIX; i++){
        for(int j=0; j<SIZE_MATRIX; j++) {  isMatrixEnable[i][j] = true; }
    }
    currentMovingPosition = RIGHT_Position;
    waiting4trasitionComplete = true;
    currentWave = 3;
    currentStep = 0;
    timer_trasition->start();

}

void MainWindow::on_timer_SingleShot_Elapsed()
{
    for(int i=0; i<SIZE_MATRIX; i++){
        for(int j=0; j<SIZE_MATRIX; j++) {
            matrix[i][j] = 0;
            isMatrixEnable[i][j] = true;
        }
    }

    // Row 0
    labelMatrix[0][0] = ui->lbl_0_0;
    labelMatrix[0][1] = ui->lbl_0_1;
    labelMatrix[0][2] = ui->lbl_0_2;
    labelMatrix[0][3] = ui->lbl_0_3;
    // Row 1
    labelMatrix[1][0] = ui->lbl_1_0;
    labelMatrix[1][1] = ui->lbl_1_1;
    labelMatrix[1][2] = ui->lbl_1_2;
    labelMatrix[1][3] = ui->lbl_1_3;
    // Row 2
    labelMatrix[2][0] = ui->lbl_2_0;
    labelMatrix[2][1] = ui->lbl_2_1;
    labelMatrix[2][2] = ui->lbl_2_2;
    labelMatrix[2][3] = ui->lbl_2_3;
    // Row 3
    labelMatrix[3][0] = ui->lbl_3_0;
    labelMatrix[3][1] = ui->lbl_3_1;
    labelMatrix[3][2] = ui->lbl_3_2;
    labelMatrix[3][3] = ui->lbl_3_3;
    /*
    for(int i=0; i<SIZE_MATRIX; i++)  {
            qDebug()<<" !!!! Matrix Row:"<<i<<" Col 0:"<<matrix[i][0]<<" Col 1:"<<matrix[i][1]<<" Col 2:"<<matrix[i][2]<<" Col 3:"<<matrix[i][3]  ;
        }
    */


    waiting4trasitionComplete = false;
    ui->statusbar->clearMessage();
    newRandomNumber();
    newRandomNumber();
    yourScore = 0;
    updateNewMatrix();


}

// ----------------- Main Methods and algorithms ----------------
void MainWindow::on_timer_trasition_Elapsed()
{
    addSameNumbersInPosition(currentMovingPosition);
    updateNewMatrix();
    /*
    if(waiting4trasitionComplete == false) {
        if(!newRandomNumber()){ gameOver(); }
    }
    */

}
void MainWindow::addSameNumbersInPosition(POSITION posi)
{

    if(currentStep>(SIZE_MATRIX-1)){
        currentWave = 1;
        currentStep = 0;
        timer_trasition->stop();
        waiting4trasitionComplete = false;
        newRandomNumber();
        //qDebug()<<" Timer Stoped and wait for user input. ";
        /*
        qDebug()<<" ++++++++++++++++++++++++++++++++++++++++++++++";
        for(int i=0; i<SIZE_MATRIX; i++) {
                qDebug()<<" !!!! Matrix Row:"<<i<<"   0:"<<matrix[i][0]<<"  1:"<<matrix[i][1]<<"  2:"<<matrix[i][2]<<"  3:"<<matrix[i][3]  ;
            }
        qDebug()<<" ------------------------------------------------ "; */
        return;
    }
    /*
    qDebug()<<" SameNumberInPosition Posi:"<<posi<<" Row:"<<currentWave<<" Step:"<<currentStep<<" 0:"<<matrix[currentWave][0]<<" 1:"<<matrix[currentWave][1]<<" 2:"<<matrix[currentWave][2]<<" 3:"<<matrix[currentWave][3]  ;
    qDebug()<<" ++++++++++++++++++++++++++++++++++++++++++++++";
    for(int i=0; i<SIZE_MATRIX; i++) {
            qDebug()<<" !!!! Matrix Row:"<<i<<"   0:"<<matrix[i][0]<<"  1:"<<matrix[i][1]<<"  2:"<<matrix[i][2]<<"  3:"<<matrix[i][3]  ;
        }
    qDebug()<<" ------------------------------------------------ \n\n";
    */

    switch (posi) {
    case UP_Position:{
        if(currentWave>(SIZE_MATRIX-1)) {
            currentWave = 1; currentStep++;
        }
        /*
        if(currentStep>(SIZE_MATRIX-1)){
            currentWave = 0;
            currentStep = 0;
            timer_trasition->stop();
            waiting4trasitionComplete = false;
             newRandomNumber();
            qDebug()<<" Timer Stoped and wait for user input. ";
            return;
        }
        */



        for(int i=0; i<SIZE_MATRIX; i++) {
            if(matrix[currentWave][i] != 0){
                if(matrix[currentWave][i] == matrix[(currentWave-1)][i] && isMatrixEnable[(currentWave-1)][i] && isMatrixEnable[(currentWave)][i])
                {
                    matrix[(currentWave-1)][i] += matrix[currentWave][i];
                    yourScore += matrix[currentWave][i];
                    matrix[currentWave][i] = 0;
                    isMatrixEnable[(currentWave-1)][i] = false;
                }
                else if(matrix[(currentWave-1)][i] == 0)
                {
                    matrix[(currentWave-1)][i] = matrix[currentWave][i];
                    matrix[currentWave][i] = 0;
                }
            }
            else if(matrix[currentWave][i] == 0)
            {
                if(currentWave==(SIZE_MATRIX-1)) matrix[currentWave][i] = 0;
                else {
                    matrix[currentWave][i] = matrix[currentWave+1][i];
                    matrix[currentWave+1][i] = 0;
                }
                //qDebug()<<" @@@@ Matrix Row:"<<currentWave<<" Col:"<<i<<" is Empty. "  ;
            }
        }
        currentWave++;
        break;
    }
    case DOWN_Position:{
        if(currentWave<0) {
            currentWave = SIZE_MATRIX-1; currentStep++;
        }
        for(int i=0; i<SIZE_MATRIX; i++) {
            if(matrix[currentWave][i] != 0){
                if(matrix[currentWave][i] == matrix[(currentWave+1)][i] && isMatrixEnable[(currentWave+1)][i] && isMatrixEnable[(currentWave)][i])
                {
                    matrix[(currentWave+1)][i] += matrix[currentWave][i];
                    yourScore += matrix[currentWave][i];
                    matrix[currentWave][i] = 0;
                    isMatrixEnable[(currentWave+1)][i] = false;
                }
                else if(matrix[(currentWave+1)][i] == 0)
                {
                    matrix[(currentWave+1)][i] = matrix[currentWave][i];
                    matrix[currentWave][i] = 0;
                }
            }
            else if(matrix[currentWave][i] == 0)
            {
                if(currentWave==0) matrix[currentWave][i] = 0;
                else {
                    matrix[currentWave][i] = matrix[currentWave-1][i];
                    matrix[currentWave-1][i] = 0;
                }
                //qDebug()<<" @@@@ Matrix Row:"<<currentWave<<" Col:"<<i<<" is Empty. "  ;
            }
        }
        currentWave--;
        break;
    }
    case RIGHT_Position:{
        if(currentWave<0) {
            currentWave = 3; currentStep++;
        }
        for(int i=0; i<(SIZE_MATRIX); i++) {
            if(matrix[i][currentWave] != 0) {
                if(matrix[i][currentWave] == matrix[i][(currentWave-1)] && isMatrixEnable[i][(currentWave)] && isMatrixEnable[i][(currentWave-1)])
                {
                    matrix[i][(currentWave)] += matrix[i][(currentWave-1)];
                    yourScore += matrix[i][(currentWave-1)];
                    matrix[i][(currentWave-1)] = 0;
                    isMatrixEnable[i][(currentWave)] = false;
                }
                /*
                else if(matrix[i][(currentWave+1)] == 0)
                {
                    matrix[i][(currentWave+1)] = matrix[i][currentWave];
                    matrix[i][currentWave] = 0;
                } */
            }
            else if(matrix[i][currentWave] == 0)
            {
                if(currentWave==0) matrix[i][currentWave] = 0;
                else {
                    matrix[i][(currentWave)] = matrix[i][(currentWave-1)];
                    matrix[i][(currentWave-1)] = 0;
                }
                //qDebug()<<" @@@@ Matrix Row:"<<currentWave<<" Col:"<<i<<" is Empty. "  ;
            }
        }
        currentWave--;
        break;
    }
    case LEFT_Position:{
        if(currentWave>(SIZE_MATRIX-1)) {
            currentWave = 1; currentStep++;
        }
        for(int i=0; i<SIZE_MATRIX; i++) {
            if(matrix[i][currentWave] != 0){
                if(matrix[i][currentWave] == matrix[i][(currentWave-1)] && isMatrixEnable[i][(currentWave-1)] && isMatrixEnable[i][(currentWave)])
                {
                    matrix[i][(currentWave-1)] += matrix[i][currentWave];
                    yourScore += matrix[i][currentWave];
                    matrix[i][currentWave] = 0;
                    isMatrixEnable[i][(currentWave-1)] = false;
                }
                else if(matrix[i][(currentWave-1)] == 0)
                {
                    matrix[i][(currentWave-1)] = matrix[i][currentWave];
                    matrix[i][currentWave] = 0;
                }
            }
            else if(matrix[i][currentWave] == 0)
            {
                if(currentWave==(SIZE_MATRIX-1)) matrix[i][currentWave] = 0;
                else {
                    matrix[i][currentWave] = matrix[i][(currentWave+1)];
                    matrix[i][(currentWave+1)] = 0;
                }
                //qDebug()<<" @@@@ Matrix Row:"<<currentWave<<" Col:"<<i<<" is Empty. "  ;
            }
        }
        currentWave++;
        break;
    }
    }



}
bool MainWindow::newRandomNumber()
{
    uint newNumber =0;
    uint newPositionCol =0;
    uint newPositionRow =0;
    /*
    qDebug()<<" ++++++++++++++++++++++++++++++++++++++++++++++";
    for(int i=0; i<SIZE_MATRIX; i++) {
            qDebug()<<" !!!! Matrix Row:"<<i<<"   0:"<<matrix[i][0]<<"  1:"<<matrix[i][1]<<"  2:"<<matrix[i][2]<<"  3:"<<matrix[i][3]  ;
        }
    qDebug()<<" ------------------------------------------------ ";
    */
    //srand(QDateTime::currentMSecsSinceEpoch());
    QRandomGenerator randomGen(QDateTime::currentMSecsSinceEpoch()/1000);
    newNumber = ((randomGen.generate() %3)*2);
    while (newNumber<=0 ) {
        newNumber = ((randomGen.generate() %3)*2);
    }
    //qDebug()<<" NUmber : "<<newNumber;

    randomGen.seed(QDateTime::currentMSecsSinceEpoch()/1000);

    randomGen.bounded(0, (SIZE_MATRIX-1));
    newPositionCol = randomGen.generate()%SIZE_MATRIX;
    newPositionRow = randomGen.generate()%SIZE_MATRIX;
    QTimer wait_Timer;
    wait_Timer.setSingleShot(true);
    wait_Timer.setInterval(1000);
    wait_Timer.start();

    while (true) {
        if(matrix[newPositionRow][newPositionCol] == 0) break;
        else if(wait_Timer.remainingTime()<=0) { gameOverDetectionBool = true; break; }
        randomGen.seed(QDateTime::currentMSecsSinceEpoch()/1000);
        newPositionCol = randomGen.generate()%SIZE_MATRIX; //(rand() % SIZE_MATRIX + 0);
        newPositionRow = randomGen.generate()%SIZE_MATRIX; //(rand() % SIZE_MATRIX + 0);
    }
    wait_Timer.stop();
    if(gameOverDetectionBool){
        for(int i=0; i<SIZE_MATRIX; i++)
            for(int j=0; j<SIZE_MATRIX; j++){
                if(matrix[i][j] == 0){
                    newPositionRow = i;
                    newPositionCol = j;
                    gameOverDetectionBool = false;
                    break;
                }
            }
    }
    if(gameOverDetectionBool) {
        gameOver();
        return false;
    }

    //qDebug()<<" newRandomNumber:: Number:"<<newNumber<<" row:"<<newPositionRow<<" col:"<<newPositionCol;
    if(matrix[newPositionRow][newPositionCol]!=0 && newNumber==0) return false;
    matrix[newPositionRow][newPositionCol] = newNumber;

    /*
    qDebug()<<" ++++++++++++++++++++++++++++++++++++++++++++++";
    for(int i=0; i<SIZE_MATRIX; i++) {
            qDebug()<<" !!!! Matrix Row:"<<i<<"   0:"<<matrix[i][0]<<"  1:"<<matrix[i][1]<<"  2:"<<matrix[i][2]<<"  3:"<<matrix[i][3]  ;
        }
    qDebug()<<" ------------------------------------------------ ";
    */

    return true;
}
void MainWindow::updateNewMatrix()
{
    for(int i=0; i<SIZE_MATRIX; i++){
        for(int j=0; j<SIZE_MATRIX; j++)
            if(matrix[i][j] == 0){
                labelMatrix[i][j]->setText("");
                labelMatrix[i][j]->setStyleSheet(disable_LBL);
            } else {
                if(matrix[i][j] == 2){
                    labelMatrix[i][j]->setText(QString::number(matrix[i][j], 10));
                    labelMatrix[i][j]->setStyleSheet(enable_2_LBL);
                } else if(matrix[i][j] == 4){
                    labelMatrix[i][j]->setText(QString::number(matrix[i][j], 10));
                    labelMatrix[i][j]->setStyleSheet(enable_4_LBL);
                } else if(matrix[i][j] == 6){
                    labelMatrix[i][j]->setText(QString::number(matrix[i][j], 10));
                    labelMatrix[i][j]->setStyleSheet(enable_6_LBL);
                } else if(matrix[i][j] > 6){
                    labelMatrix[i][j]->setText(QString::number(matrix[i][j], 10));
                    labelMatrix[i][j]->setStyleSheet(enable_all_LBL);
                }
            }
    }
    ui->lbl_YourScores->setText(QString::number(yourScore, 10));
}
void MainWindow::gameOver()
{
    timer_trasition->stop();
    waiting4trasitionComplete = true;
    QMessageBox::warning(this, "Game Over!", QString("You game is Over. Your Scores: "+QString::number(yourScore, 10)));
    ui->statusbar->showMessage("Game Over.");
}


// ----------------- Menu Tool bar Actions -----------------------
void MainWindow::on_actionName_Game_triggered()
{
    timer_SingleShot->start(10);
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}




