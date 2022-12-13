// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL() {
    BL3GLWidget::initializeGL();

    carregaShaders_nuevos();

    posFocus = glm::vec3(0.0, -0.5, 0.0);
    glUniform3fv(posFocusLoc, 1, &posFocus[0]);

    colFocus = glm::vec3(0.8, 0.8, 0.8);
    glUniform3fv(colFocusLoc, 1, &colFocus[0]);

    posFocus2 = glm::vec3(0, 0, 0);
    glUniform3fv(posFocus2Loc, 1, &posFocus2[0]);

    colFocus2 = glm::vec3(0.8, 0.8, 0.8);
    glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);
    
    focusEsc = 1;
    glUniform1i(focusEscenaLoc, focusEsc);
    
    posPat = glm::vec3(0.0,-0.85,0.0);

    iniEscena();
    iniCamera();

}

void MyGLWidget::iniMaterialTerra ()
{
  // Donem valors al material del terra
  amb = glm::vec3(0,0,0.2);
  diff = glm::vec3(0,0,0.8);
  spec = glm::vec3(0,0,1.0);
  shin = 100;
}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::translate(glm::mat4(1.f), posPat);
  TG = glm::scale(TG, glm::vec3(escala*(0.3/2.0), escala*(0.3/2.0), escala*(0.3/2.0)));
  TG = glm::translate(TG, -centrePatr);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY -= (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_K:
        if (focusEsc) {
            posFocus.x -= 0.3;
            glUniform3fv(posFocusLoc, 1, &posFocus[0]);
        }
        break;
    case Qt::Key_L:
        if (focusEsc) {
            posFocus.x += 0.3;
            glUniform3fv(posFocusLoc, 1, &posFocus[0]);
        }
        break;
    case Qt::Key_F:
        focusEsc = !focusEsc;
        glUniform1i(focusEscenaLoc, focusEsc);
        break;

    case Qt::Key_Up:
        if (focusEsc) {
            posFocus.z += 0.3;
            glUniform3fv(posFocusLoc, 1, &posFocus[0]);
        }
        posPat.z += 0.3;
        modelTransformPatricio();
        break;

    case Qt::Key_Down:
        if (focusEsc) {
            posFocus.z -= 0.3;
            glUniform3fv(posFocusLoc, 1, &posFocus[0]);
        }
        posPat.z -= 0.3;
        modelTransformPatricio();
        break;

    case Qt::Key_Left:
        if (focusEsc) {
            posFocus.x += 0.3;
            glUniform3fv(posFocusLoc, 1, &posFocus[0]);
        }
        posPat.x += 0.3;
        modelTransformPatricio();
        break;

    case Qt::Key_Right:
        if (focusEsc) {
            posFocus.x -= 0.3;
            glUniform3fv(posFocusLoc, 1, &posFocus[0]);
        }
        posPat.x -= 0.3;
        modelTransformPatricio();
        break;

    case Qt::Key_1:
        //Si está apagado que se encienda
        if (colFocus == glm::vec3(0.0,0.0,0.0)) colFocus = glm::vec3(0.8, 0.8, 0.8);
        //Si está blanco que se vuelva amarillo
        else if (colFocus == glm::vec3(0.8,0.8,0.8)) colFocus = glm::vec3(0.8, 0.8, 0.0);
        //Si está amarillo que se apague
        else colFocus = glm::vec3(0.0,0.0,0.0);

        glUniform3fv(colFocusLoc, 1, &colFocus[0]);
        break;

    case Qt::Key_2:
        if (colFocus2 == glm::vec3(0.0,0.0,0.0)) colFocus2 = glm::vec3(0.8, 0.8, 0.8);
        else colFocus2 = glm::vec3(0.0, 0.0, 0.0);
        glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);
        break;

    case Qt::Key_B:
        bfc = !bfc;

        if (bfc) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);

        break;

    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::carregaShaders_nuevos() {

    //NO LLAMAR A ESTO
    //BL3GLWidget::carregaShaders();

    posFocusLoc = glGetUniformLocation (program->programId(), "posFocus");
    colFocusLoc = glGetUniformLocation (program->programId(), "colorFocus");
    posFocus2Loc = glGetUniformLocation (program->programId(), "posFocus2");
    colFocus2Loc = glGetUniformLocation (program->programId(), "colorFocus2");
    focusEscenaLoc = glGetUniformLocation (program->programId(), "focusEscena");
}
