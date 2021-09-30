#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <chrono>
#include <random>
#include <windows.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#define dbg(x) #x << ' ' << x
#pragma optimize("03")

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine randNum(seed);

double rotate_y = 0;
double rotate_x = 0;

void add(double& a, double b) { if((a += b) >= 360) a -= 360; }
void sub(double& a, double b) { if((a -= b) < 0) a += 360; }


void drawCenter(double size, double x, double y, double z) {

    glBegin(GL_POLYGON);
 
glColor3f( 0, 1, 0 );
glVertex3f(x + 0.5 * size, y + -0.5 * size, z + -0.5 * size );
glVertex3f(x +  0.5 * size, y + 0.5 * size, z + -0.5 * size );
glVertex3f(x + -0.5 * size, y + 0.5 * size, z + -0.5 * size );
glVertex3f(x + -0.5 * size, y + -0.5 * size, z + -0.5 * size );
 
glEnd();

glBegin(GL_POLYGON);
glColor3f(  0, 0, 1 );
glVertex3f( x + 0.5 * size, y + -0.5 * size, z + 0.5 * size );
glVertex3f( x + 0.5 * size,  y + 0.5 * size, z + 0.5 * size );
glVertex3f( x + -0.5 * size,  y + 0.5 * size, z + 0.5 * size );
glVertex3f( x + -0.5 * size, y + -0.5 * size, z + 0.5 * size );
glEnd();
 
// Purple side - RIGHT
glBegin(GL_POLYGON);
glColor3f( 1,  0.0,  0 );
glVertex3f(x + 0.5 * size, y + -0.5 * size, z + -0.5 * size );
glVertex3f(x + 0.5 * size, y + 0.5 * size, z + -0.5 * size );
glVertex3f(x + 0.5 * size, y + 0.5 * size, z + 0.5 * size );
glVertex3f(x + 0.5 * size, y + -0.5 * size, z + 0.5 * size );
glEnd();
 
// Green side - LEFT
glBegin(GL_POLYGON);
glColor3f( 1,  0.4,  0.01 );
glVertex3f(x + -0.5 * size, y + -0.5 * size, z + 0.5 * size);
glVertex3f(x + -0.5 * size, y + 0.5 * size, z + 0.5 * size);
glVertex3f(x + -0.5 * size, y + 0.5 * size, z + -0.5 * size);
glVertex3f(x + -0.5 * size, y + -0.5 * size, z + -0.5 * size);
glEnd();
 
// Blue side - TOP
glBegin(GL_POLYGON);
glColor3f( 1,  1,  1.0 );
glVertex3f( x + 0.5 * size, y + 0.5 * size, z + 0.5 * size );
glVertex3f( x + 0.5 * size, y + 0.5 * size, z + -0.5 * size);
glVertex3f( x + -0.5 * size, y + 0.5 * size, z + -0.5 * size );
glVertex3f( x + -0.5 * size, y + 0.5 * size, z + 0.5 * size );
glEnd();
 
// Red side - BOTTOM
glBegin(GL_POLYGON);
glColor3f(   1,  1,  0 );
glVertex3f( x + 0.5 * size, y + -0.5 * size, z + -0.5 * size );
glVertex3f( x + 0.5 * size, y + -0.5 * size, z + 0.5 * size);
glVertex3f( x + -0.5 * size, y + -0.5 * size, z + 0.5 * size );
glVertex3f( x + -0.5 * size, y + -0.5 * size, z + -0.5 * size );
glEnd();  

  return ;
}
/*

void firstCube() {

drawCenter(0.24,0.25,0.25,0.25);
drawCenter(0.24,0.25,0.25,-0.25);
drawCenter(0.24,0.25,0.25,0);
drawCenter(0.24,0.25,-0.25,0.25);
drawCenter(0.24,0.25,-0.25,-0.25);
drawCenter(0.24,0.25,-0.25,0);
drawCenter(0.24,0.25,0,0.25);
drawCenter(0.24,0.25,0,-0.25);
drawCenter(0.24,0.25,0,0);
drawCenter(0.24,-0.25,0.25,0.25);
drawCenter(0.24,-0.25,0.25,-0.25);
drawCenter(0.24,-0.25,0.25,0);
drawCenter(0.24,-0.25,-0.25,0.25);
drawCenter(0.24,-0.25,-0.25,-0.25);
drawCenter(0.24,-0.25,-0.25,0);
drawCenter(0.24,-0.25,0,0.25);
drawCenter(0.24,-0.25,0,-0.25);
drawCenter(0.24,-0.25,0,0);
drawCenter(0.24,0,0.25,0.25);
drawCenter(0.24,0,0.25,-0.25);
drawCenter(0.24,0,0.25,0);
drawCenter(0.24,0,-0.25,0.25);
drawCenter(0.24,0,-0.25,-0.25);
drawCenter(0.24,0,-0.25,0);
drawCenter(0.24,0,0,0.25);
drawCenter(0.24,0,0,-0.25);

return ;
}

*/

struct Cube {
  double m[16];
  double x, y, z;
  Cube();
  Cube& rotate(double, double, double, double);
  void translate(double x, double y, double z) { this -> x = x; this -> y = y; this -> z = z; }
  void draw();
};

Cube::Cube() : x(0), y(0), z(0) {
    memset(m, 0, sizeof m);
    m[0] = m[5] = m[10] = m[15] = 1;
}

Cube& Cube::rotate(double theta, double x, double y, double z) {
    theta *= M_PI / 180;
    double norm = (x * x + y * y + z * z);
    x /= norm; y /= norm; z /= norm;
    double c = cos(theta);
    double s = sin(theta);
    double xy = x * y, xz = x * z, yz = y * z;
    double zs = z * s, ys = y * s, xs = x * s;
    double d = 1 - c;

    double rd[16] = { x * x * d + c, xy * d + zs,
                      xz * d - ys, 0,
                      xy * d - zs, y * y * d + c, yz + xs,
                      0, xz * d + ys,
                      yz * d - xs, z * z * d + c,
                      0, 0, 0, 0, 1
                  };
    double gr[16] = {};
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
                gr[i + 4 * j] += rd[i + 4 * k] * m[k + 4 * j];

    memcpy(m, gr, sizeof gr);
    return *this;
}

void Cube::draw() {
  glPushMatrix();
  glTranslated(x, y, z);
  glMultMatrixd(m);
  drawCenter(0.24, 0, 0, 0);
  glPopMatrix();

  return ;
}

Cube drawCube[27];

void topTurn() {
  for(int i = 0; i < 27; ++i)
    if(drawCube[i].y == 0.25) {
      drawCube[i].rotate(90, 0, 1, 0);
      if(drawCube[i].x == -0.25 && drawCube[i].z == 0.25) drawCube[i].x = 0.25;
      else if(drawCube[i].x == -0.25 && drawCube[i].z == -0.25) drawCube[i].z = 0.25;
      else if(drawCube[i].x == 0.25 && drawCube[i].z == 0.25) drawCube[i].z = -0.25;
      else if(drawCube[i].x == 0.25 && drawCube[i].z == -0.25) drawCube[i].x = -0.25;
      else if(drawCube[i].x == 0.25 && drawCube[i].z == 0) drawCube[i].x = 0, drawCube[i].z = -0.25;
      else if(drawCube[i].x == -0.25 && drawCube[i].z == 0) drawCube[i].x = 0, drawCube[i].z = 0.25;
      else if(drawCube[i].x == 0 && drawCube[i].z == -0.25) drawCube[i].x = -0.25, drawCube[i].z = 0;
      else if(drawCube[i].x == 0 && drawCube[i].z == 0.25) drawCube[i].x = 0.25, drawCube[i].z = 0;
    }

  glutPostRedisplay();

  return ;
}

void leftTurn() {
  for(int i = 0; i < 27; ++i)
    if(drawCube[i].x == -0.25) {
      drawCube[i].rotate(-90, 1, 0, 0);
      if(drawCube[i].y == -0.25 && drawCube[i].z == 0.25) drawCube[i].y = 0.25;
      else if(drawCube[i].y == -0.25 && drawCube[i].z == -0.25) drawCube[i].z = 0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].z == 0.25) drawCube[i].z = -0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].z == -0.25) drawCube[i].y = -0.25;
      else if(drawCube[i].y == 0 && drawCube[i].z == -0.25) drawCube[i].y = -0.25 , drawCube[i].z = 0;
      else if(drawCube[i].y == 0 && drawCube[i].z == 0.25) drawCube[i].y = 0.25, drawCube[i].z = 0;
      else if(drawCube[i].y == -0.25 && drawCube[i].z == 0) drawCube[i].y = 0, drawCube[i].z = 0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].z == 0) drawCube[i].y = 0, drawCube[i].z = -0.25;
    }

  glutPostRedisplay();

  return ;
}

void frontTurn() {
  for(int i = 0; i < 27; ++i)
    if(drawCube[i].z == -0.25) {
      drawCube[i].rotate(-90, 0, 0, 1);
      if(drawCube[i].y == -0.25 && drawCube[i].x == 0.25) drawCube[i].x = -0.25;
      else if(drawCube[i].y == -0.25 && drawCube[i].x == -0.25) drawCube[i].y = 0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].x == 0.25) drawCube[i].y = -0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].x == -0.25) drawCube[i].x = 0.25;
      else if(drawCube[i].y == 0 && drawCube[i].x == -0.25) drawCube[i].x = 0, drawCube[i].y = 0.25;
      else if(drawCube[i].y == 0 && drawCube[i].x == 0.25) drawCube[i].x = 0, drawCube[i].y = -0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].x == 0) swap(drawCube[i].y, drawCube[i].x);
      else if(drawCube[i].y == -0.25 && drawCube[i].x == 0) swap(drawCube[i].y, drawCube[i].x);
    }

  glutPostRedisplay();

  return ;
}

void backTurn() { 
  for(int i = 0; i < 27; ++i)
    if(drawCube[i].z == 0.25) {
      drawCube[i].rotate(90, 0, 0, 1);
      if(drawCube[i].y == -0.25 && drawCube[i].x == 0.25) drawCube[i].y = 0.25;
      else if(drawCube[i].y == -0.25 && drawCube[i].x == -0.25) drawCube[i].x = 0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].x == 0.25) drawCube[i].x = -0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].x == -0.25) drawCube[i].y = -0.25;
      else if(drawCube[i].y == 0 && drawCube[i].x == -0.25) swap(drawCube[i].x, drawCube[i].y);
      else if(drawCube[i].y == 0 && drawCube[i].x == 0.25) swap(drawCube[i].x, drawCube[i].y);
      else if(drawCube[i].y == -0.25 && drawCube[i].x == 0) drawCube[i].y = 0, drawCube[i].x = 0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].x == 0) drawCube[i].y = 0, drawCube[i].x = -0.25;
    }

  glutPostRedisplay();

  return ;
}

void bottomTurn() {
  for(int i = 0; i < 27; ++i)
    if(drawCube[i].y == -0.25) {
      drawCube[i].rotate(-90, 0, 1, 0);
      if(drawCube[i].x == -0.25 && drawCube[i].z == 0.25) drawCube[i].z = -0.25;
      else if(drawCube[i].x == -0.25 && drawCube[i].z == -0.25) drawCube[i].x = 0.25;
      else if(drawCube[i].x == 0.25 && drawCube[i].z == 0.25) drawCube[i].x = -0.25;
      else if(drawCube[i].x == 0.25 && drawCube[i].z == -0.25) drawCube[i].z = 0.25;
      else if(drawCube[i].z == 0 && drawCube[i].x == 0.25) swap(drawCube[i].x, drawCube[i].z);
      else if(drawCube[i].z == 0 && drawCube[i].x == -0.25) swap(drawCube[i].x, drawCube[i].z);
      else if(drawCube[i].z == -0.25 && drawCube[i].x == 0) drawCube[i].x = 0.25, drawCube[i].z = 0;
      else if(drawCube[i].z == 0.25 && drawCube[i].x == 0) drawCube[i].x = -0.25, drawCube[i].z = 0;
    }

  glutPostRedisplay();

  return ;
}

void rightTurn() {
  for(int i = 0; i < 27; ++i)
    if(drawCube[i].x == 0.25) {
      drawCube[i].rotate(90, 1, 0, 0);
      if(drawCube[i].y == -0.25 && drawCube[i].z == 0.25) drawCube[i].z = -0.25;
      else if(drawCube[i].y == -0.25 && drawCube[i].z == -0.25) drawCube[i].y = 0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].z == 0.25) drawCube[i].y = -0.25;
      else if(drawCube[i].y == 0.25 && drawCube[i].z == -0.25) drawCube[i].z = 0.25;
      else if(drawCube[i].y == 0 && drawCube[i].z == -0.25) drawCube[i].y = 0.25, drawCube[i].z = 0;
      else if(drawCube[i].y == 0 && drawCube[i].z == 0.25) drawCube[i].y = -0.25, drawCube[i].z = 0;
      else if(drawCube[i].y == -0.25 && drawCube[i].z == 0) swap(drawCube[i].y, drawCube[i].z);
      else if(drawCube[i].y == 0.25 && drawCube[i].z == 0) swap(drawCube[i].y, drawCube[i].z);
    }

  glutPostRedisplay();

  return ;
}


void solveCube() {

  for(int i = 0; i < 27; ++i) {
     memset(drawCube[i].m, 0, sizeof drawCube[i].m);
     drawCube[i].m[0] = drawCube[i].m[5] = drawCube[i].m[10] = drawCube[i].m[15] = 1;
  }

  int m = 0;

  const double dx[] = {0, 0.25, -0.25};

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      for(int k = 0; k < 3; ++k)
        drawCube[m++].translate(dx[i], dx[j], dx[k]);

    glutPostRedisplay();

    return ;
}

void (*fd[])() = { frontTurn, backTurn, leftTurn, rightTurn, topTurn, bottomTurn };

void randomizeCube() {

  for(int i = 0; i < 21; ++i) {
    unsigned int rx = randNum() % 6;
    fd[rx]();
    if(randNum() & 1) { fd[rx](); fd[rx]; }
  }

  return ;
}

void display(){

  glLoadIdentity();
 
glRotatef( rotate_x, 1.0, 0.0, 0.0 );
glRotatef( rotate_y, 0.0, 1.0, 0.0 );
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(int i = 0; i < 27; ++i)
    drawCube[i].draw();

 // firstCube();

glFlush();
glutSwapBuffers();

  return ;
}

void keyFunc(unsigned char key, int x, int y) {
  if(key == 27) exit(0);
  else if (key == 'h') {
    rotate_x = rotate_y = 0;
    glutPostRedisplay();
  } else if (key == 't') topTurn();
  else if(key == 'l') leftTurn();
  else if(key == 'f') frontTurn();
  else if(key == 'b') backTurn();
  else if(key == 'd') bottomTurn();
  else if(key == 'r') rightTurn();
  else if(key == 's') solveCube();
  else if(key == 'T') topTurn(), topTurn(), topTurn();
  else if(key == 'L') leftTurn(), leftTurn(), leftTurn();
  else if(key == 'F') frontTurn(), frontTurn(), frontTurn();
  else if(key == 'B') backTurn(), backTurn(), backTurn();
  else if(key == 'D') bottomTurn(), bottomTurn(), bottomTurn();
  else if(key == 'R') rightTurn(), rightTurn(), rightTurn();
  else if(key == 'S') randomizeCube();

  return ;
}

void specialKeys( int key, int x, int y ) {
 
 if(rotate_x < 90 || rotate_x > 270) {
  if (key == GLUT_KEY_RIGHT)
  sub(rotate_y, 5);
 
//  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
  add(rotate_y, 5);

 } else {

//  Right arrow - increase rotation by 5 degree
if (key == GLUT_KEY_RIGHT)
  add(rotate_y, 5);
 
//  Left arrow - decrease rotation by 5 degree
else if (key == GLUT_KEY_LEFT)
  sub(rotate_y, 5);
 }

if (key == GLUT_KEY_UP)
  add(rotate_x, 5);
 
else if (key == GLUT_KEY_DOWN)
  sub(rotate_x, 5);
 
//  Request display update
glutPostRedisplay();
 
 return ;
}

int main(int argc, char** argv) {

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(660, 660);
  glutInitWindowPosition(200, 200);

  glutCreateWindow("Hello!");
  glEnable(GL_DEPTH_TEST);

  glutKeyboardFunc(keyFunc);
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 

  int m = 0;

  const double dx[] = {0, 0.25, -0.25};

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      for(int k = 0; k < 3; ++k)
        drawCube[m++].translate(dx[i], dx[j], dx[k]);

  glutMainLoop();

  return EXIT_SUCCESS;
}