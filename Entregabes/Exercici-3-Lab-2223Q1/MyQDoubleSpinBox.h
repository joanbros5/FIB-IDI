#include <QDoubleSpinBox>

class MyQDoubleSpinBox: public QDoubleSpinBox
{    
    Q_OBJECT 
    public:   
        MyQDoubleSpinBox (QWidget *parent);
        
    public slots:

        void reset();
};
