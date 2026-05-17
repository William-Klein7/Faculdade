#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// -------------------------------
// Parâmetros da câmera
// -------------------------------
float eyeX = 0.0f, eyeY = 2.0f, eyeZ = 6.0f;
float lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = 0.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

// Ângulos da câmera
float yaw   = -90.0f; // olhando para frente no eixo -Z
float pitch = 0.0f;

// Controle do mouse
int ultimoMouseX = 400;
int ultimoMouseY = 300;
bool primeiroMovimento = true;

// Projeção
bool usarPerspectiva = true;

// Janela
int largura = 800;
int altura  = 600;

// -------------------------------
// Atualiza LookAt com base em yaw/pitch
// -------------------------------
void atualizarDirecaoCamera() {
    float radYaw   = yaw   * (M_PI / 180.0f);
    float radPitch = pitch * (M_PI / 180.0f);

    float dirX = cos(radYaw) * cos(radPitch);
    float dirY = sin(radPitch);
    float dirZ = sin(radYaw) * cos(radPitch);

    lookAtX = eyeX + dirX;
    lookAtY = eyeY + dirY;
    lookAtZ = eyeZ + dirZ;
}

// -------------------------------
// Inicialização
// -------------------------------
void inicializarOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    atualizarDirecaoCamera();
}

// -------------------------------
// Projeção
// -------------------------------
void configurarProjecao() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspecto = (float)largura / (float)altura;

    if (usarPerspectiva) {
        gluPerspective(60.0, aspecto, 0.1, 100.0);
    } else {
        glOrtho(-4.0 * aspecto, 4.0 * aspecto, -4.0, 4.0, 0.1, 100.0);
    }
}

// -------------------------------
// Câmera
// -------------------------------
void configurarCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        eyeX, eyeY, eyeZ,
        lookAtX, lookAtY, lookAtZ,
        upX, upY, upZ
    );
}

// -------------------------------
// Objetos
// -------------------------------
void desenharObjeto(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidTeapot(0.8);
    glPopMatrix();
}

// -------------------------------
// Cena
// -------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    configurarProjecao();
    configurarCamera();

    desenharObjeto(-2.0f, 0.0f,  0.0f);
    desenharObjeto( 0.0f, 0.0f, -2.0f);
    desenharObjeto( 2.0f, 0.0f, -4.0f);

    glutSwapBuffers();
}

// -------------------------------
// Viewport
// -------------------------------
void reshape(int w, int h) {
    if (h == 0) h = 1;

    largura = w;
    altura = h;

    glViewport(0, 0, largura, altura);
}

// -------------------------------
// Movimento do mouse
// -------------------------------
void movimentoMouse(int x, int y) {
    if (primeiroMovimento) {
        ultimoMouseX = x;
        ultimoMouseY = y;
        primeiroMovimento = false;
    }

    int deltaX = x - ultimoMouseX;
    int deltaY = ultimoMouseY - y; // invertido para ficar natural

    ultimoMouseX = x;
    ultimoMouseY = y;

    float sensibilidade = 0.15f;
    yaw   += deltaX * sensibilidade;
    pitch += deltaY * sensibilidade;

    // Evita "virar" a câmera completamente
    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    atualizarDirecaoCamera();
    glutPostRedisplay();
}

// -------------------------------
// Teclado
// -------------------------------
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
        case 'P':
            usarPerspectiva = true;
            glutPostRedisplay();
            break;

        case 'o':
        case 'O':
            usarPerspectiva = false;
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
            break;
    }
}

// -------------------------------
// Main
// -------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("Camera com Mouse - OpenGL");

    inicializarOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Movimento do mouse sem clicar
    glutPassiveMotionFunc(movimentoMouse);

    glutMainLoop();
    return 0;
}