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

#include "../includes/libpack.h"
				
#define FPS 60				// Frames por segundo
#define DELTA_TIME 1.0/FPS		// Tempo por frame, em segundos
#define CAM_MOVE_SPEED 100.0		// Velocidade de movimento da camera (pixels/s)
#define CAM_ROT_SPEED 2.0		// Velocidade de rotacao da camera (rad/s)
#define FISH_SPEED 100.0		// Velocidade do peixe (pixels/s)
#define AQUARIUM_SIZE 300		// Tamanho do aquário (área de liberdade do peixe)

float camWidth = 640.0;			// Largura da camera (pixels)
float camHeight = 360.0;		// Altura da camera (pixels)
float camAspect = camWidth/camHeight;	// Aspecto da camera
float camAngle = 45.0;			// Angulo da view da camera
					
float radius = AQUARIUM_SIZE * 1.5;
float alpha = 0.0;

float camX = 0.0;			// Posicao X da camera
float camY = 0.0;			// Posicao Y da camera
float camZ = radius;			// Posicao Z da camera

float prevBaitX, prevBaitY, prevBaitZ;	// Posicoes anteriores da isca

Segment fishFocus(NULL,		 0);	// O que o peixe segue
Segment fishHead(&fishFocus, 	50);	// Cabeca do peixe
Segment fishDorsal(&fishHead, 	20);	// Corpo do peixe
Segment fishTail(&fishDorsal, 	20);	// Cauda do peixe

void draw();				// Desenha objetos na cena
void updateView();			// Inicia e atualiza a view
void update(int value);			// Funcao executada a cada frame
void start(int argc, char **argv);	// Inicia parametros iniciais do Open GL	
void windowSizeUpdate(int width, int height); 	// Atualiza o tamanho da janela

int main(int argc, char **argv) 
{	
	start(argc, argv);
	return 0;
}

void update(int value) {
	float deltaBaitX, deltaBaitY, deltaBaitZ;
	float horizontalMove;
	float verticalMove;

	// Movimentacao da camera
	alpha += input::getMouseButtonAxis() * CAM_ROT_SPEED * DELTA_TIME;
	camX = radius * sin(alpha); 
	camZ = radius * cos(alpha);
	camAngle += input::getMouseWheel() * CAM_MOVE_SPEED * DELTA_TIME;
	camAngle = camAngle < 10 ? 10 : camAngle > 140 ? 140 : camAngle;

	// Movimentacao da isca
	horizontalMove = input::getHorizontalAxis() * FISH_SPEED * DELTA_TIME;
	verticalMove = input::getVerticalAxis() * FISH_SPEED * DELTA_TIME;

	fishFocus.translate
	(
		horizontalMove * cos(alpha),
		verticalMove,
		horizontalMove * -sin(alpha)
	);

	float clampLimit = (AQUARIUM_SIZE / 2.) - 10.;
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
	fishHead.multClampedDist( (deltaBaitX + deltaBaitY + deltaBaitZ) ? 1.03 : 0.99, 15, 45 );

	fishHead.updatePosition(); 
	fishDorsal.updatePosition(); 
	fishTail.updatePosition();
	
	// Atualiza a view e chama o proximo frame
	glutTimerFunc(DELTA_TIME * 1000, update, value + 1);
	updateView();
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

		glRotatef(fishHead.getRotationX(), 1, 0, 0);
		glRotatef(fishHead.getRotationY(), 0, 1, 0);
		glRotatef(fishHead.getRotationZ(), 0, 0, 1);

		fishHeadModel(20.0);
	glPopMatrix();

	// Corpo do peixe
	glPushMatrix();
		glTranslatef(
			fishDorsal.getX(), 
			fishDorsal.getY(), 
			fishDorsal.getZ());
		glRotatef(fishDorsal.getRotationX(), 1, 0, 0);
		glRotatef(fishDorsal.getRotationY(), 0, 1, 0);
		glRotatef(fishDorsal.getRotationZ(), 0, 0, 1);
		fishDorsalModel(20.0);
	glPopMatrix();

	// Cauda do peixe
	glPushMatrix();
		glTranslatef(
			fishTail.getX(), 
			fishTail.getY(), 
			fishTail.getZ());
		glRotatef(fishTail.getRotationX(), 1, 0, 0);
		glRotatef(fishTail.getRotationY(), 0, 1, 0);
		glRotatef(fishTail.getRotationZ(), 0, 0, 1);
		fishTailModel(20.0);
	glPopMatrix();
	
	// Aquario
	glDepthMask(GL_FALSE);
	glPushMatrix();
	aquariumModel(AQUARIUM_SIZE);
	glPopMatrix();
	glDepthMask(GL_TRUE);
	
	// Isca
	glPushMatrix();	
		glTranslatef(
			fishFocus.getX(), 
			fishFocus.getY(), 
			fishFocus.getZ());
		glRotatef(fishFocus.getRotationX(), 0, 0, 1);
		glRotatef(fishFocus.getRotationY(), 0, 1, 0);
		glRotatef(fishFocus.getRotationZ(), 1, 0, 0);
		baitModel(5.0, fishFocus.getX(), fishFocus.getY(), fishFocus.getZ(), AQUARIUM_SIZE);
	glPopMatrix();

	// Isca
	glPushMatrix();
		castleModel(0, 0, 0, 10, 0, 0, 0);
	glPopMatrix();
	glutSwapBuffers();
}

void start(int argc, char **argv) {
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
	    
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

	glutTimerFunc(1, update, 0);

	glClearColor(0.0, 0.0, 0.2, 1.0);
	glEnable(GL_DEPTH_TEST);

	updateView();

	glutMainLoop();
}

void updateView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camAngle, camAspect, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(	camX, 	camY, 	camZ,	// Cam-pos
			fishFocus.getX(), fishFocus.getY(), fishFocus.getZ(),		// Tar-pos
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
