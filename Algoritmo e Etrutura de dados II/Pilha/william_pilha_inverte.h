void invertepilha(pilha *p)
{
  pilha aux, aux2;
  inicializapilha(&aux);
  inicializapilha(&aux2);
  while (!pilhavazia(p))
  {
    empilha(&aux, topopilha(p));
    desempilha(p);
  }
  while (!pilhavazia(&aux))
  {
    empilha(&aux2, topopilha(&aux));
    desempilha(&aux);
  }
  while (!pilhavazia(&aux2))
  {
    empilha(p, topopilha(&aux2));
    desempilha(&aux2);
  }
}