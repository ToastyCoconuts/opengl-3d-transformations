/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.4.0/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double xRot = 0;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
  
  for(int i = 0; i < 4; i++){ //teapots directly on x and y axis
    glPushMatrix();
    if(i%2==0){
      if(i == 0){
        glTranslatef(1, 0, 0);
      }
      else{
        glTranslatef(-1, 0, 0);
      }
    }
    else{
      if(i == 1){
        glTranslatef(0, 1, 0);
      }
      else{
        glTranslatef(0, -1, 0);
      }
    }
    glRotatef(90*(1+i), 0, 0, 1); //the rotation angles are 90, 180, 270. and 360 respective to i
    glutSolidTeapot(0.1);
    glPopMatrix();
  }
  
  for(int i = 0; i < 4; i++){ //teapots in each quadrant
    glPushMatrix();
    if(i%2==0){
      if(i == 0){
        glTranslatef(0.5, -0.5, 0);
      }
      else{
        glTranslatef(-0.5, 0.5, 0);
      }
    }
    else{
      if(i == 1){
        glTranslatef(0.5, 0.5, 0);
      }
      else{
        glTranslatef(-0.5, -0.5, 0);
      }
    }    
    glRotatef(i*(90)+45, 0, 0, 1); //the rotation angles are 45, 135, 225, and 315 respective to i
    glutSolidTeapot(0.1);
    glPopMatrix();
  }
}

void problem2() {
  
  glEnable(GL_NORMALIZE); //to deal with shadow issue
  for(int i = 0; i < 12; i++){    
    for(int j = 0; j <= i; j++){    
      glPushMatrix();
      glScalef(0.5*j-(0.5*i), 0.25, 0.5*j-(0.5*i));
      glTranslatef(0, 0.5*j, 0);
      glutSolidCube(0.5);
      glPopMatrix();
    }
  }
}

void problem3() {

  for(int i = 0;  i < 6; i++){
    float row = (6 - i - 1) * 0.5;
    float x = -1.5+ i * 0.3;
    for(int j = 0; j < 6 - i; j++){
      glPushMatrix();
      glTranslatef(x + j * 0.6, -i * 0.45 + 1, 0.0);
      glutSolidTeapot(0.2);
      glPopMatrix();
    }
  }
}

void problem4() {
  float rotation = 0.0;
  float currentAngle = 0.0;

  glTranslatef(0.0, 0.0, -5.0);
  
  for (int i = 0; i < 20; i++) {
    glPushMatrix(); 
      
    glRotatef(currentAngle + rotation, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    //smaller spiral
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    glPushMatrix();
    //larger spiral offset to create triangular spaces
    glTranslatef(0.5, 0.5, 0.0);
    //larger spiral
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(0.0, 2.0);
    glEnd();
      
    glPopMatrix(); 
    glPopMatrix();
    currentAngle += (360.0/20);
  }
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
    glEnd(/*GL_LINES*/);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    if (curProblem == 1) problem1();
    if (curProblem == 2) problem2();
    if (curProblem == 3) problem3();
    if (curProblem == 4) problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
    if (leftDown) {
        xRot += (y - lastPos[1]) * .1;
        yRot += (x - lastPos[0]) * .1;
    }
    if (rightDown) {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
    }


    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    curProblem = key - '0';
    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("HW2");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
