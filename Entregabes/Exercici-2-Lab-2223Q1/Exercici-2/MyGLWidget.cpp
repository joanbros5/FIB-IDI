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

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glEnable(GL_DEPTH_TEST);
  
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersModels();
  creaBuffersTerra();
  iniEscena();
  iniCamera();
}

void MyGLWidget::iniEscena()
{
  radiEscena = sqrt(334)/2;
  centreEscena = glm::vec3(0,1.5,0);
}

void MyGLWidget::iniCamera(){

  distancia = 2*radiEscena;
  fov = 2 * glm::asin(radiEscena/distancia);
  zfar  = distancia + radiEscena;
  
  if (POV == 0) {
    znear =  distancia - radiEscena;
  }
  else {
    znear = 0.25;
  }
  
  factorAngleX = glm::radians(45.);
  factorAngleY = 0;

  viewTransform();
  projectTransform();
}

void MyGLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Rick
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  //Morty Alter
  if (morty2) {
    
    MortyAlterTransform();
    
    glUniform1i(alterLoc, 1);
    glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
    glUniform1i(alterLoc, 0);
  }
  
  //Portal
  if (portalObert) pintaPortal();  
  
  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::pintaPortal() {
  glBindVertexArray (VAO_models[PORTAL]);
  PortalTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[PORTAL].faces().size()*3);
}

void MyGLWidget::RickTransform ()
{
  glm::mat4 TG(1.0f);  
  TG = glm::translate(TG, glm::vec3(-2.5, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
  TG = glm::rotate(TG, RotRick * glm::radians(45.f), glm::vec3(0.0,1.0,0.0));
  TG = glm::rotate(TG, glm::radians(180.0f), glm::vec3(0.0,1.0,0.0));
  TG = glm::translate(TG, -centreBaseModels[RICK]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::PortalTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(-2.5,0,0));
  TG = glm::rotate(TG, RotPortal * glm::radians(45.f), glm::vec3(0.0,1.0,0.0));
  TG = glm::translate(TG, glm::vec3(0,0,3.0));
  TG = glm::scale(TG, glm::vec3(0.25,escalaModels[PORTAL],escalaModels[PORTAL]));
  TG = glm::translate(TG, -centreBaseModels[PORTAL]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posMorty);
  TG = glm::rotate(TG, RotMorty * glm::radians(45.f), glm::vec3(0.0,1.0,0.0));
  TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
  TG = glm::translate(TG, -centreBaseModels[MORTY]);
  TGMorty = TG;
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyAlterTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posMorty2);
  TG = glm::rotate(TG, RotMorty2 * glm::radians(45.f), glm::vec3(0.0,1.0,0.0));
  TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
  TG = glm::translate(TG, -centreBaseModels[MORTY]);
  TGMorty = TG;
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::portalTest() {
  if (portalObert && LL2GLWidget::MortyPortalTest(RotPortal * glm::radians(45.f), posMorty)) {
    
    //Tanca portal i crea MortyAlter
    portalObert = 0;
    morty2 = 1;
    
    //Reinicia el morty Alter
    posMorty2 = glm::vec3(1,0,0);;
    RotMorty2 = 0;
    
  }
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj(1.0f);
  Proj = glm::perspective (fov, ra, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
  if (POV == 1) {
    
    glm::mat4 View(1.0);
	View = glm::translate(View, glm::vec3(0., -0.8, 0.0));
	View = glm::rotate(View, -(RotMorty + 4)*glm::radians(45.f), glm::vec3(0., 1., 0.));
	View = glm::translate(View, -posMorty);
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else {
    glm::mat4 View(1.0);
	View = glm::translate(View, glm::vec3(0., 0., -distancia));
	View = glm::rotate(View, factorAngleX, glm::vec3(1., 0., 0.));
	View = glm::rotate(View, factorAngleY, glm::vec3(0., 1., 0.));
	View = glm::translate(View, -centreEscena);
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
    
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { 
      //Morty Original
      if (RotMorty % 8 == 0) {
          posMorty += glm::vec3(0,0,0.1);
      }
      else if (RotMorty % 8 == 1) {
          posMorty += glm::vec3(0.1,0,0.1);
      }
      else if (RotMorty % 8 == 2) {
        posMorty += glm::vec3(0.1,0,0.0);
      }
      else if (RotMorty % 8 == 3) {
          posMorty += glm::vec3(0.1,0,-0.1);
      }
      else if (RotMorty % 8 == 4) {
        posMorty += glm::vec3(0,0,-0.1);
      }
      else if (RotMorty % 8 == 5) {
          posMorty += glm::vec3(-0.1,0,-0.1);
      }
      else if (RotMorty % 8 == 6) {
        posMorty += glm::vec3(-0.1,0,0);
      }
      else if (RotMorty % 8 == 7){
          posMorty += glm::vec3(-0.1,0,0.1);
      }
      
      //Morty Alternatiu
      if (RotMorty2 % 8 == 0) {
          posMorty2 += glm::vec3(0,0,0.1);
      }
      else if (RotMorty2 % 8 == 1) {
          posMorty2 += glm::vec3(0.1,0,0.1);
      }
      else if (RotMorty2 % 8 == 2) {
        posMorty2 += glm::vec3(0.1,0,0.0);
      }
      else if (RotMorty2 % 8 == 3) {
          posMorty2 += glm::vec3(0.1,0,-0.1);
      }
      else if (RotMorty2 % 8 == 4) {
        posMorty2 += glm::vec3(0,0,-0.1);
      }
      else if (RotMorty2 % 8 == 5) {
          posMorty2 += glm::vec3(-0.1,0,-0.1);
      }
      else if (RotMorty2 % 8 == 6) {
        posMorty2 += glm::vec3(-0.1,0,0);
      }
      else if (RotMorty2 % 8 == 7){
          posMorty2 += glm::vec3(-0.1,0,0.1);
      }
      
      portalTest();
      break;
    }
    case Qt::Key_Down: {
      //Morty Original
      if (RotMorty % 8 == 0) {
          posMorty -= glm::vec3(0,0,0.1);
      }
      else if (RotMorty % 8 == 1) {
          posMorty -= glm::vec3(0.1,0,0.1);
      }
      else if (RotMorty % 8 == 2) {
        posMorty -= glm::vec3(0.1,0,0.0);
      }
      else if (RotMorty % 8 == 3) {
          posMorty -= glm::vec3(0.1,0,-0.1);
      }
      else if (RotMorty % 8 == 4) {
        posMorty -= glm::vec3(0,0,-0.1);
      }
      else if (RotMorty % 8 == 5) {
          posMorty -= glm::vec3(-0.1,0,-0.1);
      }
      else if (RotMorty % 8 == 6) {
        posMorty -= glm::vec3(-0.1,0,0);
      }
      else if (RotMorty % 8 == 7){
          posMorty -= glm::vec3(-0.1,0,0.1);
      }
      
      //Morty alternatiu
      if (RotMorty2 % 8 == 0) {
          posMorty2 -= glm::vec3(0,0,0.1);
      }
      else if (RotMorty2 % 8 == 1) {
          posMorty2 -= glm::vec3(0.1,0,0.1);
      }
      else if (RotMorty2 % 8 == 2) {
        posMorty2 -= glm::vec3(0.1,0,0.0);
      }
      else if (RotMorty2 % 8 == 3) {
          posMorty2 -= glm::vec3(0.1,0,-0.1);
      }
      else if (RotMorty2 % 8 == 4) {
        posMorty2 -= glm::vec3(0,0,-0.1);
      }
      else if (RotMorty2 % 8 == 5) {
          posMorty2 -= glm::vec3(-0.1,0,-0.1);
      }
      else if (RotMorty2 % 8 == 6) {
        posMorty2 -= glm::vec3(-0.1,0,0);
      }
      else if (RotMorty2 % 8 == 7){
          posMorty2 -= glm::vec3(-0.1,0,0.1);
      }
      
      portalTest();
      break;
    }
    case Qt::Key_Left: {
        ++RotMorty;
        ++RotMorty2;
        break;
    }
    case Qt::Key_Right: {
        --RotMorty;
        if (RotMorty < 0) RotMorty = 8 + RotMorty;
        --RotMorty2;
        if (RotMorty2 < 0) RotMorty2 = 8 + RotMorty2;
        break;
    }
    case Qt::Key_Q: {
        RotRick = (RotRick + 1) % 8;
        break;
    }
    case Qt::Key_E: {
        RotRick = (RotRick - 1) % 8;
        break;
    }
    case Qt::Key_P: {
        if (RotRick == RotPortal - 4) portalObert = !portalObert;
        else { 
            portalObert = 1;
            RotPortal = RotRick + 4;
        }
        
        if (portalObert) portalTest();
        
        break;
    }
    case Qt::Key_C: {
      POV = !POV;
      if (POV == 0) {
        znear =  distancia - radiEscena;
      }
      else {
        znear = 0.25;
      }
      break;
    }
    case Qt::Key_R: {
        iniCamera();
        factorAngleX = glm::radians(45.);
        RotRick = 0;
        RotPortal = 4;
        RotMorty = 0;
        RotMorty2 = 0;
        angleMorty = 0;
        posMorty = glm::vec3(1,0,0);
        posMorty2 = glm::vec3(1,0,0);
        morty2 = 0;
        portalObert = 1;
        POV = 0;
        
        break;
    }
    default: event->ignore(); break;
  }
  
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    factorAngleY += (e->x() - xClick) * M_PI / 180.0;
    factorAngleX -= (yClick - e->y()) * M_PI / 180.0;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
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

  // Identificador per als  atributs
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");

  // Identificadors dels uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc  = glGetUniformLocation (program->programId(), "Proj");
  viewLoc  = glGetUniformLocation (program->programId(), "View");
  
  alterLoc = glGetUniformLocation (program->programId(), "alter");
}
