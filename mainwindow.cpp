#include "mainwindow.h"
#include "ui_mainwindow.h"

int c=-1, u=-1, T=-1, htv=-1, x1Start=-1, x2Start=-1, x3Start=-1;
double g = 9.81, h = -1;

void clearVector(QVector<double> &vector){
    for(int i = 0; i < vector.size(); i++){
        vector.erase(vector.begin());
    }
}

double epsilon(double yK, double y){
    return abs(yK-y);
}

double sigma(double epsilon, double yK){
    return abs((epsilon/yK)*100);
}

double odeX3(){
    return u * (-1);
}

float r(QVector<double> values, int i){
    return 0.1 * exp(values[i-1]/htv);
}

double odeX2(QVector<double> values3, QVector<double> values2, QVector<double> values1, int i){
    return ((c*u)/values3[i-1])-g-(r(values1, i)*values2[i-1])/values3[i-1];
}

double odeX1(QVector<double> values2, int i){
    return values2[i-1];
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->replotButton->setDisabled(true);
    ui->replotButton2->setDisabled(true);
    ui->replotButton3->setDisabled(true);
    QPen pen;
    pen.setWidth(2);
    ui->x1Chart->setInteraction(QCP::iRangeZoom, true);
    ui->x1Chart->setInteraction(QCP::iRangeDrag, true);
    ui->x1Chart->xAxis->setLabel("t");
    ui->x1Chart->yAxis->setLabel("X(t)");
    ui->x2Chart->setInteraction(QCP::iRangeZoom, true);
    ui->x2Chart->setInteraction(QCP::iRangeDrag, true);
    ui->x2Chart->xAxis->setLabel("t");
    ui->x2Chart->yAxis->setLabel("X(t)");
    ui->x3Chart->setInteraction(QCP::iRangeZoom, true);
    ui->x3Chart->setInteraction(QCP::iRangeDrag, true);
    ui->x3Chart->xAxis->setLabel("t");
    ui->x3Chart->yAxis->setLabel("X(t)");
    ui->x12Chart->setInteraction(QCP::iRangeZoom, true);
    ui->x12Chart->setInteraction(QCP::iRangeDrag, true);
    ui->x12Chart->xAxis->setLabel("t");
    ui->x12Chart->yAxis->setLabel("X(t)");
    ui->x22Chart->setInteraction(QCP::iRangeZoom, true);
    ui->x22Chart->setInteraction(QCP::iRangeDrag, true);
    ui->x22Chart->xAxis->setLabel("t");
    ui->x22Chart->yAxis->setLabel("X(t)");
    ui->x32Chart->setInteraction(QCP::iRangeZoom, true);
    ui->x32Chart->setInteraction(QCP::iRangeDrag, true);
    ui->x32Chart->xAxis->setLabel("t");
    ui->x32Chart->yAxis->setLabel("X(t)");
    ui->sigmaX1Chart->setInteraction(QCP::iRangeZoom, true);
    ui->sigmaX1Chart->setInteraction(QCP::iRangeDrag, true);
    ui->sigmaX1Chart->xAxis->setLabel("t");
    ui->sigmaX1Chart->yAxis->setLabel("Sigma X1");
    ui->sigmaX2Chart->setInteraction(QCP::iRangeZoom, true);
    ui->sigmaX2Chart->setInteraction(QCP::iRangeDrag, true);
    ui->sigmaX2Chart->xAxis->setLabel("t");
    ui->sigmaX2Chart->yAxis->setLabel("Sigma X2");
    ui->autoX1Chart->setInteraction(QCP::iRangeZoom, true);
    ui->autoX1Chart->setInteraction(QCP::iRangeDrag, true);
    ui->autoX1Chart->xAxis->setLabel("t");
    ui->autoX1Chart->yAxis->setLabel("X(t)");
    ui->autoX2Chart->setInteraction(QCP::iRangeZoom, true);
    ui->autoX2Chart->setInteraction(QCP::iRangeDrag, true);
    ui->autoX2Chart->xAxis->setLabel("t");
    ui->autoX2Chart->yAxis->setLabel("X(t)");
    ui->autoX3Chart->setInteraction(QCP::iRangeZoom, true);
    ui->autoX3Chart->setInteraction(QCP::iRangeDrag, true);
    ui->autoX3Chart->xAxis->setLabel("t");
    ui->autoX3Chart->yAxis->setLabel("X(t)");
    ui->handsChart->setInteraction(QCP::iRangeZoom, true);
    ui->handsChart->setInteraction(QCP::iRangeDrag, true);
    ui->handsChart->xAxis->setLabel("Counter");
    ui->handsChart->yAxis->setLabel("Step");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_acceptButton_clicked()
{
    QString line;

    try{
        line = ui->cEdit->text();
        c = line.toInt();
        line = ui->uEdit->text();
        u = line.toInt();
        line = ui->TEdit->text();
        T = line.toInt();
        line = ui->htvEdit->text();
        htv = line.toInt();
        line = ui->x1StartEdit->text();
        x1Start = line.toInt();
        line = ui->x2StartEdit->text();
        x2Start = line.toInt();
        line = ui->x3StartEdit->text();
        x3Start = line.toInt();
        line = ui->hEdit->text();
        h = line.toInt();
        h /= 1000;
    } catch (const std::exception ex) {
        QMessageBox * msgbox = new QMessageBox(this);
        msgbox->setText(ex.what());
        msgbox->show();
    }
    if(c && u && T && htv && h > 0){
        QMessageBox * msgbox = new QMessageBox(this);
        msgbox->setText("Данные добавлены. Переключайтесь на следующую вкладку!");
        msgbox->show();
        ui->replotButton->setDisabled(false);
    }
    else{
        QMessageBox * msgbox = new QMessageBox(this);
        msgbox->setText("Ошибка! Введите другие данные!");
        msgbox->show();
    }
}


void MainWindow::on_clearButton_clicked()
{
    ui->cEdit->setText("");
    ui->uEdit->setText("");
    ui->TEdit->setText("");
    ui->htvEdit->setText("");
    ui->x1StartEdit->setText("");
    ui->x2StartEdit->setText("");
    ui->x3StartEdit->setText("");
}


void MainWindow::on_replotButton_clicked()
{
    ui->x1Chart->clearGraphs();
    ui->x2Chart->clearGraphs();
    ui->x3Chart->clearGraphs();
    xEnd = T + h;
    x.clear();
    y1.clear();
    y2.clear();
    y3.clear();

    for(float i = xBegin; i < xEnd; i+=h){
        x.push_back(i);
    }

    for(int i = xBegin; i < x.size(); i++){
        if(i == xBegin){
            y3.push_back(x3Start);
            y2.push_back(x2Start);
            y1.push_back(x1Start);
        }
        else{
            y3.push_back(y3[i-1] + h * odeX3());
            y2.push_back(y2[i-1] + h * odeX2(y3, y2, y1, i));
            y1.push_back(y1[i-1] + h * odeX1(y2, i));
        }
    }
    ui->x1Chart->xAxis->setRange(-0.1, 11.1);
    ui->x1Chart->yAxis->setRange(-0.1, y1[y1.size()-1]);
    ui->x2Chart->xAxis->setRange(-0.1, 11.1);
    ui->x2Chart->yAxis->setRange(-0.1, y2[y2.size()-1]);
    ui->x3Chart->xAxis->setRange(-0.1, 11.1);
    ui->x3Chart->yAxis->setRange(1100.1, y3[y3.size()-1]);

    ui->x1Chart->addGraph();
    ui->x1Chart->graph(0)->addData(x,y1);
    ui->x1Chart->replot();
    ui->x2Chart->addGraph();
    ui->x2Chart->graph(0)->addData(x,y2);
    ui->x2Chart->replot();
    ui->x3Chart->addGraph();
    ui->x3Chart->graph(0)->addData(x,y3);
    ui->x3Chart->replot();

    ui->replotButton2->setDisabled(false);
}


void MainWindow::on_replotButton2_clicked()
{
    ui->x12Chart->clearGraphs();
    ui->x22Chart->clearGraphs();
    ui->x32Chart->clearGraphs();
    y12.clear();
    y22.clear();
    y32.clear();
    x1.clear();
    QPen pen;
    pen.setColor(QColor(1, 138, 17));
    xStep = h/2;
    xEnd = T+xStep;

    for(float i = xBegin; i < xEnd; i+=xStep){
        x1.push_back(i);
    }

    for(int i = xBegin; i < x1.size(); i++){
        if(i == xBegin){
            y32.push_back(x3Start);
            y22.push_back(x2Start);
            y12.push_back(x1Start);
        }
        else{
            y32.push_back(y32[i-1] + xStep * odeX3());
            y22.push_back(y22[i-1] + xStep * odeX2(y32, y22, y12, i));
            y12.push_back(y12[i-1] + xStep * odeX1(y22, i));
        }
    }

    ui->x12Chart->xAxis->setRange(-0.1, 11.1);
    ui->x12Chart->yAxis->setRange(-0.1, y1[y1.size()-1]);
    ui->x22Chart->xAxis->setRange(-0.1, 11.1);
    ui->x22Chart->yAxis->setRange(-0.1, y2[y2.size()-1]);
    ui->x32Chart->xAxis->setRange(-0.1, 11.1);
    ui->x32Chart->yAxis->setRange(1100.1, y3[y3.size()-1]);

    ui->x12Chart->addGraph();
    ui->x12Chart->graph(0)->addData(x1,y12);
    ui->x12Chart->addGraph();
    ui->x12Chart->graph(1)->addData(x,y1);
    ui->x12Chart->graph(0)->setPen(pen);
    ui->x12Chart->replot();

    ui->x22Chart->addGraph();
    ui->x22Chart->graph(0)->addData(x1,y22);
    ui->x22Chart->addGraph();
    ui->x22Chart->graph(1)->addData(x,y2);
    ui->x22Chart->graph(0)->setPen(pen);
    ui->x22Chart->replot();

    ui->x32Chart->addGraph();
    ui->x32Chart->graph(0)->addData(x1,y32);
    ui->x32Chart->addGraph();
    ui->x32Chart->graph(1)->addData(x,y3);
    ui->x32Chart->graph(0)->setPen(pen);
    ui->x32Chart->replot();
    ui->replotButton3->setDisabled(false);
}


void MainWindow::on_replotButton3_clicked()
{
    ui->sigmaX1Chart->clearGraphs();
    ui->sigmaX2Chart->clearGraphs();
    sigmaYVector.clear();
    sigmaY2Vector.clear();
    xVector.clear();

    double eps, sig;
    eps = epsilon(y12[y12.size()-1], y1[y1.size()-1]);
    sig = sigma(eps, y12[y12.size()-1]);
    ui->absEpsilon1->setText(QString::number(eps));
    ui->otnSigma1->setText(QString::number(sig) + "%");

    eps = epsilon(y22[y22.size()-1], y2[y2.size()-1]);
    sig = sigma(eps, y22[y22.size()-1]);
    ui->absEpsilon2->setText(QString::number(eps));
    ui->otnSigma2->setText(QString::number(sig) + "%");

    eps = epsilon(y32[y32.size()-1], y3[y3.size()-1]);
    sig = sigma(eps, y32[y32.size()-1]);
    ui->absEpsilon3->setText(QString::number(eps));
    ui->otnSigma3->setText(QString::number(sig) + "%");

    for(int i = 0; i < x.size(); i++){
        sigmaYVector.push_back(sigma(epsilon(y12[i*2],y1[i]),y12[i*2]));
        sigmaY2Vector.push_back(sigma(epsilon(y22[i*2], y2[i]),y22[i*2]));
    }

    ui->sigmaX1Chart->xAxis->setRange(0, T);
    ui->sigmaX1Chart->yAxis->setRange(0, *std::max_element(sigmaYVector.begin(), sigmaYVector.end()));
    ui->sigmaX2Chart->xAxis->setRange(0, T);
    ui->sigmaX2Chart->yAxis->setRange(0, 0.005);
    ui->sigmaX1Chart->addGraph();
    ui->sigmaX1Chart->graph(0)->addData(x, sigmaYVector);
    ui->sigmaX1Chart->replot();
    ui->sigmaX2Chart->addGraph();
    ui->sigmaX2Chart->graph(0)->addData(x, sigmaY2Vector);
    ui->sigmaX2Chart->replot();
}


void MainWindow::on_pushButton_clicked()
{
    autoXVector.clear();
    autoX2Vector.clear();
    autoY1Vector.clear();
    autoY12Vector.clear();
    autoY2Vector.clear();
    autoY22Vector.clear();
    autoY3Vector.clear();
    autoY32Vector.clear();
    ui->autoX1Chart->clearGraphs();
    ui->autoX2Chart->clearGraphs();
    ui->autoX3Chart->clearGraphs();
    ui->handsChart->clearGraphs();

    if(T == -1){
        QMessageBox * msgbox = new QMessageBox(this);
        msgbox->setText("Введите данные!");
        msgbox->show();
        return;
    }
    xStep = 1;
    float epsY1, epsY2, epsY3, sigY1, sigY2, sigY3;

RETRY: for(float i=xBegin; i<T; i+=xStep){
        autoXVector.push_back(i);
        }
    for(int i = xBegin; i < autoXVector.size(); i++){
        if(i == xBegin){
            autoY3Vector.push_back(x3Start);
            autoY2Vector.push_back(x2Start);
            autoY1Vector.push_back(x1Start);
        }
        else{
            autoY3Vector.push_back(autoY3Vector[i-1] + xStep * odeX3());
            autoY2Vector.push_back(autoY2Vector[i-1] + xStep * odeX2(autoY3Vector, autoY2Vector, autoY1Vector, i));
            autoY1Vector.push_back(autoY1Vector[i-1] + xStep * odeX1(autoY2Vector, i));
        }
    }

    for(float i = xBegin; i<T; i+=xStep/2){
        autoX2Vector.push_back(i);
    }

    for(int i = xBegin; i < autoX2Vector.size(); i++){
        if(i == xBegin){
            autoY32Vector.push_back(x3Start);
            autoY22Vector.push_back(x2Start);
            autoY12Vector.push_back(x1Start);
        }
        else{
            autoY32Vector.push_back(autoY32Vector[i-1] + xStep/2 * odeX3());
            autoY22Vector.push_back(autoY22Vector[i-1] + xStep/2 * odeX2(autoY32Vector, autoY22Vector, autoY12Vector, i));
            autoY12Vector.push_back(autoY12Vector[i-1] + xStep/2 * odeX1(autoY22Vector, i));
        }
    }

    epsY1 = epsilon(autoY12Vector[autoY12Vector.size()-1], autoY1Vector[autoY1Vector.size()-1]);
    sigY1 = sigma(epsY1, autoY12Vector[autoY12Vector.size()-1]);
    epsY2 = epsilon(autoY22Vector[autoY22Vector.size()-1], autoY2Vector[autoY2Vector.size()-1]);
    sigY2 = sigma(epsY2, autoY22Vector[autoY22Vector.size()-1]);
    epsY3 = epsilon(autoY32Vector[autoY32Vector.size()-1], autoY3Vector[autoY3Vector.size()-1]);
    sigY3 = sigma(epsY2, autoY32Vector[autoY32Vector.size()-1]);
    if (sigY1 && sigY2 && sigY3 < 1){
        ui->autoStepLine->setText(QString::number(xStep/2));
        ui->hLine->setText(QString::number(h));
        ui->hHalfLine->setText(QString::number(h/2));
        ui->CounterHLine->setText(QString::number(x.size()));
        ui->CounterHHalfLine->setText(QString::number(x1.size()));
        ui->CounterAutoStepLine->setText(QString::number(autoX2Vector.size()));
        ui->absEpsY1Line->setText(QString::number(epsY1));
        ui->otnSigY1Line->setText(QString::number(sigY1) + "%");
        ui->absEpsY2Line->setText(QString::number(epsY2));
        ui->otnSigY2Line->setText(QString::number(sigY2) + "%");
        ui->absEpsY3Line->setText(QString::number(epsY3));
        ui->otnSigY3Line->setText(QString::number(sigY3) + "%");
        autoXVector.clear();

        autoY1Vector.clear();
        autoY1Vector.push_back(xStep*8);
        autoY1Vector.push_back(xStep*4);
        autoY1Vector.push_back(xStep*2);
        autoY1Vector.push_back(xStep);
        autoY1Vector.push_back(xStep/2);
        autoY1Vector.push_back(xStep/4);
        autoY1Vector.push_back(xStep/8);
        for(int i = 0; i < autoY1Vector.size(); i++){
            autoXVector.push_back(i);
        }

        ui->autoX1Chart->xAxis->setRange(autoX2Vector[0], autoX2Vector[autoX2Vector.size()-1]);
        ui->autoX1Chart->yAxis->setRange(autoY12Vector[0], autoY12Vector[autoY12Vector.size()-1]);
        ui->autoX2Chart->xAxis->setRange(autoX2Vector[0], autoX2Vector[autoX2Vector.size()-1]);
        ui->autoX2Chart->yAxis->setRange(autoY22Vector[0], autoY22Vector[autoY22Vector.size()-1]);
        ui->autoX3Chart->xAxis->setRange(autoX2Vector[0], autoX2Vector[autoX2Vector.size()-1]);
        ui->autoX3Chart->yAxis->setRange(autoY32Vector[0], autoY32Vector[autoY32Vector.size()-1]);
        ui->handsChart->xAxis->setRange(autoXVector[0], autoXVector[autoXVector.size()-1]);
        ui->handsChart->yAxis->setRange(*std::min_element(autoY1Vector.begin(), autoY1Vector.end()), *std::max_element(autoY1Vector.begin(),
                                                                                                                       autoY1Vector.end()));



        ui->autoX1Chart->addGraph();
        ui->autoX1Chart->graph(0)->addData(autoX2Vector, autoY12Vector);
        ui->autoX1Chart->replot();
        ui->autoX2Chart->addGraph();
        ui->autoX2Chart->graph(0)->addData(autoX2Vector, autoY22Vector);
        ui->autoX2Chart->replot();
        ui->autoX3Chart->addGraph();
        ui->autoX3Chart->graph(0)->addData(autoX2Vector, autoY32Vector);
        ui->autoX3Chart->replot();
        ui->handsChart->addGraph();
        ui->handsChart->graph(0)->addData(autoXVector, autoY1Vector);
        ui->handsChart->replot();
    }
    else{
        autoXVector.clear();
        autoX2Vector.clear();
        autoY1Vector.clear();
        autoY12Vector.clear();
        autoY2Vector.clear();
        autoY22Vector.clear();
        autoY3Vector.clear();
        autoY32Vector.clear();
        xStep /= 2;
        goto RETRY;
    }
}

