#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QVector>;

#endif // FUNCTIONS_H

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
