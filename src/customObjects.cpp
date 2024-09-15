#include "libpack.h"
#include <GL/glut.h>
#include <GL/gl.h>

void fishHeadModel(float s)
{
	glColor3f(1.0, 0.3, 0.0);
	glScalef(s, s, s);
	glutSolidTetrahedron();
}

void fishDorsalModel(float s)
{
	glColor3f(0.9, 0.2, 0.0);
	glutSolidCube(s);
}

void fishTailModel(float s)
{
	glColor3f(1.0, 0.4, 0.0);
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
	glColor3f(0, 0.5, 1);
	glutWireCube(s);
}

void baitModel(float s)
{
	glutWireCube(s);
}
