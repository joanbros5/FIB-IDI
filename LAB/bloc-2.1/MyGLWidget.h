// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    
    //Nuevas declaraciones
    virtual void creaBuffers();
    virtual void paintGL();
    virtual void keyPressEvent (QKeyEvent* event);
    virtual void modelTransform();
    
    virtual void carregaShaders();
    virtual void projectTransform (); 
    virtual void viewTransform ();  
    GLuint projLoc;
    GLuint viewLoc;
    
    //Ejercicio 2.2
    void inicamera();
    float Znear, Zfar, raw, alpha;
    glm::vec3 OBS, VRP, up;
    
    //Nuevas declaraciones
    Model m;
    GLuint VAO_Homer;

    float tx = 0.0, ty = 0.0, tz = 0.0, ry = 0.0, rx = 0.0, rz = 0.0;
};
