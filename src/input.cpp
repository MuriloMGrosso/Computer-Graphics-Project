#include "input.h"
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

bool input::isKeyPressed(unsigned char key) 
{
    return pressedKeys[(int)key];
}

bool input::isSpecialKeyPressed(int key) 
{
    return pressedSpecialKeys[key];
}

bool input::isUpPressed() 
{
    return 
        input::isKeyPressed('w') ||
        input::isKeyPressed('W');
}

bool input::isDownPressed() 
{
    return 
        input::isKeyPressed('s') || 
        input::isKeyPressed('S');
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
    return 
        input::isSpecialKeyPressed(GLUT_KEY_UP);
}

bool input::isBackwardPressed() 
{
    return 
        input::isSpecialKeyPressed(GLUT_KEY_DOWN);
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
    if(input::isForwardPressed() && !input::isBackwardPressed())  return -1;
    if(!input::isForwardPressed() && input::isBackwardPressed()) return 1;
    return 0;
}
