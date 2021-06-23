/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Negative from grayscale image
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"
#include <math.h>

void transform(image In, image Out, int nl, int nc, int mn)
{
   //  *  CLAREAR OU ESCURECER USANDO POTÊNCIA
    /*  
     
     *  O que define se estamos escurencendo ou clareando é variável nível
     *  se um inteiro escurece, se um ponto flutuante de 0 e 1 clareia
     
        int i;
        double nivel = .2;
        double T[mn + 1]; // escala de Transformação

        //  Gera a escala de transformação
        for (i = 0; i < mn + 1; i++)
            T[i] = pow(i, nivel) / pow(mn, nivel) * mn;

        //  Percorre toda a matriz de saída pegando o número na escala de transformação
        for (i = 0; i < nl * nc; i++)
            Out[i] = (int)T[In[i]];
    
    */

    //  * CLAREAR USANDO LOG
    /*
        int i;
        double nivel = 1;
        double T[mn + 1]; // escala de Transformação

        //  Gera a escala de transformação
        for (i = 0; i < mn + 1; i++)
            T[i] = log(i + nivel) / log(mn + nivel) * mn;

        //  Percorre toda a matriz de saída pegando o número na escala de transformação
        for (i = 0; i < nl * nc; i++)
            Out[i] = (int)T[In[i]];
    */

    int i;
    double nivel = 1;
    double T[mn + 1]; // escala de Transformação

    //  Gera a escala de transformação
    for (i = 0; i < mn + 1; i++)
        T[i] = i<200?0:mn;

    //  Percorre toda a matriz de saída pegando o número na escala de transformação
    for (i = 0; i < nl * nc; i++)
        Out[i] = (int)T[In[i]];
}

void msg(char *s)
{
    printf("\nImagem Intensidade");
    printf("\n-------------------------------");
    printf("\nUsage:  %s  <IMG.PGM>\n\n", s);
    printf("    <IMG.PGM> is pgm image file \n\n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int OK, nc, nr, ml;
    char name[100];
    char command[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    In = img_readpgm(argv[1], &nr, &nc, &ml);
    printf("\nImage");
    img_info(argv[1], nr, nc, ml);
    Out = img_alloc(nr, nc);

    /*-- transformation --*/
    transform(In, Out, nr, nc, ml);

    sprintf(name, "resultado.pgm");
    img_writepgm(Out, name, nr, nc, ml);
    sprintf(command, "%s %s &", VIEW, name);
    system(command);
    img_free(In);
    img_free(Out);
    return 0;
}
