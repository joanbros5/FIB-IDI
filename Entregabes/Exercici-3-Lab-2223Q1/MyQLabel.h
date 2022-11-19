#include <QLabel>

class MyQLabel: public QLabel
{    
    Q_OBJECT 
    public:   
        MyQLabel (QWidget *parent);
        
        double notaFinal = 0;
        double notaLab = 0;
        double notaExParcial = 0;
        double notaExFinal = 0;
        double entregables = 0;
        
    public slots:

        void calculaNotaFinal();
        
        void reset();
        
        void setParcial(double);
        void setFinal(double);
        void setLab(double);
        void calculaEntregables(bool);
};
