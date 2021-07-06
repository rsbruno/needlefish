/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Mediana from grayscale image
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"

void histograma(image In, int *histo, int nl, int nc, int mn)
{
    int i;
    for (i = 0; i <= mn; i++)
        histo[i] = 0;
    for (i = 0; i <= nl * nc; i++)
        histo[In[i]]++;
}

void mostra(int *histo, int mn)
{
    for (int i = 0; i <= mn; i++)
        printf("h[%3d] = %d ", i, histo[i]);
}

void equaliza(image In, image Out, int *histo, int nl, int nc, int mn)
{
    float pk[mn + 1], ak[mn + 1];
    int sk[mn + 1];

    for (int i = 1; i <= mn; i++)
    {
        //CÁLCULO DE PROBABILIDADE
        pk[i] = (float)histo[i] / (nl * nc);
        //CÁLCULO DO ACUMULADOR DE PROBABILIDADE
        i == 0 ? (ak[0] = pk[0]) : (ak[i] = ak[i - 1] + pk[i]);
        //RESULTADO DA EQUALIZAÇÃO
        sk[i] = ak[i] * mn;
    }

    //CONSTRUINDO A IMAGEM DE SAÍDA
    for (int i = 0; i <= nl * nc; i++)
        Out[i] = sk[In[i]];
}

void msg(char *s)
{
    printf("Histograma");
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
    int *histo;
    char name[100];
    char command[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    In = img_readpgm(argv[1], &nr, &nc, &ml);
    printf("\nHistograma");
    img_info(argv[1], nr, nc, ml);
    histo = (int *)malloc(sizeof(int) * ml);
    Out = img_alloc(nr, nc);

    histograma(In, histo, nr, nc, ml);
    //mostra(histo, ml);
    equaliza(In, Out, histo, nr, nc, ml);

    //sprintf(name, "%s-%s", argv[1], "Mediana.pgm");
    img_writepgm(Out, "saida.pgm", nr, nc, ml);
    // sprintf(command, "%s %s &", VIEW, name);
    // system(command);
    img_free(In);
    img_free(Out);
    return 0;
}
