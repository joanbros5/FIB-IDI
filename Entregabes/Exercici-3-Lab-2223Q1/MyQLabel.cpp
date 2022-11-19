#include "MyQLabel.h"
#include <cmath>

MyQLabel::MyQLabel(QWidget *parent)
    : QLabel(parent) {      
        // Inicialització d'atributs si cal
    } 
    // implementació slots
    void MyQLabel::calculaNotaFinal() { 
        
        if (notaLab >= 4.5) {
            notaFinal = qMin(10.0,(notaExParcial*0.25) + (notaLab + (pow(entregables/4,2.2)))*0.25 + (notaExFinal*0.5));
        }
        
        else {
            notaFinal = qMin(10.0,(notaExParcial*0.25) + (notaLab)*0.25 + (notaExFinal*0.5));
        }
        
        if (notaFinal >= 5) setStyleSheet("QLabel {color : green;}");
        else setStyleSheet("QLabel {color : red;}");
        
        setNum(round(notaFinal*100)/100);
    }
    
    void MyQLabel::setParcial(double x) {
        notaExParcial = x;
        
        calculaNotaFinal();
    }
    
    void MyQLabel::setFinal(double x) {
        notaExFinal = x;
        
        calculaNotaFinal();
    }
    
    void MyQLabel::setLab(double x) {
        notaLab = x;
        
        calculaNotaFinal();
    }
    
    void MyQLabel::calculaEntregables(bool b) {
        
        if (b) ++entregables;
        else --entregables;
        
        calculaNotaFinal();
    }
    
    void MyQLabel::reset() {
        notaFinal = 0;
        notaLab = 0;
        notaExParcial = 0;
        notaExFinal = 0;
        entregables = 0;
        
        calculaNotaFinal();
    }
    
    
    
    
    
