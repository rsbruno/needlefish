/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
2 ∗         UNIFAL − Universidade Federal de Alfenas.
3 ∗           BACHARELADO EM CIENCIA DA COMPUTACAO.
4 ∗ Trabalho..: Rotulacao de componentes conexos.
5 ∗ Disciplina: Processamento de Imagens
6 ∗ Professor.: Luiz Eduardo da Silva
7 ∗ Aluno .....: Bruno Roberto Santos
8 ∗ Data . . . . . . : 08/07/2021
9 ∗−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"
#include "equivalencia.h"
#include "thresholding.h"

void msg(char *s)
{
    printf("\nImage Mediana");
    printf("\n-------------------------------");
    printf("\nUsage:  %s  <IMG.PGM>\n\n", s);
    printf("    <IMG.PGM> is pgm image file \n\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    int nc, nr, ml, rotulo = 0;

    int r, t;
    image In;
    if (argc < 2)
        msg(argv[0]);

    //Quando faço a leitura da Imagem ja transformo em preto e branco
    In = thresholding(img_readpgm(argv[1], &nr, &nc, &ml), nr, nc, ml);

    //Digo ao algoritmo qual a tonalidade é branco
    int white = 255;

    for (int i = 0; i < nr * nc; i++)
        if (In[i] != white)
        {
            r = In[i - nc];
            t = In[i - 1];

            if (t == white && r == white)
            {
                In[i] = --rotulo;
                insertFirst(In[i], 0);
            }
            else if (t != white && r == white)
                In[i] = t;
            else if (t == white && r != white)
                In[i] = r;
            else
            {
                if (t == r)
                    In[i] = r;
                else
                {
                    In[i] = t;
                    insertFirst(r, t);
                }
            }
        }

    printf("\nContador de Componentes Conexos");
    printf("\nArquivo %s", argv[1]);
    printf("\n-------------------------------\n");
    printf("\n#componentes = %d\n\n", length());
    img_free(In);
    return 0;
}