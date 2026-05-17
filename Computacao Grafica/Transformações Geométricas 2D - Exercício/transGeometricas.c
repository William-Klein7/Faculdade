#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include "plano.h"
#include "casa.h"
#define TAM_JANELA 100.00

#define CASA_ALTURA 50.0f
#define CASA_ESCALA_BASE 0.45f
#define CASA_PIVO_X 25.0f
#define CASA_PIVO_Y 25.0f

#define QUADRANTE_1_X 50.0f
#define QUADRANTE_1_Y 50.0f
#define QUADRANTE_2_X -50.0f
#define QUADRANTE_2_Y 50.0f
#define QUADRANTE_3_X -50.0f
#define QUADRANTE_3_Y -50.0f
#define QUADRANTE_4_X 50.0f
#define QUADRANTE_4_Y -50.0f

int translacao = 0, rotacao = 0, escala = 0;
int angulo_rotacao = 0;
int x_translacao = 0;
int y_translacao = 0;
float x_escala = 1.0;
float y_escala = 1.0;

int g_posicao_x = 50;
int g_posicao_y = 50;
int g_largura = 500;
int g_altura = 500;
char g_titulo[] = "Tranformacoes Geometricas";
int g_idle = 0;
int g_timer = 0;
int g_timer_value = 1;

void DesenhaCasaBase(void)
{
    DesenhaCasa(0, 0, CASA_ALTURA, 1);
}

void gDesenha(void)
{
    glEnable(GL_DEPTH_TEST);                            // Habilita buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicialização
    glMatrixMode(GL_MODELVIEW);                         // Sistema de Coordendas do modelo

    glPushMatrix();
    DesenhaPlano(TAM_JANELA, 1, 1, 1);
    glPopMatrix();

    // 1o quadrante: casa base
    glPushMatrix();
    glTranslatef(QUADRANTE_1_X, QUADRANTE_1_Y, 0.0f);
    glScalef(CASA_ESCALA_BASE, CASA_ESCALA_BASE, 1.0f);
    DesenhaCasaBase();
    glPopMatrix();

    // 2o quadrante: aplica apenas rotacao
    glPushMatrix();
    glTranslatef(QUADRANTE_2_X, QUADRANTE_2_Y, 0.0f);
    glScalef(CASA_ESCALA_BASE, CASA_ESCALA_BASE, 1.0f);
    glTranslatef(CASA_PIVO_X, CASA_PIVO_Y, 0.0f);
    glRotatef(angulo_rotacao, 0, 0, 1);
    glTranslatef(-CASA_PIVO_X, -CASA_PIVO_Y, 0.0f);
    DesenhaCasaBase();
    glPopMatrix();

    // 3o quadrante: aplica apenas translacao
    glPushMatrix();
    glTranslatef(QUADRANTE_3_X, QUADRANTE_3_Y, 0.0f);
    glTranslatef(x_translacao, y_translacao, 0.0f);
    glScalef(CASA_ESCALA_BASE, CASA_ESCALA_BASE, 1.0f);
    DesenhaCasaBase();
    glPopMatrix();

    // 4o quadrante: aplica apenas escala
    glPushMatrix();
    glTranslatef(QUADRANTE_4_X, QUADRANTE_4_Y, 0.0f);
    glScalef(CASA_ESCALA_BASE, CASA_ESCALA_BASE, 1.0f);
    glTranslatef(CASA_PIVO_X, CASA_PIVO_Y, 0.0f);
    glScalef(x_escala, y_escala, 1.0f);
    glTranslatef(-CASA_PIVO_X, -CASA_PIVO_Y, 0.0f);
    DesenhaCasaBase();
    glPopMatrix();

    glutSwapBuffers();
}

void gRedimensiona(GLsizei largura, GLsizei altura)
{

    GLsizei a_l, l_a;

    if (altura == 0)
        altura = 1;
    a_l = altura / largura;
    l_a = largura / altura;

    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (largura <= altura)
        gluOrtho2D(-TAM_JANELA, TAM_JANELA, (-TAM_JANELA * a_l), (TAM_JANELA * a_l));
    else
        gluOrtho2D((-TAM_JANELA * l_a), (TAM_JANELA * l_a), -TAM_JANELA, TAM_JANELA);
}

void gTeclado(unsigned char tecla, int x, int y)
{

    if (tecla == 27)
        exit(0);
    if (tecla == 't')
    {
        printf("Translacao OK\n");
        translacao = 1;
        rotacao = escala = 0;
    }

    if (tecla == 'e')
    {
        printf("Escala OK\n");
        escala = 1;
        rotacao = translacao = 0;
    }

    if (tecla == 'r')
    {
        printf("Rotacao OK %d, %d\n", x, y);
        rotacao = 1;
        translacao = escala = 0;
    }
}
void gEspeciais(int tecla, int x, int y)
{

    if (tecla == GLUT_KEY_UP)
    {
        printf("Tecla UP");
        if (translacao)
        {
            y_translacao += 5;
        }

        if (escala)
        {
            y_escala += 0.1;
        }
    }
    if (tecla == GLUT_KEY_DOWN)
    {
        printf("Tecla DOWN");
        if (translacao)
        {
            y_translacao -= 5;
        }

        if (escala)
        {
            y_escala -= 0.1;
        }
    }

    if (tecla == GLUT_KEY_LEFT)
    {
        printf("Tecla LEFT");
        if (translacao)
        {
            x_translacao -= 5;
        }

        if (escala)
        {
            x_escala -= 0.1;
        }

        if (rotacao)
        {
            angulo_rotacao += 5;
        }
    }

    if (tecla == GLUT_KEY_RIGHT)
    {
        printf("Tecla RIGHT");
        if (translacao)
        {
            x_translacao += 5;
        }

        if (escala)
        {
            x_escala += 0.1;
        }

        if (rotacao)
        {
            angulo_rotacao -= 5;
        }
    }

    glutPostRedisplay();
}
void gMouse(int botao, int estado, int x, int y) { ; }
void gMousePressionado(int x, int y) { ; }
void gMouseLiberado(int x, int y) { ; }
void gMouseScroll(int botao, int direcao, int x, int y) { ; }

void gSistemaOcioso(void) { ; }
void gTempoExecucao(int valor) { ; }
void gMenuTeclado(void) { ; }
void gMenuJanela(void) { ; }
void gInicializa(void)
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-TAM_JANELA, TAM_JANELA, -TAM_JANELA, TAM_JANELA); // Define a janela de visualização 2D
}

int main(int argc, char *argv[])
{

    // Instruções de inicialização da utilização da api

    glutInit(&argc, argv); // Inicialização da GLUT
    // buffer duplo para construção de imagem
    // remoção de superfícies escondidas e sistema cor
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    // posição da imagem - canto superior esquerdo (x,y)
    glutInitWindowPosition(g_posicao_x, g_posicao_y);
    // definição da largura e altura da janela
    glutInitWindowSize(g_largura, g_altura);
    // título e criação da janela
    glutCreateWindow(g_titulo);

    // Declaração de callbacks

    // desenho de objetos gráficos
    glutDisplayFunc(gDesenha);
    // redimensionamento da janela de exibição
    glutReshapeFunc(gRedimensiona);
    // pressionamento de teclas comuns
    glutKeyboardFunc(gTeclado);
    // pressionamento de teclas especiais
    glutSpecialFunc(gEspeciais);
    // eventos de pressionamento/liberação mouse
    glutMouseFunc(gMouse);
    // movimento do mouse enquanto pressionado
    glutMotionFunc(gMousePressionado);
    // movimento do mouse enquanto liberado
    glutPassiveMotionFunc(gMouseLiberado);
    // eventos do mouse scroll
    glutMouseWheelFunc(gMouseScroll);

    // Callbacks e Funções auxiliares
    if (g_idle)
        glutIdleFunc(gSistemaOcioso); // Quando da ociosidade do sistema
    if (g_timer)
        glutTimerFunc(g_timer_value, gTempoExecucao, 1); // Quando trabalhar com animaçção

    gMenuTeclado();
    gMenuJanela();
    gInicializa();

    glutMainLoop();

    system("pause");
    return 0;
}
