#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    virtual void keyPressEvent (QKeyEvent *e);
    virtual void modelTransform ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

  private:
    void creaBuffers ();
    void carregaShaders ();
    
    // attribute locations
    GLuint vertexLoc, sclLoc, transLoc;
    
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1;
    GLint ample, alt;
    float scl = 1.0;
    float tx = 0.0, ty = 0.0, tz = 0.0, ry = 0.0, rx = 0.0, rz = 0.0, sx = 1.0, sy = 1.0, sz = 1.0;
};
