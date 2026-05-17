#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

int g_posicao_x = 50, g_posicao_y = 50, g_largura = 500, g_altura = 500, g_idle = 0, g_timer = 0;
char g_titulo[] = "Projeto aula 2 2";

void gDesenha(void) {
  glEnable(GL_DEPTH_TEST); // Habilita o buffer de profundidade
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Definindo a inicialização
  glMatrixMode(GL_MODELVIEW); // Sistema de coordenadas do modelo de visualização

  glColor3f(0, 0, 0);
  glBegin(GL_LINE_LOOP);
    glVertex2i(-1,0);
    glVertex2i( 1,0);
  glEnd();

  glBegin(GL_LINE_LOOP);
    glVertex2i(0,-1);
    glVertex2i(0,1);
  glEnd();

  glutSwapBuffers(); //Sempre no final, apos desenhar tudo
 }
void gRedimensiona(GLsizei largura, GLsizei altura) { ; }
void gTeclado(unsigned char tecla, int x, int y) { ; }
void gEspeciais(int tecla, int x, int y) { ; }
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
  glClearColor (0, 1, 0, 0);
  glMatrixMode (GL_PROJECTION);
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

  int g_timer_value = 1;

  gInicializa();

  glutMainLoop();

  system("pause");

  return 0;
}