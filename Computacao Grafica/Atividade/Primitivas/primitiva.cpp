#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

#define PI 3.14159265f

int g_posicao_x = 50;
int g_posicao_y = 50;
int g_largura = 800;
int g_altura = 800;
char g_titulo[] = "Primitivas Graficas - Todos os Quadrantes";
int g_idle = 0;
int g_timer = 0;
int g_timer_value = 1;

void gDesenha (void) {
    glClear (GL_COLOR_BUFFER_BIT); 
    glMatrixMode (GL_MODELVIEW); 
    glLoadIdentity();
    
    glColor3f (1.0, 0.0, 0.0);
    glBegin (GL_LINES);
        glVertex2f (-10.0, 0.0); glVertex2f ( 10.0, 0.0); // X
        glVertex2f ( 0.0, -10.0); glVertex2f ( 0.0,  10.0); // Y
    glEnd ();
    
    // QUADRANTE 2 - Formas Vermelhas
    glColor3f (1.0, 0.0, 0.0);
    
    glBegin (GL_TRIANGLES);
        glVertex2f (-9.0, 8.0); glVertex2f (-8.0, 7.0); glVertex2f (-7.0, 8.0);
        glVertex2f (-6.0, 7.0); glVertex2f (-5.0, 8.0); glVertex2f (-4.0, 7.0);
    glEnd ();
    
    glBegin (GL_TRIANGLE_STRIP);
        glVertex2f (-9.0, 6.0); glVertex2f (-8.0, 5.0); glVertex2f (-7.0, 6.0);
        glVertex2f (-6.0, 5.0); glVertex2f (-5.0, 6.0); glVertex2f (-4.0, 5.0);
    glEnd ();
    
    glBegin (GL_QUADS);
        glVertex2f (-9.0, 3.0); glVertex2f (-9.0, 1.0); 
        glVertex2f (-8.0, 1.0); glVertex2f (-8.0, 3.0);
    glEnd ();
    
    glBegin (GL_QUAD_STRIP);
        glVertex2f (-7.0, 3.0); glVertex2f (-7.0, 1.0);
        glVertex2f (-5.0, 3.0); glVertex2f (-5.0, 1.0);
        glVertex2f (-3.0, 4.0); glVertex2f (-3.0, 0.0);
        glVertex2f (-1.0, 3.0); glVertex2f (-1.0, 1.0);
    glEnd ();
    
    glBegin (GL_TRIANGLE_FAN);
        glVertex2f (-2.0, 9.0); glVertex2f (-4.0, 7.0);
        glVertex2f (-3.0, 6.0); glVertex2f (-1.0, 6.0); glVertex2f ( 0.0, 7.0);
    glEnd ();

    // QUADRANTE 3 - Linhas Pretas
    glColor3f (0.0, 0.0, 0.0);
    
    glBegin (GL_LINE_STRIP);
        glVertex2f (-9.0, -1.0); glVertex2f (-8.0, -2.0); glVertex2f (-7.0, -1.0);
        glVertex2f (-6.0, -2.0); glVertex2f (-5.0, -1.0); glVertex2f (-4.0, -2.0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
        glVertex2f (-9.0, -5.0); glVertex2f (-8.0, -6.0); glVertex2f (-7.0, -5.0);
        glVertex2f (-6.0, -6.0); glVertex2f (-5.0, -5.0); glVertex2f (-4.0, -6.0);
    glEnd ();
    
    glBegin (GL_LINE_STRIP);
        glVertex2f (-2.0, -1.0); glVertex2f (-4.0, -3.0); glVertex2f (-3.0, -4.0);
        glVertex2f (-1.0, -4.0); glVertex2f ( 0.0, -3.0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
        glVertex2f (-2.0, -5.0); glVertex2f (-4.0, -7.0); glVertex2f (-3.0, -8.0);
        glVertex2f (-1.0, -8.0); glVertex2f ( 0.0, -7.0);
    glEnd ();

    // QUADRANTE 4 - Formas Circulares
    float cx, cy, raio = 2.0f;
    int i;

    // 1. LINES (Circulo Tracejado)
    cx = 3.0f; cy = -3.0f;
    glBegin(GL_LINES);
    for(i = 0; i < 30; i += 2) {
        glVertex2f(cx + raio * cosf(2.0f * PI * i / 30.0f), cy + raio * sinf(2.0f * PI * i / 30.0f));
        glVertex2f(cx + raio * cosf(2.0f * PI * (i+1) / 30.0f), cy + raio * sinf(2.0f * PI * (i+1) / 30.0f));
    }
    glEnd();

    // 2. LINE_STRIP (Circulo Aberto)
    cx = 7.0f; cy = -3.0f;
    glBegin(GL_LINE_STRIP);
    for(i = 0; i < 28; i++) { // Vai até 28 para deixar um buraco no desenho
        glVertex2f(cx + raio * cosf(2.0f * PI * i / 30.0f), cy + raio * sinf(2.0f * PI * i / 30.0f));
    }
    glEnd();

    // 3. LINE_LOOP (Circulo Fechado)
    cx = 3.0f; cy = -7.0f;
    glBegin(GL_LINE_LOOP);
    for(i = 0; i < 30; i++) {
        glVertex2f(cx + raio * cosf(2.0f * PI * i / 30.0f), cy + raio * sinf(2.0f * PI * i / 30.0f));
    }
    glEnd();

    // 4. POINTS (Circulo Pontilhado)
    cx = 7.0f; cy = -7.0f;
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for(i = 0; i < 20; i++) {
        glVertex2f(cx + raio * cosf(2.0f * PI * i / 20.0f), cy + raio * sinf(2.0f * PI * i / 20.0f));
    }
    glEnd();
    
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