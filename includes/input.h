/* 
 * Funcoes para o gerenciamento do mouse e teclado.
 */

#ifndef INPUT_H
#define INPUT_H

/*----------------------------------------------------------------------------------------*/
// DECLARACAO DAS FUNCOES

namespace input{
    static bool pressedKeys[255];           // Lista de teclas ASCII pressionadas
    static bool pressedSpecialKeys[255];    // Lista de teclas especiais GLUT pressionadas
    static bool pressedMouse[3];            // Lista de botoes do mouse pressionados    
    static int mouseWheelCount;             // Contador do scroll do mouse

    void keyboardDown(unsigned char key, int x, int y);     	// Gatilho para tecla pressionada
    void keyboardUp(unsigned char key, int x, int y);       	// Gatilho para tecla liberada
    void exitKey(unsigned char key, int x, int y);		        // Gatilho para tecla de saída (X)
    void specialKeysDown(int key, int x, int y);            	// Gatilho para tecla especial pressionada
    void specialKeysUp(int key, int x, int y);              	// Gatilho para tecla especial liberada
    void mouseManager(int button, int state, int x, int y);     // Gerencia o mouse

    bool isKeyPressed(unsigned char key);       // Verifica se a tecla ASCII foi pressionada
    bool isSpecialKeyPressed(int key);          // Verifica se a tecla especial GLUT foi pressionada
    bool isMouseButtonPressed(int button);      // Verifica se botao do mouse foi pressionado

    bool isUpPressed();             // Verifica se W/UP foi pressionada
    bool isDownPressed();           // Verifica se S/DOWN foi pressionada
    bool isLeftPressed();           // Verifica se A/LEFT foi pressionada
    bool isRightPressed();          // Verifica se D/RIGHT foi pressionada

    void endSimulation();           // Finaliza a simulacao

    short getHorizontalAxis();      // Retorna a direcao horizontal (-1, 0 ou 1)
    short getVerticalAxis();      	// Retorna a direcao vertical (-1, 0 ou 1)
    short getMouseButtonAxis();     // Retorna a direcao do botao do mouse (-1, 0 ou 1)
    short getMouseWheel();          // Retorna a direcao da wheel do mouse (-1, 0 ou 1)
}

#endif
