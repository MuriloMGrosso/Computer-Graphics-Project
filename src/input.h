/* 
 * Funcoes para o gerenciamento do mouse e teclado.
 */

#ifndef INPUT_H
#define INPUT_H

namespace input{
    static bool pressedKeys[255];           // Lista de teclas ASCII pressionadas
    static bool pressedSpecialKeys[255];    // Lista de teclas especiais GLUT pressionadas

    void mouseManager(int button, int state, int x, int y); // Gatilho para mouse
    void keyboardDown(unsigned char key, int x, int y);     // Gatilho para tecla pressionada
    void keyboardUp(unsigned char key, int x, int y);       // Gatilho para tecla liberada
    void specialKeysDown(int key, int x, int y);            // Gatilho para tecla especial pressionada
    void specialKeysUp(int key, int x, int y);              // Gatilho para tecla especial liberada

    bool isKeyPressed(unsigned char key);   // Verifica se a tecla ASCII foi pressionada
    bool isSpecialKeyPressed(int key);      // Verifica se a tecla especial GLUT foi pressionada
    bool isUpPressed();                     // Verifica se W ou UP foram pressionadas
    bool isDownPressed();                   // Verifica se S ou Down foram pressionadas
    bool isLeftPressed();                   // Verifica se A ou LEFT foram pressionadas
    bool isRightPressed();                  // Verifica se D ou RIGHT foram pressionadas

    short getHorizontalAxis();    // Retorna a direcao horizontal (-1, 0 ou 1)
    short getVerticalAxis();      // Retorna a direcao vertical (-1, 0 ou 1)
}

#endif