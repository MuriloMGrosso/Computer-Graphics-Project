#include "libpack.h"
#include <iostream>
#include <GL/glut.h>

void input::keyboardDown(unsigned char key, int x, int y) 
{
    int btn = (int)key;
    if(btn != 27) 	{ pressedKeys[(int)key] = true;   } // Registrar tecla
    else 		{ glutDestroyWindow(0); exit (0); } // Finalizar simulação (esc)
}

void input::keyboardUp(unsigned char key, int x, int y) 
{
    pressedKeys[(int)key] = false;
}

void input::specialKeysDown(int key, int x, int y) 
{
    pressedSpecialKeys[key] = true;
}

void input::specialKeysUp(int key, int x, int y) 
{
    pressedSpecialKeys[key] = false;
}

void input::mouseManager(int button, int state, int x, int y) {
    switch(button)
    {
        case 0:
        case 1:
        case 2:
            pressedMouse[button] = state == GLUT_DOWN;
            break;
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

bool input::isKeyPressed(unsigned char key) 
{
    return pressedKeys[(int)key];
}

bool input::isSpecialKeyPressed(int key) 
{
    return pressedSpecialKeys[key];
}

bool input::isMouseButtonPressed(int button)
{
    return pressedMouse[button];
}

bool input::isUpPressed() 
{
    return 
        input::isKeyPressed('w') ||
        input::isKeyPressed('W') ||
        input::isSpecialKeyPressed(GLUT_KEY_UP);
}

bool input::isDownPressed() 
{
    return 
        input::isKeyPressed('s') || 
        input::isKeyPressed('S') ||
        input::isSpecialKeyPressed(GLUT_KEY_DOWN);
}

bool input::isLeftPressed() 
{
    return 
        input::isKeyPressed('a') || 
        input::isKeyPressed('A') ||
        input::isSpecialKeyPressed(GLUT_KEY_LEFT);
}

bool input::isRightPressed() 
{
    return 
        input::isKeyPressed('d') || 
        input::isKeyPressed('D') ||
        input::isSpecialKeyPressed(GLUT_KEY_RIGHT);
}

bool input::isForwardPressed() 
{
    return false;
}

bool input::isBackwardPressed() 
{
    return false;
}


short input::getHorizontalAxis() 
{
    if(input::isLeftPressed() && !input::isRightPressed()) return -1;
    if(!input::isLeftPressed() && input::isRightPressed()) return 1;
    return 0;
}

short input::getVerticalAxis() 
{
    if(input::isDownPressed() && !input::isUpPressed()) return -1;
    if(!input::isDownPressed() && input::isUpPressed()) return 1;
    return 0;
}

short input::getDepthAxis()
{
    if(input::isForwardPressed() && !input::isBackwardPressed()) return -1;
    if(!input::isForwardPressed() && input::isBackwardPressed()) return 1;
    return 0;
}

short input::getMouseButtonAxis()
{
    if(pressedMouse[GLUT_LEFT_BUTTON] && !pressedMouse[GLUT_RIGHT_BUTTON]) return -1;
    if(!pressedMouse[GLUT_LEFT_BUTTON] && pressedMouse[GLUT_RIGHT_BUTTON]) return 1;
    return 0;
}

short input::getMouseWheel()
{
    if(mouseWheelCount > 0)
    {
        mouseWheelCount--;
        return 1;
    }
    else if(mouseWheelCount < 0) 
    {
        mouseWheelCount++;
        return -1;
    }
    else
        return 0;
}
