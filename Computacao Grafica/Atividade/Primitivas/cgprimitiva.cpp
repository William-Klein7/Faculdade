#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

#define PI 3.14159265f

int g_posicao_x = 50;
int g_posicao_y = 50;
int g_largura = 1000;
int g_altura = 1000;
char g_titulo[] = "CG Atividade Primitivas - Casa Ajustada";
int g_idle = 0;
int g_timer = 0;
int g_timer_value = 1;

void gDesenha (void) {
    glClear (GL_COLOR_BUFFER_BIT); 
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    // 1. Eixos do plano (Vermelho Escuro)
    // O cruzamento (0,0) ficara no canto inferior esquerdo da casa
    glColor3f (0.5, 0.0, 0.0);
    glBegin (GL_LINES);
        glVertex2f (-10.0, 0.0); glVertex2f (10.0, 0.0); // Eixo X
        glVertex2f (0.0, -10.0); glVertex2f (0.0, 10.0); // Eixo Y
    glEnd ();

    // 2. Base da Casa (Azul Forte)
    // Deixamos um espaço nas laterais para ficar igual à imagem (x vai de 1 a 7)
    glColor3f (0.0, 0.0, 1.0); 
    glBegin (GL_QUADS);
        glVertex2f ( 1.0,  0.0);
        glVertex2f ( 7.0,  0.0);
        glVertex2f ( 7.0,  5.0);
        glVertex2f ( 1.0,  5.0);
    glEnd ();

    // 3. Telhado (Amarelo)
    // As pontas tocam exatamente as bordas do quadrado delimitador (x=0 e x=8, y=8 no topo)
    glColor3f (1.0, 1.0, 0.0); 
    glBegin (GL_TRIANGLES);
        glVertex2f ( 0.0,  5.0); // Ponta esquerda toca x=0
        glVertex2f ( 8.0,  5.0); // Ponta direita toca x=8
        glVertex2f ( 4.0,  8.0); // Topo toca y=8 (centro em x=4)
    glEnd ();

    // 4. Porta (Cinza)
    glColor3f (0.6, 0.6, 0.6); 
    glBegin (GL_QUADS);
        glVertex2f ( 1.5,  0.0);
        glVertex2f ( 3.0,  0.0);
        glVertex2f ( 3.0,  3.5);
        glVertex2f ( 1.5,  3.5);
    glEnd ();

    // 5. Maçaneta da Porta (Ponto Preto)
    glColor3f (0.0, 0.0, 0.0);
    glPointSize (4.0);
    glBegin (GL_POINTS);
        glVertex2f ( 2.7,  1.7);
    glEnd ();

    // 6. Fundo da Janela (Cinza)
    glColor3f (0.6, 0.6, 0.6);
    glBegin (GL_QUADS);
        glVertex2f ( 4.0,  1.5);
        glVertex2f ( 6.5,  1.5);
        glVertex2f ( 6.5,  3.5);
        glVertex2f ( 4.0,  3.5);
    glEnd ();

    // 7. Grades da Janela (Linhas Pretas)
    glColor3f (0.0, 0.0, 0.0);
    glBegin (GL_LINES);
        glVertex2f ( 5.25, 1.5); glVertex2f ( 5.25, 3.5); // Vertical
        glVertex2f ( 4.0,  2.5); glVertex2f ( 6.5,  2.5); // Horizontal
    glEnd ();

    // 8. Contorno Quadrado Azul (Caixa Delimitadora)
    // O quadrado vai exatamente de (0,0) a (8,8), que é o tamanho máximo ocupado pela casa
    glColor3f (0.0, 0.0, 0.5); // Azul Escuro
    glBegin (GL_LINE_LOOP);
        glVertex2f ( 0.0,  0.0);
        glVertex2f ( 8.0,  0.0);
        glVertex2f ( 8.0,  8.0);
        glVertex2f ( 0.0,  8.0);
    glEnd ();

    // 9. Círculo Preto Espesso ao redor do quadrado
    glColor3f (0.0, 0.0, 0.0);
    glLineWidth (4.0); 
    glBegin (GL_LINE_LOOP);
        // O centro do quadrado é (4,4). A distância do centro até o canto (0,0) é a raiz quadrada de 32.
        float cx = 4.0f; 
        float cy = 4.0f; 
        float raio = sqrt(32.0f); 
        
        for (int i = 0; i < 100; i++) {
            float angulo = 2.0f * PI * float(i) / 100.0f;
            float x = cx + (raio * cosf(angulo));
            float y = cy + (raio * sinf(angulo));
            glVertex2f (x, y);
        }
    glEnd ();
    glLineWidth (1.0); // Retorna a espessura da linha ao normal

    glutSwapBuffers ();
}

void gRedimensiona (GLsizei largura, GLsizei altura) {;}
void gTeclado (unsigned char tecla, int x, int y) {;}
void gEspeciais (int tecla, int x, int y) {;}
void gMouse (int botao, int estado, int x, int y) {;}
void gMousePressionado (int x, int y) {;}
void gMouseLiberado (int x, int y) {;}
void gMouseScroll (int botao, int direcao, int x, int y) {;}
void gSistemaOcioso (void) {;}
void gTempoExecucao (int valor) {;}
void gMenuTeclado (void) {;}
void gMenuJanela (void) {;}

void gInicializa (void) {
    glClearColor (1.0, 1.0, 1.0, 1.0); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    // Sistema de coordenadas continua de -10 a 10 para visualizarmos tudo em escala
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); 
}

int main (int argc, char *argv[]) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (g_posicao_x, g_posicao_y);
    glutInitWindowSize (g_largura, g_altura);
    glutCreateWindow (g_titulo);
    
    glutDisplayFunc (gDesenha);
    glutReshapeFunc (gRedimensiona);
    glutKeyboardFunc (gTeclado);
    glutSpecialFunc (gEspeciais);
    glutMouseFunc (gMouse);
    glutMotionFunc (gMousePressionado);
    glutPassiveMotionFunc (gMouseLiberado);
    glutMouseWheelFunc (gMouseScroll);
    
    if (g_idle) glutIdleFunc (gSistemaOcioso);
    if (g_timer) glutTimerFunc (g_timer_value, gTempoExecucao, 1);
    
    gMenuTeclado ();
    gMenuJanela ();
    gInicializa ();
    
    glutMainLoop ();
    
    system ("pause");
    return 0;
}