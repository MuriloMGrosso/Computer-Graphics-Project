/* 
 * Modelos de objetos customizados.
 */

/*----------------------------------------------------------------------------------------*/
// BIBLIOTECAS

#include "../includes/libpack.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

/*----------------------------------------------------------------------------------------*/
// MACROS

#define FISH_COLOR 1.0, 0.5, 0.1, 1.0
#define FIN_COLOR 1.0, 0.2, 0.0, 0.8
#define KELP_COLOR 0.1, 0.8, 0.4, 0.1

/*----------------------------------------------------------------------------------------*/
// IMPLEMENTACAO DAS FUNCOES

void crossProd(	float ux, float uy, float uz, float vx, float vy, float vz, float& nx, float& ny, float& nz ) {
    nx = uy * vz - uz * vy;
    ny = uz * vx - ux * vz;
    nz = ux * vy - uy * vx;
}

void normalize(float& x, float& y, float& z) {
    float len = sqrt(x * x + y * y + z * z);
    x /= len; y /= len; z /= len; // Modulo = 1
}

// Para GL_TRIANGLES
void getNormal( float x1, float y1, float z1, // v1 
		float x2, float y2, float z2, // v2  > Anti-horario!
		float x3, float y3, float z3, // v3 
               
		float& nx, float& ny, float& nz) 
{

    float ux = x2 - x1;
    float uy = y2 - y1;
    float uz = z2 - z1;

    float vx = x3 - x1;
    float vy = y3 - y1;
    float vz = z3 - z1;

    crossProd(ux, uy, uz, vx, vy, vz, nx, ny, nz);

    normalize(nx, ny, nz);
}

// Para GL_QUADS
void getNormal(
		float x1, float y1, float z1, // v1  > Um tanto desnecessario,
		float x2, float y2, float z2, // v2  > mas, ajuda a organizar.
		float x3, float y3, float z3, // v3  
		float x4, float y4, float z4, // v4  > Tambem anti-horario.

               float& nx, float& ny, float& nz) {

    getNormal(x1, y1, z1, x2, y2, z2, x3, y3, z3, nx, ny, nz);
}

void betterSolidCube(GLfloat size) {
    GLfloat halfSize = size / 2.0f;

    GLfloat mat_diffuse[] = {116.0 / 255.0, 225.0 / 255.0, 178.0 / 255.0, 0.2}; 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    // Frente
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize,  halfSize);

    // Tras
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);

    // Direita
    glNormal3f(1.0f, 0.0f, 0.0f);  
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);

    // Esquerda
    glNormal3f(-1.0f, 0.0f, 0.0f);  
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Cima
    glNormal3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);

    // Abaixo
    glNormal3f(0.0f, -1.0f, 0.0f); 
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
}

void eyeModel() {
	glPushMatrix();
		glColor4f(0,0,0,1);
		glTranslated(-0.1,0,0);
		glutSolidSphere(0.15,10,10);
	glPopMatrix();
}

void fishHeadModel(float s) {
	glPushMatrix();
	glColor4f(FISH_COLOR);
	glScalef(s, s, s);
	float nx, ny, nz;

	glBegin(GL_TRIANGLES);
		// Forehead
		getNormal(0, 0, 1, 0.5, .5, 0, -0.5, .5, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, 0, 1); 		// Nose-tip
		glVertex3f(0.5, .5, 0);		// Left brow
		glVertex3f(-.5, .5, 0);		// Right brow	
					
		// Chin
		getNormal(0, 0, 1, -0.25, -0.75, -.5, 0.25, -0.75 , -.5, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, 0, 1);   		// Nose-tip
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin
		glVertex3f(0.25, -0.75 , -.5); 	// Left chin
					  
		// Left side of face
		getNormal(0, 0, 1, 0.25, -0.75, -.5, 0.5, .5, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, 0, 1);   		// Nose-tip
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
		glVertex3f(0.5, .5, 0);		// Left brow
					
		// Right side of face
		getNormal(0, 0, 1, -0.5, .5, 0, -0.25, -0.75, -.5, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, 0, 1);   		// Nose-tip
		glVertex3f(-.5, .5, 0);		// Right brow	
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	

		glColor4f(FIN_COLOR);
		// Left hand
		getNormal(0.4, -0.5, 0, 1, -1, -1, 1, -0.5, -1, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0.4, -0.5, 0);   	// Joint
		glVertex3f(1, -1 , -1); 	// Lower
		glVertex3f(1, -0.5, -1);	// Upper
					
		// Right hand
		getNormal(-0.4, -0.5, 0, -1, -0.5, -1, -1, -1, -1, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.4, -0.5, 0);	// Joint
		glVertex3f(-1, -0.5, -1);	// Upper	
		glVertex3f(-1, -1, -1); 	// Lower

		glColor4f(FISH_COLOR);
		// Left side of neck
		getNormal(0.5, 0.5, -0.75, 0.5, .5, 0, 0.25, -0.75, -.5, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
		glVertex3f(0.5, .5, 0);		// Left brow
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
					
		// Right side of neck
		getNormal(-0.5, 0.5, -0.75, -0.25, -0.75, -.5, -0.5, .5, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top	
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	
		glVertex3f(-.5, .5, 0);		// Right brow	
	glEnd();

	glBegin(GL_QUADS);
		// Top of head
		getNormal(-0.5, 0.5, 0, 0.5, 0.5, 0, 0.5, 0.5, -0.75, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.5, 0);	// Right brow	
		glVertex3f(0.5, 0.5, 0);	// Left brow
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top	
		
		// Back of head
		getNormal(0.25, -0.75, -.5, -0.25, -0.75, -.5, -0.5, 0.5, -0.75, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
	glEnd();

	glTranslated(-.2,0,0);
	eyeModel();
	glTranslated(.4,0,0);
	glRotatef(180,0,1,0);
	eyeModel();

	glPopMatrix();
}

void fishDorsalModel(float s) {
	glPushMatrix();
	glScalef(s, s, s);
	float nx, ny, nz;

	glBegin(GL_TRIANGLES);
		glColor4f(FIN_COLOR);

		// Top fin
		glNormal3f(0., 0., 1.); 	// A definir...
		glVertex3f(0, 0.5, 0.5);	// Base front
		glVertex3f(0, 1.5, -1);		// Tip	
		glVertex3f(0, 0.25, -0.75);	// Base back			
	glEnd();

	glBegin(GL_QUADS);
		glColor4f(FISH_COLOR);

		// Neck conection
		getNormal(-0.5, 0.5, 0.75, 0.5, 0.5, 0.75, 0.25, -0.5, 0.75, -0.25, -0.5, 0.75, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.5, 0.75);	// Right front top
		glVertex3f(0.5, 0.5, 0.75);	// Left front top
		glVertex3f(0.25, -0.5, 0.75);	// Left front bottom
		glVertex3f(-0.25, -0.5, 0.75);	// Right front bottom	
		
		// Left side
		getNormal(0.5, 0.5, 0.75, 0.25, -0.5, 0.75, 0.25, -0.25, -1, 0.5, 0.25, -1, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0.5, 0.5, 0.75);	// Left front top
		glVertex3f(0.25, -0.5, 0.75);	// Left front bottom
		glVertex3f(0.25, -0.25, -1);	// Left back bottom
		glVertex3f(0.5, 0.25, -1);	// Left back top

		// Right side
		getNormal(-0.5, 0.5, 0.75, 0.5, 0.25, -1, 0.25, -0.25, -1, -0.25, -0.5, 0.75, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.5, 0.75);	// Right front top
		glVertex3f(-0.5, 0.25, -1);	// Right back top
		glVertex3f(-0.25, -0.25, -1);	// Right back bottom	
		glVertex3f(-0.25, -0.5, 0.75);	// Right front bottom	
	
		// Top side
		getNormal(-0.5, 0.5, 0.75, 0.5, 0.5, 0.75, 0.5, 0.25, -1, -0.5, 0.25, -1, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.5, 0.75);	// Right front top
		glVertex3f(0.5, 0.5, 0.75);	// Left front top
		glVertex3f(0.5, 0.25, -1);	// Left back top
		glVertex3f(-0.5, 0.25, -1);	// Right back top

		// Bottom side
		getNormal(0.25, -0.25, -1, -0.25, -0.25, -1, -0.25, -0.5, 0.75, 0.25, -0.5, 0.75, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0.25, -0.25, -1);	// Left back bottom
		glVertex3f(-0.25, -0.25, -1);	// Right back bottom	
		glVertex3f(-0.25, -0.5, 0.75);	// Right front bottom	
		glVertex3f(0.25, -0.5, 0.75);	// Left front bottom
		
		// Tail conection
		getNormal(-0.5, 0.25, -1, 0.5, 0.25, -1, 0.25, -0.25, -1, -0.25, -0.25, -1, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.25, -1);	// Right back top
		glVertex3f(0.5, 0.25, -1);	// Left back top
		glVertex3f(0.25, -0.25, -1);	// Left back bottom
		glVertex3f(-0.25, -0.25, -1);	// Right back bottom	
	glEnd();

	glBegin(GL_POLYGON);
		glColor4f(FIN_COLOR);

		// Bottom fin
		glNormal3f(0.0, 0.0, -1.0);	// A definir...
		glVertex3f(0, -0.25, 0.3);	// Base front	
		glVertex3f(0, -1, -0.25);	// Tip 1
		glVertex3f(0, -2, -0.75);	// Tip 2
		glVertex3f(0, -1, -0.5);	// Tip 3
		glVertex3f(0, -0.25, -0.75); 	// Base Back
	glEnd();

	glPopMatrix();
}

void fishTailModel(float s) {	
	glPushMatrix();
	glScalef(s, s, s);
	float nx, ny, nz;

	glBegin(GL_QUADS);
		glColor4f(FISH_COLOR);

		// Tail conection
		getNormal(0.5, 0.25, 0, -0.5, 0.25, 0, -0.25, -0.25, 0, 0.25, -0.25, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0.5, 0.25, 0);	// Left top
		glVertex3f(-0.5, 0.25, 0);	// Right top
		glVertex3f(-0.25, -0.25, 0);	// Right bottom	
		glVertex3f(0.25, -0.25, 0);	// Left bottom

		// Left side
		getNormal(0, 0.5, -0.25, 0.5, 0.25, 0, 0.25, -0.25, 0, 0, -0.5, -0.25, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0.5, 0.25, 0);	// Left top
		glVertex3f(0.25, -0.25, 0);	// Left bottom
		glVertex3f(0, -0.5, -0.25);	// Tail bottom	
		
		// Right side
		getNormal(-0.5, 0.25, 0, 0, 0.5, -0.25, 0, -0.5, -0.25, -0.25, -0.25, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.5, 0.25, 0);	// Right top
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0, -0.5, -0.25);	// Tail bottom
		glVertex3f(-0.25, -0.25, 0);	// Right bottom	
	glEnd();	

	glBegin(GL_TRIANGLES);
		glColor4f(FISH_COLOR);

		// Top side
		getNormal(0, 0.25, -0.25, 0.5, 0.25, 0, -0.5, 0.25, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0.5, 0.25, 0);	// Left top
		glVertex3f(-0.5, 0.25, 0);	// Right top

		// Top side
		getNormal(0, -0.5, -0.25, 0.25, -0.25, 0, -0.25, -0.25, 0, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(0, -0.5, -0.25);	// Tail bottom	
		glVertex3f(0.25, -0.25, 0);	// Left bottom
		glVertex3f(-0.25, -0.25, 0);	// Right bottom	
	glEnd();

	glBegin(GL_POLYGON);
		glColor4f(FIN_COLOR);
		
		// Big fin
		glNormal3f(0.0, 0.0, 1.0); 	// A definir...
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0, 2, -1.5);		// Tip 1
		glVertex3f(0, 0.5, -1);		// Tip 2
		glVertex3f(0, -2, -1.5);	// Tip 3
		glVertex3f(0, -0.5, -0.25); 	// Tail bottom
	glEnd();

	glPopMatrix();
}

void stonePillar(float topSize, float height) {
	glBegin(GL_QUADS);
    	// Frente
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(topSize, height, topSize);
		glVertex3f(-topSize, height, topSize);
		
		// Tras
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-1.0, 0.0, -1.0);
		glVertex3f(-topSize, height, -topSize);
		glVertex3f(topSize, height, -topSize);
		glVertex3f(1.0, 0.0, -1.0);
		
		// Esquerda
		glNormal3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, 0.0, -1.0);
		glVertex3f(-1.0, 0.0, 1.0);
		glVertex3f(-topSize, height, topSize);
		glVertex3f(-topSize, height, -topSize);
			
		// Direita
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, -1.0);
		glVertex3f(topSize, height, -topSize);
		glVertex3f(topSize, height, topSize);
		glVertex3f(1.0, 0.0, 1.0);
		
		// Cima
		glNormal3f(0.0, height, 0.0);
		glVertex3f(-topSize, height, -topSize);
		glVertex3f(-topSize, height, topSize);
		glVertex3f(topSize, height, topSize);
		glVertex3f(topSize, height, -topSize);
		
		// Abaixo
		glNormal3f(0.0, 0.0, 0.0);
		glVertex3f(-1.0, 0.0, -1.0);
		glVertex3f(1.0, 0.0, -1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(-1.0, 0.0, 1.0);
	glEnd();	
}

void castleModel(
			float x, float y, float z,
			float scale, 
			float rotationX, float rotationY, float rotationZ
		) 
{
	float height = 3;
	float topSize = 0.5;

	glTranslatef(x, y, z);

	glScalef(scale, scale, scale);
	
	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);

	glColor4f(0.2, 0.1, 0.2, 1);
	/* Base */
	stonePillar(topSize, height);

	/* Boca */
	glColor4f(.1, 0, 0, 1);
	glPushMatrix();
		glTranslated(0, .35, 1);
		glScalef(1.5, 2, 1);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(.2, 1, 10, 10); 
	glPopMatrix();

	/* Olhos */
	glColor4f(0.5, 0.8, 1, 1);
	glPushMatrix();
		glTranslated(-.35, height/1.5, .81);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(.1, 1, 10, 10); 
	glPopMatrix();

	glPushMatrix();
		glTranslated(.35, height/1.5, .81);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(.1, 1, 10, 10); 
	glPopMatrix();

	glColor4f(0.5, 0.5, 0.5, 1);
	glPushMatrix();
		glTranslated(-.35, height/1.5, .8);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(.2, 1, 10, 10); 
	glPopMatrix();

	glPushMatrix();
		glTranslated(.35, height/1.5, .8);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(.2, 1, 10, 10); 
	glPopMatrix();

	glColor4f(0.1, 0.05, 0.1, 1);
	/* Monocelha */
	glPushMatrix();
		glTranslated(0, height/1.3, (topSize + 1.0)/2.0);
		glScalef(.5, .2, .2);
		stonePillar(1, 1);
	glPopMatrix();

	/* Nariz */
	glPushMatrix();
		glTranslated(0, height/2.5, (topSize + 1.0)/2.0);
		glScalef(.25, .25, .25);
		stonePillar(topSize, height * 1.5);
	glPopMatrix();

	/* Orelha direita */
	glPushMatrix();
		glTranslated((topSize + 1.0)/2.0, height/2.0, 0);
		glScalef(.25, .25, .25);
		stonePillar(0.9, height);
	glPopMatrix();

	/* Orelha esquerda */
	glPushMatrix();
		glTranslated(-(topSize + 1.0)/2.0, height/2.0, 0);
		glScalef(.25, .25, .25);
		stonePillar(0.9, height);
	glPopMatrix();
}

void aquariumModel(float s) {
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Cores
    GLfloat topColor[] 	  = {116.0 / 255.0, 225.0 / 255.0, 178.0 / 255.0, 0.2};
    GLfloat bottomColor[] = { 34.0 / 255.0,  68.0 / 255.0, 164.0 / 255.0, 0.2};
    GLfloat floorColor[]  = {200.0 / 255.0, 180.0 / 255.0, 110.0 / 255.0, 1.0};
    GLfloat tableColor[]  = {145.0 / 255.0,  67.0 / 255.0,  29.0 / 255.0, 1.0};
    
    // Mesa
    glPushMatrix();
  	glTranslatef(0., -(10 + (s/2.)), 0.);
    	glScalef(s * 1.3, 10, s * 1.3);
    	glColor4fv(tableColor); 
	glBegin(GL_QUADS);

        glNormal3f(.0, 1., .0);
        glVertex3f(-.5, -.5, -.5);
        glVertex3f(.5, -.5, -.5);
        glVertex3f(.5, -.5, .5);
        glVertex3f(-.5, -.5, .5);
 	glEnd();

    glPopMatrix();

    // Aquário
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(s/2., s/2., s/2.);

        glBegin(GL_QUADS);

    	    // Frente
	    glNormal3f(0.0, 0.0, 1.0);
	    glColor4fv(bottomColor);
	    glVertex3f(-1.0, -1.0, 1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glColor4fv(topColor); 
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	
	    // Tras
	    glNormal3f(0.0, 0.0, -1.0);
	    glColor4fv(bottomColor);
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, -1.0);
	    glColor4fv(topColor); 
	    glVertex3f(1.0, 1.0, -1.0);
	    glVertex3f(-1.0, 1.0, -1.0);
	
	    // Esquerda
	    glNormal3f(-1.0, 0.0, 0.0);
	    glColor4fv(bottomColor); 
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(-1.0, -1.0, 1.0);
	    glColor4fv(topColor); 
	    glVertex3f(-1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, -1.0);
	
	    // Direita
	    glNormal3f(1.0, 0.0, 0.0);
	    glColor4fv(bottomColor); 
	    glVertex3f(1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glColor4fv(topColor); 
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	
	    // Cima
	    glNormal3f(0.0, 1.0, 0.0);
	    glColor4fv(topColor); 
	    glVertex3f(-1.0, 1.0, -1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	
	    // Abaixo
	    glNormal3f(0.0, -1.0, 0.0);
	    glColor4fv(floorColor); 
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glVertex3f(-1.0, -1.0, 1.0);
	
	glEnd();
    glPopMatrix();
    
    // Vidro do Aquario
    glColor4f(1, 1, 1, 0.4);
    glutWireCube(s); 
 
    // Areia (planificada)
    glPushMatrix();
    glTranslatef(.0, -s / 2., .0);
    glScalef(s, 10., s);
    glColor4fv(floorColor); 

    glBegin(GL_QUADS);
        glNormal3f(.0, 1., .0);
        glVertex3f(-.5, -.5, -.5);
        glVertex3f(.5, .5, -.5);
        glVertex3f(.5, -1., .5);
        glVertex3f(-.5, 1.0, .5);
    glEnd();

    glPopMatrix();
}

void baitModel(float s) {
	glPushMatrix();
    	glColor4f(0.5, 0.2, 0.2, 1.);
		glScalef(s, s, s);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

float bezierPoint(int axis, float t, float Bx[4], float By[4], float Bz[4]) {
	switch (axis)
	{
		case 'x':
		  return (pow(1.0 - t, 3.0) * Bx[0] 
		          + 3.0 * t * pow(1.0 - t, 2.0) * Bx[1] 
		          + 3.0 * pow(t, 2.0) * (1.0 - t) * Bx[2] 
		          + pow(t, 3.0) * Bx[3]);
		case 'y':
		  return (pow(1.0 - t, 3.0) * By[0] 
		          + 3.0 * t * pow(1.0 - t, 2.0) * By[1] 
		          + 3.0 * pow(t, 2.0) * (1.0 - t) * By[2] 
		          + pow(t, 3.0) * By[3]);
		case 'z':
		  return (pow(1.0 - t, 3.0) * Bz[0] 
		          + 3.0 * t * pow(1.0 - t, 2.0) * Bz[1] 
		          + 3.0 * pow(t, 2.0) * (1.0 - t) * Bz[2] 
		          + pow(t, 3.0) * Bz[3]);
	}
	return 0.0;
}


void kelpSegment(float s, float baseX, float baseY, float baseZ) 
{
	glPushMatrix();
	        glTranslatef(baseX, baseY, baseZ);
	
	        float nx, ny, nz;
    	        glColor4f(KELP_COLOR);
		glScalef(s, s, s);
		
		// Top
		glBegin(GL_QUADS);
                  glNormal3f(.0, 1., .0);
                  glVertex3f( .5, 1., -.5); // Back-right
                  glVertex3f(-.5, 1., -.5); // Back-left 
                  glVertex3f(-.5, 1.,  .5); // Front-left
                  glVertex3f( .5, 1.,  .5); // Front-right
                glEnd();
		
		glBegin(GL_TRIANGLES);	  
		  // Side 1
		  getNormal(-.5, 1., -.5, .5, 1., -.5, 0, 0, 0, nx, ny, nz);
		  glNormal3f(nx, ny, nz);
		  glVertex3f(-.5, 1., -.5); // Back-left
		  glVertex3f( .5, 1., -.5); // Back-right	
		  glVertex3f(0, 0, 0);      // Tip
		  
		  // Side 2
		  getNormal(.5, 1., -.5, .5, 1.,  .5, 0, 0, 0, nx, ny, nz);
		  glNormal3f(nx, ny, nz);
		  glVertex3f( .5, 1., -.5); // Back-right	
		  glVertex3f( .5, 1.,  .5); // Front-right	
		  glVertex3f(0, 0, 0);      // Tip
		  
		  // Side 3
		  getNormal(.5, 1.,  .5, -.5, 1.,  .5, 0, 0, 0, nx, ny, nz);
		  glNormal3f(nx, ny, nz);
		  glVertex3f( .5, 1.,  .5); // Front-right
		  glVertex3f(-.5, 1.,  .5); // Front-left
		  glVertex3f(0, 0, 0);      // Tip
		  
		  // Side 4
		  getNormal(-.5, 1.,  .5, -.5, 1., -.5, 0, 0, 0, nx, ny, nz);
		  glNormal3f(nx, ny, nz);
		  glVertex3f(-.5, 1.,  .5); // Front-left
		  glVertex3f(-.5, 1., -.5); // Back-left 	
		  glVertex3f(0, 0, 0);      // Tip
        	glEnd();
		
      glPopMatrix();
}

void kelpModel(int segments, float scale, float baseX, float baseY, float baseZ, float Bx[4], float By[4], float Bz[4]) 
{
  
  if (segments < 5 || scale < 1) return;
  GLfloat Px, Py, Pz;
  glPushMatrix();
  	glTranslatef(baseX, baseY, baseZ);
        
	glColor3f(1.0f, 0.6, 0.6f);
	
	glBegin(GL_LINE_STRIP);
		for (GLdouble t=0; t<=1.0; t+=1./segments) {
			Px = bezierPoint('x', t, Bx, By, Bz); 
			Py = bezierPoint('y', t, Bx, By, Bz); 
			Pz = bezierPoint('z', t, Bx, By, Bz);
			
			kelpSegment(scale, Px, Py, Pz);
	        }
	glEnd();
  glPopMatrix();
}

