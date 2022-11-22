// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

    virtual void initializeGL();
    virtual void carregaShaders_nuevos();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra ();

  private:
    int printOglError(const char file[], int line, const char func[]);

    //Posició i color del focus (Vectors i Uniforms pel vertex shader)
    glm::vec3 posFocus;
    glm::vec3 colFocus;
    GLuint posFocusLoc, colFocusLoc;
};
