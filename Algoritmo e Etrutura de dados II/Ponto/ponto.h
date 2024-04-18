#include <stdio.h>
#include <math.h>

typedef struct
{
    float x, y;
} ponto;

void setx(ponto *p, float x)
{
    p->x = x;
}

void sety(ponto *p, float y)
{
    p->y = y;
}

void setponto(ponto *p, float x, float y)
{
    p->x = x;
    p->y = y;
}

float getx(ponto *p)
{
    return p->x;
}

float gety(ponto *p)
{
    return p->y;
}

float ponto_origem(ponto *p)
{
    return sqrt(pow(p->x, 2) + pow(p->y, 2));
}

float ponto_distancia(ponto *a, ponto *b)
{
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}