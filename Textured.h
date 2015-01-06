#ifndef TEXTURED_H
#define TEXTURED_H
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "lodepng.h"

using namespace std;
using namespace lodepng;

class Textured{
    private:
        unsigned int texture[1];
        void loadGLTextures(char* imagePath);
    public:
        double x;
        double y;
        double w;
        double h;
        double r;
        Textured();
        virtual ~Textured();
		void init(double x,double y,double w,double h,double r,char* imagePath);
		void update(double x,double y,double w,double h,double r);
		void render();
};

#endif
