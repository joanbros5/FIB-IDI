#include "MyQDoubleSpinBox.h"

MyQDoubleSpinBox::MyQDoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox(parent) {      
        // Inicialitzaci√≥ d'atributs si cal
    } 
    
    void MyQDoubleSpinBox::reset() {
        setValue(0);
    }
