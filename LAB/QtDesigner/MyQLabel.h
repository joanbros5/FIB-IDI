#include <QLabel>

class MyQLabel: public QLabel
{    
    Q_OBJECT 
    public:   
        MyQLabel (QWidget *parent);
        
        QString textito;
        int mida;
        int abierto = 1;
        
    public slots:
        void truncatext(int);
        
        void GuardaGuarda(QString);

        void PUTOROJO();

        void abre();
        void cierra();
};
