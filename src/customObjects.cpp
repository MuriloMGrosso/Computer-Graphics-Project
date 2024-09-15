#include "libpack.h"
#include <GL/glut.h>
#include <GL/gl.h>

void fishHeadModel(float s)
{
GLfloat head[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    // Back face
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    // Left face
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

    // Right face
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,

    // Top face
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f
};

	glColor4f(1.0, 0.3, 0.0, 1.);
	glPushMatrix();
	glScalef(s, s, s);
	glVertexPointer(3, GL_FLOAT, 0, head);
	glDrawArrays(GL_QUADS, 0, 24);
	glutSolidTetrahedron();
	glPopMatrix();
}

void fishDorsalModel(float s)
{
	glColor4f(0.9, 0.2, 0.0, 1.);
	glutSolidCube(s);
}

void fishTailModel(float s)
{
	glColor4f(1.0, 0.4, 0.0, 1.);
	glScalef(0.5 * s, 2. * s, 0.5 * s);
	glutSolidTetrahedron();
}

void castleModel(float x, float y, float z, float scale, float rotationX, float rotationY, float rotationZ) 
{
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
	
	GLfloat vertices[] = {
		-50.0f, -50.0f, -150.0f, // Vertex 0
		-50.0f, 50.0f, -150.0f, // Vertex 1
		50.0f, -50.0f, -150.0f, // Vertex 2
		50.0f, 50.0f, -150.0f  // Vertex 3
	};

	GLubyte indices[] = {
		0, 1, 2, // Face 1
		0, 1, 3, // Face 2
		1, 2, 3, // Face 3
		2, 0, 3  // Face 4
	};
    
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < sizeof(indices)/sizeof(indices[0]); i += 3) {
		glVertex3fv(&vertices[indices[i] * 3]);
		glVertex3fv(&vertices[indices[i+1] * 3]);
		glVertex3fv(&vertices[indices[i+2] * 3]);
	}
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
}

void baitModel(float s)
{
	glutWireCube(s);
}
