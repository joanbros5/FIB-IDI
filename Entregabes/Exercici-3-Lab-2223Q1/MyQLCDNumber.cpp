#include "MyQLCDNumber.h"

MyQLCDNumber::MyQLCDNumber(QWidget *parent) : QLCDNumber (parent) {}

void MyQLCDNumber::calculaNotaFinal() {
    
    //5 = notaExPacial*0.25 + notaLab*0.25 + NotaExFinal*0.5
    
    display((5-(notaExParcial*0.25)-(notaLab*0.25))*2.);
}

void MyQLCDNumber::setParcial(double x) {
    notaExParcial = x;
    
    calculaNotaFinal();
}

void MyQLCDNumber::setLab(double x) {
    notaLab = x;
    
    calculaNotaFinal();
}

void MyQLCDNumber::reset() { 
    notaLab = 0;
    notaExParcial = 0;
    
    calculaNotaFinal();
}
