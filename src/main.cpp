/*
 * Este programa foi feito para o projeto 1 da disciplina 
 * de Computacao Grafica do curso Bacharelado em Ciencias
 * da Computacao (BCC) na FFCLRP USP.
 *
 * Autores:
 * Murilo M. Grosso
 * Octavio X. Furio
 */

#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <chrono>

#include "../includes/libpack.h"
				
#define FPS 60				// Frames por segundo
#define DELTA_TIME 1.0/FPS		// Tempo por frame, em segundos
#define FPS_DISPLAY_RATE .1
#define CAM_MOVE_SPEED 100.0		// Velocidade de movimento da camera (pixels/s)
#define CAM_ROT_SPEED 2.0		// Velocidade de rotacao da camera (rad/s)
#define FISH_SPEED 75.0			// Velocidade do peixe (pixels/s)
#define AQUARIUM_SIZE 500		// Tamanho do aquário (área de liberdade do peixe)
#define FISH_SIZE 20.0			// Tamanho do peixe (cada segmento tem o mesmo tamanho)

float camWidth = 640.0;			// Largur60a da camera (pixels)
float camHeight = 360.0;		// Altura da camera (pixels)
float camAspect = camWidth/camHeight;	// Aspecto da camera
float camAngle = 45.0;			// Angulo da view da camera
					
float radius = AQUARIUM_SIZE * 1.5;
float alpha = 0.0;

float camLerp = 0.05;			// Lerp da camera
float camX = 0.0;			// Posicao X da camera
float camY = 0.0;			// Posicao Y da camera
float camZ = radius;			// Posicao Z da camera
					
float focusLerp = 0.05;			// Lerp do alvo
float tarX = 0.0;			// Posicao X do alvo
float tarY = 0.0;			// Posicao Y do alvo
float tarZ = 0.0;			// Posicao Z do alvo

float prevBaitX, prevBaitY, prevBaitZ;	// Posicoes anteriores da isca

Segment fishFocus(NULL,	0, 1);		// O que o peixe segue
Segment fishHead(&fishFocus, 50, 0.02);		// Cabeca do peixe
Segment fishDorsal(&fishHead, 	FISH_SIZE * 1.75, 1);	// Corpo do peixe
Segment fishTail(&fishDorsal, 	FISH_SIZE * 1.5, 1);	// Cauda do peixe

int fpsCount;
float currentFPS;
float fpsDisplayTimer;
float deltaTime = DELTA_TIME;
std::chrono::time_point<std::chrono::system_clock> startFrameTime;

void draw();				// Desenha objetos na cena
void setLight();			// Iluminacao da cena
void updateView();			// Inicia e atualiza a view
void update(int value);			// Funcao executada a cada frame
void start(int argc, char **argv);	// Inicia parametros iniciais do Open GL	
void windowSizeUpdate(int width, int height); 	// Atualiza o tamanho da janela

int main(int argc, char **argv) 
{	
	std::cout << std::endl;
	start(argc, argv);
	return 0;
}

void update(int value) {
	float deltaBaitX, deltaBaitY, deltaBaitZ;
	float horizontalMove;
	float verticalMove;
	std::chrono::duration<double> timeElapsed;
	auto prevStartFrame = startFrameTime;

	startFrameTime = std::chrono::system_clock::now();
	timeElapsed = startFrameTime - prevStartFrame;
	currentFPS += 1.0/timeElapsed.count();
	fpsCount++;

	if(fpsDisplayTimer < 0) 
	{
		std::cout << "FPS: " << currentFPS/fpsCount << " \r";
		fpsDisplayTimer = FPS_DISPLAY_RATE;
		currentFPS = 0;
		fpsCount = 0;
	}
	else
		fpsDisplayTimer -= DELTA_TIME;

	// Movimentacao da camera
	alpha += input::getMouseButtonAxis() * CAM_ROT_SPEED * DELTA_TIME;
	camX = (camLerp * radius * sin(alpha)) + ((1 - camLerp) * camX); 
	camZ = (camLerp * radius * cos(alpha)) + ((1 - camLerp) * camZ);
	
	camAngle += input::getMouseWheel() * CAM_MOVE_SPEED * DELTA_TIME;
	camAngle = camAngle < 5 ? 5 : camAngle > 80 ? 80 : camAngle;

	// Movimentacao da isca
	horizontalMove = input::getHorizontalAxis() * (FISH_SPEED + camAngle) * DELTA_TIME;
	verticalMove = input::getVerticalAxis() * (FISH_SPEED + camAngle) * DELTA_TIME;

	fishFocus.translate
	(
		horizontalMove * cos(alpha),
		verticalMove,
		horizontalMove * -sin(alpha)
	);

	float clampLimit = (AQUARIUM_SIZE / 2.) - 30.;
	fishFocus.clampX(-clampLimit, clampLimit);
	fishFocus.clampY(-clampLimit, clampLimit);
	fishFocus.clampZ(-clampLimit, clampLimit);	

	deltaBaitX = fishFocus.getX() - prevBaitX;
	deltaBaitY = fishFocus.getY() - prevBaitY;	
	deltaBaitZ = fishFocus.getZ() - prevBaitZ;			

	prevBaitX = fishFocus.getX();
	prevBaitY = fishFocus.getY();
	prevBaitZ = fishFocus.getZ();	

	// Movimenta o peixe
	fishHead.updatePosition(); 
	fishDorsal.updatePosition(); 
	fishTail.updatePosition();
	
	float lightPos[4] = {prevBaitX, prevBaitY, prevBaitZ, 1.};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	
	// Atualiza a view e chama o proximo frame
	updateView();

	auto endFrameTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = endFrameTime - startFrameTime;
	double timeLeft = DELTA_TIME * 1000 - elapsed_seconds.count();
	timeLeft = timeLeft < 0 ? 0 : timeLeft;

	glutTimerFunc(timeLeft, update, value + 1);
}

void draw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, camWidth, camHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Cabeca do peixe
	glPushMatrix();
		glTranslatef(
			fishHead.getX(), 
			fishHead.getY(), 
			fishHead.getZ());

		glRotatef(fishHead.getRotationY(), 0, 1, 0);
		glRotatef(fishHead.getRotationXZ(), 1, 0, 0);

		glTranslatef(0,0,.5 * FISH_SIZE);

		fishHeadModel(FISH_SIZE);
	glPopMatrix();

	// Corpo do peixe
	glPushMatrix();
		glTranslatef(
			fishDorsal.getX(), 
			fishDorsal.getY(), 
			fishDorsal.getZ());

		glRotatef(fishDorsal.getRotationY(), 0, 1, 0);
		glRotatef(fishDorsal.getRotationXZ(), 1, 0, 0);

		glTranslatef(0,0,1 * FISH_SIZE);
		fishDorsalModel(FISH_SIZE);
	glPopMatrix();

	// Cauda do peixe
	glPushMatrix();
		glTranslatef(
			fishTail.getX(), 
			fishTail.getY(), 
			fishTail.getZ());

		glRotatef(fishTail.getRotationY(), 0, 1, 0);
		glRotatef(fishTail.getRotationXZ(), 1, 0, 0);

		glTranslatef(0,0,1.5 * FISH_SIZE);
		fishTailModel(FISH_SIZE);
	glPopMatrix();
	
	// Isca
	glPushMatrix();	
		glTranslatef(
			fishFocus.getX(), 
			fishFocus.getY(), 
			fishFocus.getZ());

		glRotatef(fishFocus.getRotationY(), 0, 1, 0);
		glRotatef(fishFocus.getRotationXZ(), 1, 0, 0);

		baitModel(3.0);
	glPopMatrix();	

	// Castelo
	glPushMatrix();
		castleModel(-100, -(AQUARIUM_SIZE / 2), -100, // X, Y, Z
			   40, 				     // Escala
			   0, 0, 0);			     // Rotação
	glPopMatrix();

	// Aquario
	glDepthMask(GL_FALSE);
		glPushMatrix();
			aquariumModel(AQUARIUM_SIZE);
		glPopMatrix();
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

void start(int argc, char **argv) {
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	    
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(camWidth, camHeight);
    glutCreateWindow("Peixe");

    glutDisplayFunc(draw);
	glutReshapeFunc(windowSizeUpdate);

	glutMouseFunc(input::mouseManager);
	glutKeyboardFunc(input::keyboardDown);
	glutKeyboardUpFunc(input::keyboardUp);
	glutSpecialFunc(input::specialKeysDown);
	glutSpecialUpFunc(input::specialKeysUp);

	glClearColor(0.0, 0.0, 0.1, 1.0);

	setLight();

	glDisable( GL_CULL_FACE );
	glutTimerFunc(1, update, 0);
	updateView();

	glutMainLoop();
}


void updateView() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camAngle, camAspect, 0.1, 3000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	tarX = (focusLerp * fishFocus.getX()) + ((1 - focusLerp) * tarX);
	tarY = (focusLerp * fishFocus.getY()) + ((1 - focusLerp) * tarY);
	tarZ = (focusLerp * fishFocus.getZ()) + ((1 - focusLerp) * tarZ);

	gluLookAt(	camX, 	camY, 	camZ,	// Cam-pos
			tarX, 	tarY, 	tarZ,	// Tar-pos
			0, 	1, 	0	// Normal
		);

	glutPostRedisplay();
}

void windowSizeUpdate(int width, int height)
{
	height = height == 0 ? 1 : height;

	camWidth = width;
	camHeight = height;
	camAspect = (float)width / (float)height;
}

void setLight()
{
	float lightPos[4] = {0., AQUARIUM_SIZE, 100., 1.};

        // Normal Light
	float ambient[4] = {0, 0, 0, .3};
	float diffuse[4] = {1., 1., 1., .3};
	float specular[4] = {.5, .5, .5, .3};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	// NightMode Light
	float baitAmbient[4] = {0.1, 0, 0, .3};
	float baitSpecular[4] = {1., .6, .6, 1.};
	float baitDiffuse[4] = {1., .5, .5, 1.};
	glLightfv(GL_LIGHT1, GL_AMBIENT, baitAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, baitDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, baitSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

	glShadeModel(GL_SMOOTH);

	float specularity[4] = {.1, .15, .1, 1.};
	int expoent = 1024;
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
	glMateriali(GL_FRONT,GL_SHININESS, expoent);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
 	glDepthMask(GL_TRUE);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
