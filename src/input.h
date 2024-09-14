/* 
 * Funcoes para o gerenciamento do mouse e teclado.
 */

#ifndef INPUT_H
#define INPUT_H

namespace input{
    static bool pressedKeys[255];           			// Lista de teclas ASCII pressionadas
    static bool pressedSpecialKeys[255];    			// Lista de teclas especiais GLUT pressionadas
    
    void keyboardDown(unsigned char key, int x, int y);     	// Gatilho para tecla pressionada
    void keyboardUp(unsigned char key, int x, int y);       	// Gatilho para tecla liberada
    void exitKey(unsigned char key, int x, int y);		// Gatilho para tecla de saída (X)
    void specialKeysDown(int key, int x, int y);            	// Gatilho para tecla especial pressionada
    void specialKeysUp(int key, int x, int y);              	// Gatilho para tecla especial liberada

    bool isKeyPressed(unsigned char key);   			// Verifica se a tecla ASCII foi pressionada
    bool isSpecialKeyPressed(int key);      			// Verifica se a tecla especial GLUT foi pressionada
    bool isUpPressed();                     			// Verifica se W foi pressionada
    bool isDownPressed();                   			// Verifica se S foi pressionada
    bool isLeftPressed();                   			// Verifica se A foi pressionada
    bool isRightPressed();                  			// Verifica se D foi pressionada
    bool isForwardPressed();					// Verifica se UP foi pressionada
    bool isBackwardPressed();					// Verifica se DOWN foi pressionada

    void endSimulation();					// Finaliza a simulacao

    short getHorizontalAxis();    				// Retorna a direcao horizontal (-1, 0 ou 1)
    short getVerticalAxis();      				// Retorna a direcao vertical (-1, 0 ou 1)
    short getDepthAxis();					// Retorna a direcao em profundidade (-1, 0 ou 1) 
}

#endif
