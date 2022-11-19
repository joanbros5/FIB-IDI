#include <QLCDNumber>

class MyQLCDNumber: public QLCDNumber
{
    Q_OBJECT
    public:
        MyQLCDNumber (QWidget *parent);

        double notaLab = 0;
        double notaExParcial = 0;

    public slots:
        void calculaNotaFinal();
        
        void reset();
        
        void setParcial(double);
        void setLab(double);
};
