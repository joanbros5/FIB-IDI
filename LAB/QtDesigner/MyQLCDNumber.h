#include <QLCDNumber>

class MyQLCDNumber: public QLCDNumber
{
    Q_OBJECT
    public:
        MyQLCDNumber (QWidget *parent);

        int value = 0;
        bool abierto = 1;

    public slots:
        void suma1();
        void suma4();

        void abre();
        void cierra();
};
