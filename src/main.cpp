/*
 * PROJETO 1 DE COMPUTACAO GRAFICA:
 * Este programa foi feito para o 1o projeto da disciplina 
 * de Computacao Grafica do curso Bacharelado em Ciencias
 * da Computacao (BCC) na FFCLRP USP.
 *
 * AUTORES:
 * Murilo M. Grosso
 * Octavio X. Furio
 */

/*----------------------------------------------------------------------------------------*/
// BIBLIOTECAS

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <chrono>
#include <cmath>

#include "../includes/libpack.h"

/*----------------------------------------------------------------------------------------*/
// MACROS

#define TARGET_FPS 60					// Frames por segundo alvo
#define TARGET_DELTATIME 1.0/TARGET_FPS	// Duracao alvo de um frame (s)
#define FPS_DISPLAY_RATE 0.5			// Tempo (s) em que o FPS eh exibido na tela

#define CAM_MOVE_SPEED 100.0			// Velocidade de movimento da camera (pixels/s)
#define CAM_ROT_SPEED 2.0				// Velocidade de rotacao da camera (rad/s)
#define CAM_LERP 0.05					// Lerp da camera
#define CAM_TARGET_LERP 0.05			// Lerp do target da camera
#define CAM_MIN_ANGLE 5					// Angulo minimo da camera
#define CAM_MAX_ANGLE 80				// Angulo maximo da camera

#define BAIT_SPEED 75.0					// Velocidade da isca (pixels/s)
#define FISH_SIZE 20.0					// Tamanho do peixe
#define AQUARIUM_SIZE 500				// Tamanho do aquário (área de liberdade do peixe)
#define AQUARIUM_COLLISION ((AQUARIUM_SIZE / 2.) - 30.)	// Limite com a parede do aquario

/*----------------------------------------------------------------------------------------*/
// VARIAVEIS GLOBAIS

float camAngle = 45.0;					// Angulo da view da camera
float camWidth = 640.0;					// Largura da camera (pixels)
float camHeight = 360.0;				// Altura da camera (pixels)
float camAspect = camWidth/camHeight;	// Aspecto da camera
					
float camRadius = AQUARIUM_SIZE * 1.5;	// Distancia da camera a origem
float camTetha = 0.0;					// Angulo da camera com o eixo z (rad)

float camX = 0.0;			// Posicao X da camera
float camY = 0.0;			// Posicao Y da camera
float camZ = camRadius;		// Posicao Z da camera
					
float tarX = 0.0;			// Posicao X do alvo
float tarY = 0.0;			// Posicao Y do alvo
float tarZ = 0.0;			// Posicao Z do alvo

Segment fishFocus (NULL       ,	0               , 1    );	// Isca
Segment fishHead  (&fishFocus , 50              , 2e-2 );	// Cabeca do peixe
Segment fishDorsal(&fishHead  , FISH_SIZE * 1.75, 1    );	// Corpo do peixe
Segment fishTail  (&fishDorsal, FISH_SIZE * 1.5 , 1    );	// Cauda do peixe

int fpsCount;						// Contador de FPS				
float meanFPS;						// Armazena o valor do FPS atual medio
float fpsDisplayTimer;				// Temporizador para mostrar FPS
float deltaTime = 1.0/TARGET_FPS;	// Duracao de 1 frame (s)
std::chrono::time_point<std::chrono::system_clock> startFrameTime;	// Inicio do frame

/*----------------------------------------------------------------------------------------*/
// DECLARACAO DAS FUNCOES

void draw();									// Desenha objetos na cena
void setLight();								// Iluminacao da cena
void updateView();								// Inicia e atualiza a view
void update(int value);							// Funcao executada a cada frame
void start(int argc, char **argv);				// Inicia parametros iniciais do Open GL	
void windowSizeUpdate(int width, int height); 	// Atualiza o tamanho da janela

int normalize(double value, double min, double max);	// Normalizacao entre 0 e 1
double lerp(double a, double b, float l);				// Interpolacao linear
double clamp(double value, double min, double max);		// Limitacao do valor

/*----------------------------------------------------------------------------------------*/
// IMPLEMENTACAO DAS FUNCOES

int main(int argc, char **argv) {	
	std::cout << std::endl;
	std::cout << "Iniciando simulacao..." << std::endl;
	std::cout << std::endl;

	start(argc, argv);

	return 0;
}

void update(int value) {
	/* Variaveis */
	int normalizedCamAngle;
	float verticalMove;
	float horizontalMove;
	float lightPos[4] = {0, 0, 0, 1};

	double timeLeft;	// Tempo para fim do frame (ms)
	std::chrono::duration<double> timeElapsed;
	std::chrono::time_point<std::chrono::system_clock> prevStartFrame;

	/* Calcula o valor do FPS atual */
	prevStartFrame = startFrameTime;
	startFrameTime = std::chrono::system_clock::now();
	timeElapsed = (startFrameTime - prevStartFrame);
	deltaTime = timeElapsed.count();
	meanFPS += 1.0/deltaTime;
	fpsCount++;

	if(fpsDisplayTimer < 0) 
	{
		std::cout << "FPS: " << (int)(meanFPS/fpsCount) << std::endl;
		fpsDisplayTimer = FPS_DISPLAY_RATE;
		meanFPS = 0;
		fpsCount = 0;
	}
	else
		fpsDisplayTimer -= deltaTime;

	/* Movimentacao da camera */
	camTetha += input::getMouseButtonAxis() * CAM_ROT_SPEED * deltaTime;
	camX = lerp(camRadius * sin(camTetha), camX, CAM_LERP);
	camZ = lerp(camRadius * cos(camTetha), camZ, CAM_LERP);
	
	camAngle += input::getMouseWheel() * CAM_MOVE_SPEED * deltaTime;
	camAngle = clamp(camAngle, CAM_MIN_ANGLE, CAM_MAX_ANGLE);

	/* Movimentacao da isca */
	normalizedCamAngle = normalize(camAngle, CAM_MIN_ANGLE, CAM_MAX_ANGLE) + 1;
	horizontalMove = input::getHorizontalAxis() * BAIT_SPEED * normalizedCamAngle * deltaTime;
	verticalMove = input::getVerticalAxis() * BAIT_SPEED * normalizedCamAngle * deltaTime;

	fishFocus.translate
	(
		horizontalMove * cos(camTetha),
		verticalMove,
		horizontalMove * -sin(camTetha)
	);

	fishFocus.clampX(-AQUARIUM_COLLISION, AQUARIUM_COLLISION);
	fishFocus.clampY(-AQUARIUM_COLLISION, AQUARIUM_COLLISION);
	fishFocus.clampZ(-AQUARIUM_COLLISION, AQUARIUM_COLLISION);				

	/* Atualiza posicao do peixe */
	fishHead.updatePosition(); 
	fishDorsal.updatePosition(); 
	fishTail.updatePosition();
	
	/* Atualiza posicao da luz */
	if(input::isKeyPressed('1')) {
		// Luz padrao
		glDisable(GL_LIGHT1); 
		glEnable(GL_LIGHT0);
	}
	else if(input::isKeyPressed('2')){
		// Luz darkmode
		glDisable(GL_LIGHT0); 
		glEnable(GL_LIGHT1);
	}
	else if(input::isKeyPressed('3')){
		// Desativa todas as luzes
		glDisable(GL_LIGHT0); 
		glDisable(GL_LIGHT1);
	}

	lightPos[0] = fishFocus.getX();
	lightPos[1] = fishFocus.getY();
	lightPos[2] = fishFocus.getZ();

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

	/* Atualiza a view */
	updateView();

	/* Chama o proximo frame */
	timeElapsed = std::chrono::system_clock::now() - startFrameTime;
	timeLeft = TARGET_DELTATIME * 1000 - timeElapsed.count();
	timeLeft = clamp(timeLeft, 0, timeLeft);

	glutTimerFunc(timeLeft, update, value + 1);
}

void draw() {
	/* Parametros gl */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, camWidth, camHeight);
	glEnable(GL_BLEND);

	/* Cabeca do peixe */
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

	/* Corpo do peixe */
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

	/* Cauda do peixe */
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
	
	/* Isca */
	glPushMatrix();	
		glTranslatef(
			fishFocus.getX(), 
			fishFocus.getY(), 
			fishFocus.getZ());

		glRotatef(fishFocus.getRotationY(), 0, 1, 0);
		glRotatef(fishFocus.getRotationXZ(), 1, 0, 0);

		baitModel(3.0);
	glPopMatrix();	

	/* Castelo */
	glPushMatrix();
		castleModel(-100, -(AQUARIUM_SIZE / 2), -100, // X, Y, Z
			   60, 				     // Escala
			   0, 0, 0);			 // Rotação
	glPopMatrix();

	/* Aquario */
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

void updateView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camAngle, camAspect, 0.1, 3000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	tarX = lerp(fishFocus.getX(), tarX, CAM_TARGET_LERP);
	tarY = lerp(fishFocus.getY(), tarY, CAM_TARGET_LERP);
	tarZ = lerp(fishFocus.getZ(), tarZ, CAM_TARGET_LERP);

	gluLookAt(
			camX, 	camY, 	camZ,	// Cam-pos
			tarX, 	tarY, 	tarZ,	// Tar-pos
			0   , 	1   , 	0		// Normal
		);

	glutPostRedisplay();
}

void windowSizeUpdate(int width, int height) {
	height = height == 0 ? 1 : height;

	camWidth = width;
	camHeight = height;
	camAspect = (float)width / (float)height;
}

void setLight() {
	/* Variaveis */
	int expoent = 1024;

	float ambient[4] = {0, 0, 0, .3};
	float diffuse[4] = {1., 1., 1., .3};
	float specular[4] = {.5, .5, .5, .3};

	float ambientDark[4] = {0.1, 0, 0, .3};
	float diffuseDark[4] = {1., .6, .6, 1.};
	float specularDark[4] = {1., .5, .5, 1.};

	float specularity[4] = {.1, .15, .1, 1.};
	float lightPos[4] = {0., AQUARIUM_SIZE, 100., 1.};

	/* Luz padrao */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	/* Luz darkmode */
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientDark);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseDark);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularDark);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

	/* Outros parametros */
	glShadeModel(GL_SMOOTH);

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

int normalize(double value, double min, double max) {
	return (value - min) / (max - min);
}

double lerp(double a, double b, float l) {
	return a * l + b * (1 - l);
}

double clamp(double value, double min, double max) {
	return value < min ? min : value > max ? max : value;
}