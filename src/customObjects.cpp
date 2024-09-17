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

void fishHeadModel(float s)
{
	glPushMatrix();
	glColor4f(FISH_COLOR);
	glScalef(s, s, s);

	glBegin(GL_TRIANGLES);
		// Forehead
		glVertex3f(0, 0, 1); 		// Nose-tip
		glVertex3f(0.5, .5, 0);		// Left brow
		glVertex3f(-.5, .5, 0);		// Right brow	
					
		// Chin
		glVertex3f(0, 0, 1);   		// Nose-tip
		glVertex3f(0.25, -0.75 , -.5); 	// Left chin
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin
					  
		// Left side of face
		glVertex3f(0, 0, 1);   		// Nose-tip
		glVertex3f(0.5, .5, 0);		// Left brow
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
					
		// Right side of face
		glVertex3f(0, 0, 1);   		// Nose-tip
		glVertex3f(-.5, .5, 0);		// Right brow	
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	

		glColor4f(FIN_COLOR);
		// Left hand
		glVertex3f(0.4, -0.5, 0);   	// Joint
		glVertex3f(1, -0.5, -1);	// Upper
		glVertex3f(1, -1 , -1); 	// Lower
					
		// Right hand
		glVertex3f(-0.4, -0.5, 0);	// Joint
		glVertex3f(-1, -0.5, -1);	// Upper	
		glVertex3f(-1, -1, -1); 	// Lower

		glColor4f(FISH_COLOR);
		// Left side of neck
		glVertex3f(0.5, .5, 0);		// Left brow
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
					
		// Right side of neck
		glVertex3f(-.5, .5, 0);		// Right brow	
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top	
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	
	glEnd();

	glBegin(GL_QUADS);
		// Top of head
		glVertex3f(-0.5, 0.5, 0);	// Right brow	
		glVertex3f(0.5, 0.5, 0);	// Left brow
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top	
		
		glColor4f(FISH_SHADOW);
		// Back of head
		glVertex3f(0.25, -0.75, -.5); 	// Left chin
		glVertex3f(-0.25, -0.75, -.5); 	// Right chin	
		glVertex3f(-0.5, 0.5, -0.75);	// Right neck-top	
		glVertex3f(0.5, 0.5, -0.75);	// Left neck-top
	glEnd();

	glPopMatrix();
}

void fishDorsalModel(float s)
{
	glPushMatrix();
	glScalef(s, s, s);

	glBegin(GL_TRIANGLES);
		glColor4f(FIN_COLOR);

		// Top fin
		glVertex3f(0, 0.5, 0.5);	// Base front
		glVertex3f(0, 1.5, -1);		// Tip	
		glVertex3f(0, 0.25, -0.75);	// Base back			
	glEnd();

	glBegin(GL_QUADS);
		glColor4f(FISH_COLOR);

		// Neck conection
		glVertex3f(-0.5, 0.5, 0.75);	// Right front top
		glVertex3f(0.5, 0.5, 0.75);	// Left front top
		glVertex3f(0.25, -0.5, 0.75);	// Left front bottom
		glVertex3f(-0.25, -0.5, 0.75);	// Right front bottom	
		
		// Left side
		glVertex3f(0.5, 0.5, 0.75);	// Left front top
		glVertex3f(0.25, -0.5, 0.75);	// Left front bottom
		glVertex3f(0.25, -0.25, -1);	// Left back bottom
		glVertex3f(0.5, 0.25, -1);	// Left back top

		// Right side
		glVertex3f(-0.5, 0.5, 0.75);	// Right front top
		glVertex3f(-0.5, 0.25, -1);	// Right back top
		glVertex3f(-0.25, -0.25, -1);	// Right back bottom	
		glVertex3f(-0.25, -0.5, 0.75);	// Right front bottom	
	
		// Top side
		glVertex3f(-0.5, 0.5, 0.75);	// Right front top
		glVertex3f(0.5, 0.5, 0.75);	// Left front top
		glVertex3f(0.5, 0.25, -1);	// Left back top
		glVertex3f(-0.5, 0.25, -1);	// Right back top

		glColor4f(FISH_SHADOW);

		// Bottom side
		glVertex3f(0.25, -0.25, -1);	// Left back bottom
		glVertex3f(-0.25, -0.25, -1);	// Right back bottom	
		glVertex3f(-0.25, -0.5, 0.75);	// Right front bottom	
		glVertex3f(0.25, -0.5, 0.75);	// Left front bottom
		
		// Tail conection
		glVertex3f(-0.5, 0.25, -1);	// Right back top
		glVertex3f(0.5, 0.25, -1);	// Left back top
		glVertex3f(0.25, -0.25, -1);	// Left back bottom
		glVertex3f(-0.25, -0.25, -1);	// Right back bottom	
	glEnd();

	glBegin(GL_POLYGON);
		glColor4f(FIN_COLOR);

		// Bottom fin
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
	
	glBegin(GL_QUADS);
		glColor4f(FISH_COLOR);

		// Tail conection
		glVertex3f(-0.5, 0.25, 0);	// Right top
		glVertex3f(0.5, 0.25, 0);	// Left top
		glVertex3f(0.25, -0.25, 0);	// Left bottom
		glVertex3f(-0.25, -0.25, 0);	// Right bottom	

		// Left side
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0.5, 0.25, 0);	// Left top
		glVertex3f(0.25, -0.25, 0);	// Left bottom
		glVertex3f(0, -0.5, -0.25);	// Tail bottom	
		
		// Right side
		glVertex3f(-0.5, 0.25, 0);	// Right top
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0, -0.5, -0.25);	// Tail bottom
		glVertex3f(-0.25, -0.25, 0);	// Right bottom	
	glEnd();	

	glBegin(GL_TRIANGLES);
		glColor4f(FISH_COLOR);

		// Top side
		glVertex3f(0, 0.5, -0.25);	// Tail top
		glVertex3f(0.5, 0.25, 0);	// Left top
		glVertex3f(-0.5, 0.25, 0);	// Right top

		glColor4f(FISH_SHADOW);

		// Top side
		glVertex3f(0, -0.5, -0.25);	// Tail bottom	
		glVertex3f(0.25, -0.25, 0);	// Left bottom
		glVertex3f(-0.25, -0.25, 0);	// Right bottom	
	glEnd();

	glBegin(GL_POLYGON);
		glColor4f(FIN_COLOR);
		
		// Bottom fin
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
	
    	GLfloat walls[] = {116.0 / 255.0, 25.0 / 255.0f, 78.0 / 255.0, 1.};
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

void baitModel(float s, float x, float y, float z, float ceil)
{
	glPushMatrix();
    		glColor4f(0.5, 0.2, 0.2, 1.);
		glutSolidSphere(s, 20, 20);
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

void skyBox(std::string filepath) {
    	int width, height;
    	unsigned char* data = loadBMP(filepath, &width, &height);

    	if (!data) { return; }

    	GLuint textureID;
    	glGenTextures(1, &textureID);
    	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    	delete[] data;

    	glEnable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, textureID);

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

