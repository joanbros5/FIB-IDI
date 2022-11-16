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

    //Nueva función
void MyGLWidget::paintGL(){
    // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();

  // Activem el VAO per a pintar la caseta
  glBindVertexArray (VAO_Homer);

  // pintem
  glDrawArrays (GL_TRIANGLES, 0, m.faces ().size () * 3);

  glBindVertexArray (0);
}


    //Nueva función
void MyGLWidget::creaBuffers() {
    m.load("../models/HomerProves.obj");

    glGenVertexArrays(1, &VAO_Homer);
    glBindVertexArray(VAO_Homer);

    GLuint VBO_Homer[2];
    glGenBuffers(2, VBO_Homer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);
}

void MyGLWidget::carregaShaders() {
    BL2GLWidget::carregaShaders();
    
    //Nueva líena
    inicamera();
    
    projLoc = glGetUniformLocation (program-> programId(), "proj");
    viewLoc = glGetUniformLocation (program-> programId(), "view");
    
    projectTransform();
    viewTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    }
    case Qt::Key_R: { // escalar a més petit
      ry += M_PI/4;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::modelTransform () {
    glm::mat4 TG (1.0);   // Matriu de transformació, inicialment identitat
    TG = glm::translate (TG, glm::vec3 (tx, ty, tz));
    TG = glm::rotate (TG, rx,  glm::vec3 (1.0,0.0,0.0));
    TG = glm::rotate (TG, ry,  glm::vec3 (0.0,1.0,0.0));
    TG = glm::rotate (TG, rz,  glm::vec3 (0.0,0.0,1.0));
    TG = glm::scale (TG, glm::vec3 (escala, escala, escala));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform () {
    glm::mat4 Proj = glm::perspective (alpha, raw, Znear, Zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()  {
    glm::mat4 View = glm::lookAt (OBS, VRP, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::inicamera() {
    
    glEnable (GL_DEPTH_TEST);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Projection Matrix
    alpha = float(M_PI)/2.0f;
    raw = 1.0f;
    Znear = 0.4f;
    Zfar = 3.0f;
    
    //View Matrix
    OBS = glm::vec3(0,0,1);
    VRP = glm::vec3(0,0,0);
    up = glm::vec3(0,1,0);
}


