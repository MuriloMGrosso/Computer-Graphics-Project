/*
 * Este programa foi feito para o projeto 1 da disciplina 
 * de Computacao Grafica do curso Bacharelado em Ciencias
 * da Computacao (BCC) na FFCLRP USP.
 *
 * Autores:
 * Murilo M. Grosso
 * Octavio X. Furio
 */

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include "input.h"
				
#define CAM_MOVE_SPEED 100			// Velocidade de movimento da camera (pixels/s)
#define FPS 60						// Frames por segundo
#define DELTA_TIME 1/FPS			// Tempo por frame, em segundos

float camWidth = 640.0;					// Largura da camera (pixels)
float camHeight = 360.0;				// Altura da camera (pixels)
float camAspect = camWidth/camHeight;		// Aspecto da camera
float camAngle = 45.0;					// Angulo da view da camera
float camX = 0.0;						// Posicao X da camera
float camY = 0.0;						// Posicao Y da camera
float camZ = 300.0;						// Posicao Z da camera

void draw();									// Desenha objetos na cena
void updateView();								// Inicia e atualiza a view
void update(int value);							// Funcao executada a cada frame
void start(int argc, char **argv);				// Inicia parametros iniciais do Open GL
void windowSizeUpdate(int width, int height); 	// Atualiza o tamanho da janela

int main(int argc, char **argv) {
    start(argc, argv);
	return 0;
}

void update(int value) {

	/*
	 * Movimenta a camera.
	 * Nota: Multiplicar por DELTA_TIME garante que o 
	 * movimento seja o mesmo independentemente do FPS 
	 * escolhido.
	 */ 
	if(input::isUpPressed())
		camY += CAM_MOVE_SPEED * DELTA_TIME;
	if(input::isDownPressed())
		camY -= CAM_MOVE_SPEED * DELTA_TIME;
	if(input::isLeftPressed())
		camX -= CAM_MOVE_SPEED * DELTA_TIME;
	if(input::isRightPressed())
		camX += CAM_MOVE_SPEED * DELTA_TIME;

	// Atualiza a view e chama o proximo frame
	glutTimerFunc(DELTA_TIME * 1000, update, value + 1);
	updateView();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, camWidth, camHeight);

	glColor3f(0.8, 0.0, 0.3);
	glPushMatrix();
		glutWireCube(50.0);
	glPopMatrix();

	glutSwapBuffers();
}

void start(int argc, char **argv) {
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

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

	glutTimerFunc(DELTA_TIME * 1000, update, 0);

	glClearColor(0.0, 0.0, 0.2, 1.0);
	glEnable(GL_DEPTH_TEST);

	updateView();

	glutMainLoop();
}

void updateView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, camAspect, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		camX, camY, camZ,
		0, 0, 0  ,
		0, 1, 0
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