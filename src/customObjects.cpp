#include "../includes/libpack.h"
#include <GL/glut.h>
#include <GL/gl.h>

#define FISH_HEAD_FACE_LEN 0.2
#define FISH_HEAD_NECK_LEN 0.8
#define FISH_HEAD_SIDE_LEN 0.5
#define FISH_EYE_RADIUS 0.2

#define FISH_COLOR 1.0, 0.5, 0.1, 1.0

void fishHeadModel(float s)
{
	glPushMatrix();
	glColor4f(FISH_COLOR);
	glScalef(s, s, s);

	// Globo ocular esquerdo
	glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 1.0f);
		glTranslatef(-(FISH_HEAD_NECK_LEN + FISH_HEAD_FACE_LEN)/2,0,0);
		glutSolidSphere(FISH_EYE_RADIUS, 16, 16);
	glPopMatrix();

	// Globo ocular direito
	glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 1.0f);
		glTranslatef((FISH_HEAD_NECK_LEN + FISH_HEAD_FACE_LEN)/2,0,0);
		glutSolidSphere(FISH_EYE_RADIUS, 16, 16);
	glPopMatrix();

	// Pupila direita
	glPushMatrix();
		glColor4f(0.0, 0.0, 0.0, 1.0f);
		glTranslatef((FISH_HEAD_NECK_LEN + FISH_HEAD_FACE_LEN + FISH_EYE_RADIUS * 1.5)/2,0,0);
		glutSolidSphere(FISH_EYE_RADIUS*0.75, 8, 8);
	glPopMatrix();

	// Pupila esquerda
	glPushMatrix();
		glColor4f(0.0, 0.0, 0.0, 1.0f);
		glTranslatef(-(FISH_HEAD_NECK_LEN + FISH_HEAD_FACE_LEN + FISH_EYE_RADIUS * 1.5)/2,0,0);
		glutSolidSphere(FISH_EYE_RADIUS*0.75, 8, 8);
	glPopMatrix();

	glColor4f(FISH_COLOR);
	glBegin(GL_QUADS);
    	// Frente
	    glVertex3f(-FISH_HEAD_FACE_LEN, -FISH_HEAD_FACE_LEN, FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_FACE_LEN, -FISH_HEAD_FACE_LEN, FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_FACE_LEN,  FISH_HEAD_FACE_LEN, FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_FACE_LEN,  FISH_HEAD_FACE_LEN, FISH_HEAD_SIDE_LEN);
	
	    // Tras
	    glVertex3f(-FISH_HEAD_NECK_LEN, -FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_NECK_LEN, -FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_NECK_LEN,  FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_NECK_LEN,  FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	
	    // Esquerda
	    glVertex3f(-FISH_HEAD_NECK_LEN, -FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_FACE_LEN, -FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_FACE_LEN,  FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_NECK_LEN,  FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	
	    // Direita
	    glVertex3f(FISH_HEAD_NECK_LEN, -FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f(FISH_HEAD_FACE_LEN, -FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	    glVertex3f(FISH_HEAD_FACE_LEN,  FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	    glVertex3f(FISH_HEAD_NECK_LEN,  FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	
	    // Cima
	    glVertex3f(-FISH_HEAD_NECK_LEN, FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_NECK_LEN, FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_FACE_LEN, FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_FACE_LEN, FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	
	    // Abaixo
	    glVertex3f(-FISH_HEAD_NECK_LEN, -FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_NECK_LEN, -FISH_HEAD_NECK_LEN, -FISH_HEAD_SIDE_LEN);
	    glVertex3f( FISH_HEAD_FACE_LEN, -FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	    glVertex3f(-FISH_HEAD_FACE_LEN, -FISH_HEAD_FACE_LEN,  FISH_HEAD_SIDE_LEN);
	glEnd();

	glPopMatrix();
}

void fishDorsalModel(float s)
{
	glColor4f(FISH_COLOR);
	glutSolidCube(s);
}

void fishTailModel(float s)
{
	glColor4f(FISH_COLOR);
	glScalef(.5 * s, .5 * s, 2. * s);
	glutSolidTetrahedron();
}

void castleModel(
			float x, float y, float z, 
			float scale, 
			float rotationX, float rotationY, float rotationZ
		) 
{
	glTranslatef(x, y, z);
	
	glScalef(scale, scale, scale);
	
	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
	
    	GLfloat walls[] = {216.0 / 255.0, 25.0 / 255.0f, 178.0 / 255.0, 1.};
	glColor4fv(walls);

	glBegin(GL_QUADS);
    	// Frente
	    glVertex3f(-1.0, -1.0, 1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	
	    // Tras
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, -1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	    glVertex3f(-1.0, 1.0, -1.0);
	
	    // Esquerda
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(-1.0, -1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, -1.0);
	
	    // Direita
	    glVertex3f(1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	
	    // Cima
	    glVertex3f(-1.0, 1.0, -1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	
	    // Abaixo
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
}

void aquariumModel(float s) 
{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 
    // Cores
    GLfloat topColor[] 	  = {116.0 / 255.0, 225.0 / 255.0f, 178.0 / 255.0, 0.4};
    GLfloat bottomColor[] = { 34.0 / 255.0,  68.0 / 255.0f, 164.0 / 255.0, 0.4};
    GLfloat floorColor[]  = {239.0 / 255.0, 214.0 / 255.0f, 177.0 / 255.0, 1.0};

    // Aquário
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(s/2., s/2., s/2.);

        glBegin(GL_QUADS);

    	    // Frente
	    glColor4fv(bottomColor);
	    glVertex3f(-1.0, -1.0, 1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glColor4fv(topColor); 
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	
	    // Tras
	    glColor4fv(bottomColor);
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, -1.0);
	    glColor4fv(topColor); 
	    glVertex3f(1.0, 1.0, -1.0);
	    glVertex3f(-1.0, 1.0, -1.0);
	
	    // Esquerda
	    glColor4fv(bottomColor); 
	    glVertex3f(-1.0, -1.0, -1.0);
	    glVertex3f(-1.0, -1.0, 1.0);
	    glColor4fv(topColor); 
	    glVertex3f(-1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, -1.0);
	
	    // Direita
	    glColor4fv(bottomColor); 
	    glVertex3f(1.0, -1.0, -1.0);
	    glVertex3f(1.0, -1.0, 1.0);
	    glColor4fv(topColor); 
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	
	    // Cima
	    glColor4fv(topColor); 
	    glVertex3f(-1.0, 1.0, -1.0);
	    glVertex3f(1.0, 1.0, -1.0);
	    glVertex3f(1.0, 1.0, 1.0);
	    glVertex3f(-1.0, 1.0, 1.0);
	
	    // Abaixo
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

    // Areia
    glPushMatrix();
  	glTranslatef(0., -s/2., 0.);
    	glScalef(s, 10, s);
    	glColor4fv(floorColor);
	glutSolidCube(1.);
    glPopMatrix();
}

void baitModel(float s, float x, float y, float z, float ceil)
{
	glPushMatrix();
    		glColor4f(0.5, 0.2, 0.2, 1.);
		glutSolidSphere(s, 20, 20);
    		glColor4f(0, 0, 0.1, 0.6);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, ceil, 0);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
    		glColor4f(1, 1, 1, 0.4);
		glTranslatef(0., ceil, 0.);
		glScalef(2., 1., 2.);
		glutSolidCube(s);
	glPopMatrix();
}
