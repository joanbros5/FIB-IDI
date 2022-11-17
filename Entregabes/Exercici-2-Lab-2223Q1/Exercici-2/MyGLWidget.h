#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();
    
    virtual void initializeGL();
    
    virtual void iniCamera();
    virtual void iniEscena();
    
    virtual void paintGL();
    void pintaPortal();
    
    virtual void RickTransform();
    virtual void PortalTransform();
    virtual void MortyTransform();
    void MortyAlterTransform();
    
    virtual void projectTransform();
    virtual void viewTransform();
    
    virtual void keyPressEvent(QKeyEvent* event);
    
    virtual void mousePressEvent (QMouseEvent *e);
    virtual void mouseReleaseEvent( QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *e);
    
    void portalTest();
    
    virtual void carregaShaders();
    
    float distancia;
    
    int RotRick = 0, RotMorty = 0, RotMorty2 = 0;
    int RotPortal = 4;
    
    glm::vec3 posMorty2 = glm::vec3(1,0,0);
    
    //Bools
    int portalObert = 1;
    int POV = 0;
    int morty2 = 0;
    
    GLint alterLoc;

  private:

    int printOglError(const char file[], int line, const char func[]);
    
};
