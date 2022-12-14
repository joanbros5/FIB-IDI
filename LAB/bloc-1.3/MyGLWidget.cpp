
//#include <GL/glew.h>
#include "MyGLWidget.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
}

void MyGLWidget::paintGL ()
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer
  
  modelTransform ();
  // Activem l'Array a pintar 
  glBindVertexArray(VAO1);
 
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  ample = w;
  alt = h;
}

void MyGLWidget::creaBuffers ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.0, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::keyPressEvent (QKeyEvent *e) {
    makeCurrent ();
    switch (e->key())  {
        //Mover
        case  Qt::Key_Up :
            ty += 0.1;
            break;
        case  Qt::Key_Down :
            ty -= 0.1;
            break;
        case  Qt::Key_Left :
            tx -= 0.1;
            break;
        case  Qt::Key_Right :
            tx += 0.1;
            break;
            
        //Rotar
        case  Qt::Key_A :
            ry += M_PI/16;
            break;
        case  Qt::Key_D :
            ry -= M_PI/16;
            break;
        case  Qt::Key_W :
            rx += M_PI/16;
            break;
        case  Qt::Key_S :
            rx -= M_PI/16;
            break;
        case  Qt::Key_Q :
            rz += M_PI/16;
            break;
        case  Qt::Key_E :
            rz -= M_PI/16;
            break;
            
        //Escalar
        case Qt::Key_P :
            sx += 0.05;
            sy += 0.05;
            sz += 0.05;
            break;
        case Qt::Key_O :
            sx -= 0.05;
            sy -= 0.05;
            sz -= 0.05;
            break;
        
        //Reset
        case Qt::Key_R :
            tx = 0.0;
            ty = 0.0;
            tz = 0.0;
            ry = 0.0;
            rx = 0.0;
            rz = 0.0;
            sx = 1.0;
            sy = 1.0;
            sz = 1.0;
            scl = 1.0;
            break;
        default: e->ignore ();   //   propagar al pare
    } 
    update ();
}

void MyGLWidget::modelTransform () {
    glm::mat4 TG (1.0);   // Matriu de transformació, inicialment identitat
    TG = glm::translate (TG, glm::vec3 (tx, ty, tz));
    TG = glm::rotate (TG, rx,  glm::vec3 (1.0,0.0,0.0));
    TG = glm::rotate (TG, ry,  glm::vec3 (0.0,1.0,0.0));
    TG = glm::rotate (TG, rz,  glm::vec3 (0.0,0.0,1.0));
    TG = glm::scale (TG, glm::vec3 (sx, sy, sz));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  sclLoc = glGetUniformLocation (program-> programId (), "scl");
  glUniform1f (sclLoc, scl);
  transLoc = glGetUniformLocation (program-> programId(), "TG");
}
