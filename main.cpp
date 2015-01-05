#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "wtypes.h"
#include <iomanip>
#include <cmath>

// Video Parameters
#define WINDOW_TITLE    "Video"
#define FULL_SCREEN     1
#define FRAME_TIME      10

// Camera Parameters
#define VIEW_W          160
#define VIEW_H          90

// Keyboard Commands
#define EXIT            27
#define MOVE_FORTH      'w'
#define MOVE_BACK       's'
#define MOVE_LEFT       'a'
#define MOVE_RIGHT      'd'

using namespace std;

double mouse_x      = 0;
double mouse_y      = 0;

// Screen Resolution
int window_h        = 0;
int window_v        = 0;


// Camera position/motion
double view_x       = 0;
double view_y       = 0;
double x_min        = 0;
double x_max        = 0;
double y_min        = 0;
double y_max        = 0;
double cam_speed    = 0.5;

// User input flags
int moveLeft        = 0;
int moveRight       = 0;
int moveBack        = 0;
int moveForth       = 0;

void getScreenResolution(int& h, int& v);

void iniGl();

void mouseMove(int x, int y);

void mouseAction( int x, int y);

void glutMouseFunc(int button, int state, int x, int y);

void keyPressed(unsigned char key, int x, int y);

void keyReleased(unsigned char key, int x, int y);

void updateValues(int n);

void RenderScene();

int main(int argc, char **argv){

    getScreenResolution(window_h,window_v);

    glutInit(&argc, argv);

    iniGl();

    glutMainLoop();

    return 0;
}

// Get the horizontal and vertical screen sizes in pixel
void getScreenResolution(int& h, int& v){

    RECT desktop;

    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();

    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    h   = desktop.right;
    v   = desktop.bottom;
}

void iniGl(){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(window_h,window_v);
    glutCreateWindow(WINDOW_TITLE);
    glutMotionFunc(&mouseAction);
    glutPassiveMotionFunc(&mouseMove);
    glutKeyboardFunc(&keyPressed);
    glutKeyboardUpFunc(&keyReleased);
    glutDisplayFunc(&RenderScene);
    glutIdleFunc(&RenderScene);
    glutTimerFunc(1,updateValues,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(x_min,x_max,y_min,y_max);
    if (FULL_SCREEN)
        glutFullScreen();
}

// Updates the last free mouse position
void mouseMove(int x, int y){
    mouse_x = x;
    mouse_y = y;
}

void mouseAction( int x, int y){
    view_x +=  VIEW_W*((double)(mouse_x-x)/window_h);
    view_y += -VIEW_H*((double)(mouse_y-y)/window_v);
    mouse_x = x;
    mouse_y = y;
}

void keyPressed(unsigned char key, int x, int y){
    switch (key){
        case EXIT:
            exit(0);
            break;
        case MOVE_LEFT:
            moveLeft = 1;
            break;
        case MOVE_RIGHT:
            moveRight = 1;
            break;
        case MOVE_BACK:
            moveBack = 1;
            break;
        case MOVE_FORTH:
            moveForth = 1;
            break;
        default:
            break;
    }
}

void keyReleased(unsigned char key, int x, int y){
    switch (key){
        case MOVE_LEFT:
            moveLeft = 0;
            break;
        case MOVE_RIGHT:
            moveRight = 0;
            break;
        case MOVE_BACK:
            moveBack = 0;
            break;
        case MOVE_FORTH:
            moveForth = 0;
            break;
        default:
            break;
    }
}

void updateValues(int n){

    // Frame limiter
    glutTimerFunc(FRAME_TIME,updateValues,0);

    // Moving the camera given the camera speed
    if(moveLeft)
        view_x -= cam_speed;
    if(moveRight)
        view_x += cam_speed;
    if(moveBack)
        view_y -= cam_speed;
    if(moveForth)
        view_y += cam_speed;

    // Updating camera projection parameters
    x_min = view_x - VIEW_W/2;
    x_max = view_x + VIEW_W/2;
    y_min = view_y - VIEW_H/2;
    y_max = view_y + VIEW_H/2;
}

void RenderScene(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(x_min,x_max,y_min,y_max);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0,0);
            glVertex2f(0,5);
            glVertex2f(5,5);
            glVertex2f(5,0);
        glEnd();

        glPushMatrix();
            glTranslatef(1,1,0);
            glColor3f(0.0,1.0,0.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(0,0);
                glVertex2f(0,7);
                glVertex2f(7,7);
            glEnd();
        glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}
