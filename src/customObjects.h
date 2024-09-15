#include <GL/glut.h>
#include <GL/gl.h>

void fishSeg1(float s)
{
	glPushMatrix();
	glScalef(s, s, s);
	glutSolidTetrahedron();
	glPopMatrix();
}

void fishSeg2(float s)
{
	glutSolidCube(s);
}

void fishSeg3(float s)
{
	glPushMatrix();
	glScalef(0.5 * s, 2. * s, 0.5 * s);
	glutSolidTetrahedron();
	glPopMatrix();
}

void castle(float x, float y, float z, float scale, float rotationX, float rotationY, float rotationZ) 
{
	glPushMatrix();
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
	glPopMatrix();
}


