#include "MyLineEdit.h"
// constructor
MyLineEdit::MyLineEdit(QWidget *parent)
    : QLineEdit(parent) {      
        connect(this,SIGNAL(returnPressed()),this,SLOT(tractaReturn()));
        // Inicialitzaci√≥ d'atributs si cal
    } 
    // implementaci√≥ slots
    void MyLineEdit::tractaReturn() {  
        // Implementaci√≥ de tractaReturn    
        emit returnPressed (text());
    }
