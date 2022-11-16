#include "MyGLWidget.h"

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

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST); // NOMES UN COP! En paintGL() molt incorrecte
  carregaShaders();
  createBuffers();

  rotate = 0.0f;
  scale = 1.0f;

  calculaCapsaModel();
  calculaCapsaEscena();
  calculaCentreEscnea();
  calculaRadiEscena();

  ini_camera();
}

void MyGLWidget::ini_camera ()
{
  // distancia pot ser valor qualsevol que peremti veure tota lescena
  distancia = radi * 2.0;
  Znear = distancia - radi;
  Zfar = distancia + radi;
  raw = 1.0f;
  FOV = 2.0 * asin(radi / distancia);

  OBS = glm::vec3(0,2.0,distancia);
  VRP = glm::vec3(centreEscena);
  UP = glm::vec3(0,1,0);

  projectTransform();
  viewTransform();
}

void MyGLWidget::paintGL ()
{
  glViewport (0, 0, width(), height()); // Aquesta crida no caldria perquè Qt la fa de forma automàtica amb aquests paràmetres

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (legoman) {
    glBindVertexArray(VA2_Legoman);
    modelTransformHomerProves(); // Carreguem la transformació de model (rotacio)
    glDrawArrays(GL_TRIANGLES, 0, Legoman.faces().size()*3);
  }
  else {
    glBindVertexArray(VA0_HomerProves);
    modelTransformHomerProves(); // Carreguem la transformació de model (rotacio)
    glDrawArrays(GL_TRIANGLES, 0, HomerProves.faces().size()*3);
  }

  glBindVertexArray(VA1_Terra);
  modelTransformTerra (); // Carreguem la transformació de model
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray (0);
}

void MyGLWidget::resizeGL (int w, int h)
{
    ample = w;
    alt = h;
    float rav = float(w) / float(h);
	raw = rav;
	if (rav < 1.0) FOV = 2.0*atan(tan(FOVini/2.0)/rav);
	projectTransform ();
	glViewport(0, 0, w, h);
}

void MyGLWidget::modelTransformTerra ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformHomerProves ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, rotate, glm::vec3(0.0, 1.0, 0.0));
  transform = glm::scale(transform, glm::vec3(scale));
  transform = glm::scale(transform, glm::vec3(escala));
  transform = glm::translate(transform, -centreBasePatricio);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform ()
{
    glm::mat4 Proj = glm::mat4(1.f);
    if (camOrtho == 1) Proj = glm::ortho(-radi,radi,-radi,radi, Znear, Zfar);
	if (camOrtho == 0) Proj = glm::perspective (FOV, raw, Znear, Zfar);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
	//glm::lookAt(OBS, VRP, UP);
	glm::mat4 View(1.0);
	View = glm::translate(View, glm::vec3(0., 0., -distancia));
	View = glm::rotate(View, girTheta, glm::vec3(1., 0., 0.));
	View = glm::rotate(View, -girPsi, glm::vec3(0., 1., 0.));
	View = glm::translate(View, -centreEscena);
	glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::createBuffers ()
{
  // HomerProves
  HomerProves.load("../models/Patricio.obj");

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VA0_HomerProves);
  glBindVertexArray(VA0_HomerProves);

  GLuint VB0_HomerProvesPos;
  glGenBuffers(1, &VB0_HomerProvesPos);
  glBindBuffer(GL_ARRAY_BUFFER, VB0_HomerProvesPos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*HomerProves.faces().size()*3*3,
				HomerProves.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  GLuint VB0_HomerProvesCol;
  glGenBuffers(1, &VB0_HomerProvesCol);
  glBindBuffer(GL_ARRAY_BUFFER, VB0_HomerProvesCol);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*HomerProves.faces().size()*3*3,
				HomerProves.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Legoman
  Legoman.load("../models/legoman.obj");

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VA2_Legoman);
  glBindVertexArray(VA2_Legoman);

  GLuint VB2_Legoman;
  glGenBuffers(1, &VB2_Legoman);
  glBindBuffer(GL_ARRAY_BUFFER, VB2_Legoman);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*HomerProves.faces().size()*3*3,
				Legoman.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  GLuint VB2_Legoman_Col;
  glGenBuffers(1, &VB2_Legoman_Col);
  glBindBuffer(GL_ARRAY_BUFFER, VB2_Legoman_Col);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*HomerProves.faces().size()*3*3,
				Legoman.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);


  //Terra
  glm::vec3 posicio[6] = {
	glm::vec3(2.5, 0, 2.5),
	glm::vec3(2.5, 0, -2.5),
	glm::vec3(-2.5, 0, -2.5),

	glm::vec3(2.5, 0, 2.5),
	glm::vec3(-2.5, 0, -2.5),
	glm::vec3(-2.5, 0, 2.5)
  };
   glm::vec3 color[6] = {
	glm::vec3(1,0,0),
	glm::vec3(0,0,1),
	glm::vec3(0,1,0),

	glm::vec3(1,0,0),
	glm::vec3(0,1,0),
	glm::vec3(0,0,1),
  };

  glGenVertexArrays(1, &VA1_Terra);
  glBindVertexArray(VA1_Terra);

  GLuint VB0_TerraPos;
  glGenBuffers(1, &VB0_TerraPos);
  glBindBuffer(GL_ARRAY_BUFFER, VB0_TerraPos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  GLuint VB0_TerraCol;
  glGenBuffers(1, &VB0_TerraCol);
  glBindBuffer(GL_ARRAY_BUFFER, VB0_TerraCol);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);


  glBindVertexArray (0);
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
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::calculaCapsaModel ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  if (legoman) {
      minx = maxx = Legoman.vertices()[0];
    miny = maxy = Legoman.vertices()[1];
    minz = maxz = Legoman.vertices()[2];
    for (unsigned int i = 3; i < Legoman.vertices().size(); i+=3)
    {
        if (Legoman.vertices()[i+0] < minx)
        minx = Legoman.vertices()[i+0];
        if (Legoman.vertices()[i+0] > maxx)
        maxx = Legoman.vertices()[i+0];
        if (Legoman.vertices()[i+1] < miny)
        miny = Legoman.vertices()[i+1];
        if (Legoman.vertices()[i+1] > maxy)
        maxy = Legoman.vertices()[i+1];
        if (Legoman.vertices()[i+2] < minz)
        minz = Legoman.vertices()[i+2];
        if (Legoman.vertices()[i+2] > maxz)
        maxz = Legoman.vertices()[i+2];
    }

    escala = factor/(maxy-miny);
    centreBasePatricio = glm::vec3((minx+maxx)/2, miny, (minz+maxz)/2);
    escenaMaxima.y = 4.0;
  }
  else {
    minx = maxx = HomerProves.vertices()[0];
    miny = maxy = HomerProves.vertices()[1];
    minz = maxz = HomerProves.vertices()[2];
    for (unsigned int i = 3; i < HomerProves.vertices().size(); i+=3)
    {
        if (HomerProves.vertices()[i+0] < minx)
        minx = HomerProves.vertices()[i+0];
        if (HomerProves.vertices()[i+0] > maxx)
        maxx = HomerProves.vertices()[i+0];
        if (HomerProves.vertices()[i+1] < miny)
        miny = HomerProves.vertices()[i+1];
        if (HomerProves.vertices()[i+1] > maxy)
        maxy = HomerProves.vertices()[i+1];
        if (HomerProves.vertices()[i+2] < minz)
        minz = HomerProves.vertices()[i+2];
        if (HomerProves.vertices()[i+2] > maxz)
        maxz = HomerProves.vertices()[i+2];
    }

    escala = factor/(maxy-miny);
    centreBasePatricio = glm::vec3((minx+maxx)/2, miny, (minz+maxz)/2);
    escenaMaxima.y = 4.0;
  }
}

void MyGLWidget::calculaCapsaEscena ()
{
  escenaMaxima.x = 2.5;
  escenaMaxima.z = 2.5;

  escenaMinima = glm::vec3(-2.5, 0.0, -2.5);
}

void MyGLWidget::calculaRadiEscena ()
{
  radi = distance(escenaMinima, escenaMaxima)/2.0;
}

void MyGLWidget::calculaCentreEscnea ()
{
  centreEscena = (escenaMaxima + escenaMinima);
  centreEscena = centreEscena / glm::vec3(2.0);

}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    case Qt::Key_R: {
		rotate += float(M_PI)/4.0f;
		break;
	}
    case Qt::Key_O: {
        camOrtho = !camOrtho;
        projectTransform();
        break;
    }
    default: event->ignore(); break;
  }
  viewTransform();
  projectTransform();
  update();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    girPsi -= (e->x() - x_ant) * M_PI / ample;
    girTheta -= (y_ant - e->y()) * M_PI / ample;
    viewTransform ();
  }

  x_ant = e->x();
  y_ant = e->y();

  viewTransform();
  update ();
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  x_ant = e->x();
  y_ant = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::afov(int newFOV) {
    makeCurrent();
    FOV = 90 - newFOV*0.05;
    projectTransform();
    viewTransform();
    update();
}

void MyGLWidget::modelleg(bool b) {
    makeCurrent();
    legoman = b;
    calculaCapsaModel();
    paintGL();
    update();
}

void MyGLWidget::modelpat(bool b) {
    makeCurrent();
    legoman = !b;
    calculaCapsaModel();
    paintGL();
    update();
}

void MyGLWidget::camor(bool b) {
    makeCurrent();
    camOrtho = b;
    projectTransform();
    viewTransform();
    update();
}

void MyGLWidget::campe(bool b) {
    makeCurrent();
    camOrtho = !b;
    projectTransform();
    viewTransform();
    update();
}

void MyGLWidget::aescala(int e) {
    makeCurrent();
    factor = e;
    calculaCapsaModel();
    paintGL();
    update();
}
