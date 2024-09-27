/* 
 * Funcoes para o gerenciamento do mouse e teclado.
 */

/*----------------------------------------------------------------------------------------*/
// BIBLIOTECAS

#include "../includes/libpack.h"
#include <iostream>
#include <GL/glut.h>

/*----------------------------------------------------------------------------------------*/
// IMPLEMENTACAO DAS FUNCOES

void input::keyboardDown(unsigned char key, int x, int y) {
    pressedKeys[(int)key] = true;

    // Finalizar simulação (esc)
    if((int)key == 27) {
        glutDestroyWindow(0); 
        exit(0);
    }
}

void input::keyboardUp(unsigned char key, int x, int y) {
    pressedKeys[(int)key] = false;
}

void input::specialKeysDown(int key, int x, int y) {
    pressedSpecialKeys[key] = true;
}

void input::specialKeysUp(int key, int x, int y) {
    pressedSpecialKeys[key] = false;
}

void input::mouseManager(int button, int state, int x, int y) {
    pressedMouse[button] = (state == GLUT_DOWN);
    switch(button)
    {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3:
            if(state == GLUT_DOWN)
                mouseWheelCount--;
            break;
        case 4:
            if(state == GLUT_DOWN) 
                mouseWheelCount++;
            break;
    }
}

bool input::isKeyPressed(unsigned char key) {
    return pressedKeys[(int)key];
}

bool input::isSpecialKeyPressed(int key) {
    return pressedSpecialKeys[key];
}

bool input::isMouseButtonPressed(int button){
    return pressedMouse[button];
}

bool input::isUpPressed() {
    return 
        input::isKeyPressed('w') ||
        input::isKeyPressed('W') ||
        input::isSpecialKeyPressed(GLUT_KEY_UP);
}

bool input::isDownPressed() {
    return 
        input::isKeyPressed('s') || 
        input::isKeyPressed('S') ||
        input::isSpecialKeyPressed(GLUT_KEY_DOWN);
}

bool input::isLeftPressed() {
    return 
        input::isKeyPressed('a') || 
        input::isKeyPressed('A') ||
        input::isSpecialKeyPressed(GLUT_KEY_LEFT);
}

bool input::isRightPressed() {
    return 
        input::isKeyPressed('d') || 
        input::isKeyPressed('D') ||
        input::isSpecialKeyPressed(GLUT_KEY_RIGHT);
}

short input::getHorizontalAxis() {
    if(input::isLeftPressed() && !input::isRightPressed()) return -1;
    if(!input::isLeftPressed() && input::isRightPressed()) return 1;
    return 0;
}

short input::getVerticalAxis() {
    if(input::isDownPressed() && !input::isUpPressed()) return -1;
    if(!input::isDownPressed() && input::isUpPressed()) return 1;
    return 0;
}

short input::getMouseButtonAxis() {
    if(pressedMouse[GLUT_LEFT_BUTTON] && !pressedMouse[GLUT_RIGHT_BUTTON]) return -1;
    if(!pressedMouse[GLUT_LEFT_BUTTON] && pressedMouse[GLUT_RIGHT_BUTTON]) return 1;
    return 0;
}

short input::getMouseWheel() {
    if(mouseWheelCount > 0)
    {
        mouseWheelCount--;

        if(mouseWheelCount > 5)
            mouseWheelCount = 5;

        return 1;
    }
    else if(mouseWheelCount < 0) 
    {
        mouseWheelCount++;

        if(mouseWheelCount < -5)
            mouseWheelCount = -5;

        return -1;
    }
    else
        return 0;
}
