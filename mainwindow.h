#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_acceptButton_clicked();

    void on_clearButton_clicked();

    void on_replotButton_clicked();

    void on_replotButton2_clicked();

    void on_replotButton3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> x, x1, y1, y2, y3, y12, y22, y32, xVector, sigmaYVector, sigmaY2Vector, autoXVector, autoX2Vector, autoY1Vector, autoY2Vector,
    autoY3Vector, autoY12Vector, autoY22Vector, autoY32Vector;
    double xBegin = 0, xEnd, xStep;
};
#endif // MAINWINDOW_H
