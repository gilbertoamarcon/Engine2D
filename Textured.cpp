#include "Textured.h"

Textured::Textured(){
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->r = 0;
};

Textured::~Textured(){};

void Textured::init(double x,double y,double w,double h,double r,char* imagePath){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	loadGLTextures(imagePath);
};

void Textured::update(double x,double y,double w,double h,double r){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
};

void Textured::loadGLTextures(char* imagePath){
    vector<unsigned char> image;
    unsigned width;
    unsigned height;
    decode(image,width,height,imagePath);
    glGenTextures(2, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
};

void Textured::render(){
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glColor3f(1.0,1.0,1.0);
            glBindTexture(GL_TEXTURE_2D,texture[0]);
            glTranslatef(-x,-y,0);
            glScalef(w,h,1);
            glRotatef(r,0,0,1);
            glRotatef(180,0,0,1);
            glTranslatef(-0.5,-0.5,0);
            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(0,0);
                glTexCoord2f(0,1);
                glVertex2f(0,1);
                glTexCoord2f(1,1);
                glVertex2f(1,1);
                glTexCoord2f(1,0);
                glVertex2f(1,0);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
};
