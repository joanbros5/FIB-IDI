#include "MyQDoubleSpinBox.h"

MyQDoubleSpinBox::MyQDoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox(parent) {      
        // Inicialització d'atributs si cal
    } 
    
    void MyQDoubleSpinBox::reset() {
        setValue(0);
    }
