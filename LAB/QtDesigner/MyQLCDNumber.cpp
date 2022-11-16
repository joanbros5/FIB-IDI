#include "MyQLCDNumber.h"

MyQLCDNumber::MyQLCDNumber(QWidget *parent) : QLCDNumber (parent) {}

void MyQLCDNumber::suma1() {
    if (abierto) {
        ++value;
        display(value);
    }
}

void MyQLCDNumber::suma4() {
    if (abierto) {
        value += 4;
        display(value);
    }
}

void MyQLCDNumber::abre() { abierto = 1;}

void MyQLCDNumber::cierra() {abierto = 0;}
