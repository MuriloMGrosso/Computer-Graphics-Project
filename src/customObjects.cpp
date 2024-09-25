#include "../includes/libpack.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>

#define FISH_COLOR 1.0, 0.5, 0.1, 1.0
#define FISH_SHADOW 0.8, 0.3, 0.0, 1.0
#define FIN_COLOR 1.0, 0.3, 0.1, 0.6

void crossProd(	float ux, float uy, float uz, float vx, float vy, float vz, float& nx, float& ny, float& nz ) 
{
    nx = uy * vz - uz * vy;
    ny = uz * vx - ux * vz;
    nz = ux * vy - uy * vx;
}

void normalize(float& x, float& y, float& z) 
{
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

void fishHeadModel(float s)
{
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
		getNormal(-0.25, -0.75, -.5, 0.25, -0.75, -.5, 0.5, 0.5, -0.75, nx, ny, nz);
		glNormal3f(nx, ny, nz);
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top	
	glEnd();

	glPopMatrix();
}

void fishDorsalModel(float s)
{
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

void fishTailModel(float s)
{	
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

		//glColor4f(FISH_SHADOW);

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

	glColor4f(1, 0, 0, 1);
	glBegin(GL_QUADS);
    	// Frente
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		
		// Tras
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(1.0, -1.0, -1.0);
		
		// Esquerda
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, -1.0);
			
		// Direita
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		
		// Cima
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, -1.0);
		
		// Abaixo
		glNormal3f(0.0, -1.0, 0.0);
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
    GLfloat topColor[] 	  = {116.0 / 255.0, 225.0 / 255.0, 178.0 / 255.0, 0.4};
    GLfloat bottomColor[] = { 34.0 / 255.0,  68.0 / 255.0, 164.0 / 255.0, 0.4};
    GLfloat floorColor[]  = {239.0 / 255.0, 214.0 / 255.0, 177.0 / 255.0, 1.0};
    GLfloat tableColor[]  = {145.0 / 255.0,  67.0 / 255.0,  29.0 / 255.0, 1.0};
    
    // Mesa
    glPushMatrix();
  	glTranslatef(0., -(10 + (s/2.)), 0.);
    	glScalef(s * 1.3, 10, s * 1.3);
    	glColor4fv(tableColor);
	glutSolidCube(1.);
    glPopMatrix();

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

void baitModel(float s)
{
	glPushMatrix();
    	glColor4f(0.5, 0.2, 0.2, 1.);
		glScalef(s, s, s);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

unsigned char* loadBMP(std::string filepath, int* width, int* height) {
    	FILE* file = fopen(filepath.c_str(), "rb");
    	if (!file) {
        	printf("Failed to open file: %s\n", filepath.c_str());
        	return nullptr;
    	}

    	unsigned char header[54];
    	fread(header, sizeof(unsigned char), 54, file);

    	*width = *(int*)&header[18];
    	*height = *(int*)&header[22];

    	int imageSize = 3 * (*width) * (*height); 
    	unsigned char* data = new unsigned char[imageSize];
    	fread(data, sizeof(unsigned char), imageSize, file); 
    	fclose(file);

	for (int i = 0; i < imageSize; i += 3) {
	    unsigned char temp = data[i];
	    data[i] = data[i + 2];
	    data[i + 2] = temp;
	}

    	return data;
}

int skyBoxWidth, skyBoxHeight;
unsigned char* skyBoxData;

void loadSkyBox(std::string filepath) {
	skyBoxData = loadBMP(filepath, &skyBoxWidth, &skyBoxHeight);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyBoxWidth, skyBoxHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBoxData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, skyBoxWidth, skyBoxHeight, GL_RGB, GL_UNSIGNED_BYTE, skyBoxData);

	glBindTexture(GL_TEXTURE_2D, textureID);
}

void updateSkyBox() {
    	if (!skyBoxData) { return; }

		glEnable(GL_TEXTURE_2D);
    	glBegin(GL_QUADS);
    		// Frente // L2C2
    		glTexCoord2f(0.25f, 0.33f); glVertex3f(-1000.0f, -1000.0f, 1000.0f);  
    		glTexCoord2f(0.5f, 0.33f);  glVertex3f(1000.0f, -1000.0f, 1000.0f);   
    		glTexCoord2f(0.5f, 0.66f);  glVertex3f(1000.0f, 1000.0f, 1000.0f);    
    		glTexCoord2f(0.25f, 0.66f); glVertex3f(-1000.0f, 1000.0f, 1000.0f);   

    		// Tras // L2C4
    		glTexCoord2f(0.75f, 0.33f); glVertex3f(1000.0f, -1000.0f, -1000.0f);  
    		glTexCoord2f(1.0f, 0.33f);  glVertex3f(-1000.0f, -1000.0f, -1000.0f); 
    		glTexCoord2f(1.0f, 0.66f);  glVertex3f(-1000.0f, 1000.0f, -1000.0f);  
    		glTexCoord2f(0.75f, 0.66f); glVertex3f(1000.0f, 1000.0f, -1000.0f);   

    		// Esquerda // L2C1
    		glTexCoord2f(0.0f, 0.33f);  glVertex3f(-1000.0f, -1000.0f, -1000.0f); 
    		glTexCoord2f(0.25f, 0.33f); glVertex3f(-1000.0f, -1000.0f, 1000.0f);  
    		glTexCoord2f(0.25f, 0.66f); glVertex3f(-1000.0f, 1000.0f, 1000.0f);   
    		glTexCoord2f(0.0f, 0.66f);  glVertex3f(-1000.0f, 1000.0f, -1000.0f);  

    		// Direita // L2C3
    		glTexCoord2f(0.5f, 0.33f);  glVertex3f(1000.0f, -1000.0f, 1000.0f);   
    		glTexCoord2f(0.75f, 0.33f); glVertex3f(1000.0f, -1000.0f, -1000.0f);  
    		glTexCoord2f(0.75f, 0.66f); glVertex3f(1000.0f, 1000.0f, -1000.0f);   
    		glTexCoord2f(0.5f, 0.66f);  glVertex3f(1000.0f, 1000.0f, 1000.0f);    

    		// Cima // L1C2
    		glTexCoord2f(0.25f, 0.66f); glVertex3f(-1000.0f, 1000.0f, 1000.0f);   
    		glTexCoord2f(0.5f, 0.66f);  glVertex3f(1000.0f, 1000.0f, 1000.0f);    
   			glTexCoord2f(0.5f, 1.0f);   glVertex3f(1000.0f, 1000.0f, -1000.0f);   
    		glTexCoord2f(0.25f, 1.0f);  glVertex3f(-1000.0f, 1000.0f, -1000.0f);  

    		// Baixo // L3C2
    		glTexCoord2f(0.25f, 0.0f);  glVertex3f(-1000.0f, -1000.0f, -1000.0f); 
    		glTexCoord2f(0.5f, 0.0f);   glVertex3f(1000.0f, -1000.0f, -1000.0f);  
    		glTexCoord2f(0.5f, 0.33f);  glVertex3f(1000.0f, -1000.0f, 1000.0f);   
    		glTexCoord2f(0.25f, 0.33f); glVertex3f(-1000.0f, -1000.0f, 1000.0f);  

    	glEnd();

    	glDisable(GL_TEXTURE_2D);
}

