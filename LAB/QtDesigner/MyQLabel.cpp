#include "MyQLabel.h"

MyQLabel::MyQLabel(QWidget *parent)
    : QLabel(parent) {      
        connect(this,SIGNAL(valueChanged(int)),this,SLOT(truncatext(int x)));
        // Inicialització d'atributs si cal
    } 
    // implementació slots
    void MyQLabel::truncatext(int x) {  
        // Implementació de truncatext 
        mida = x;
        QString aux = textito;
        aux.truncate(mida);
        emit setText(aux);
    }
    
    void MyQLabel::GuardaGuarda(QString text) {
        textito = text;
        text.truncate(mida);
        emit setText(text);
    }

    void MyQLabel::PUTOROJO() {
        setStyleSheet("QLabel { background-color : red;}");
    }

     void MyQLabel::abre() {
        abierto = 1;

        setStyleSheet("QLabel { background-color : green;}");
        emit setText("OPEN");


    }

    void MyQLabel::cierra() {
        abierto = 0;

        setStyleSheet("QLabel { background-color : red;}");
        emit setText("CLOSED");
    }
