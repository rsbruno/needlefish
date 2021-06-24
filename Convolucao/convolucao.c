/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Negative from grayscale image
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"

void tranf_local(image In, image Out, int nl, int nc, int mn)
{
    int i, j, y, x, soma = 0,
                    peso[3][3] = {
                        -1, -2, -1,
                        0, 0, 0,
                        1, 2, 1},
                    min = 1000, max = -1000, valor;

    for (int i = 1; i < nl - 1; i++)
        for (int j = 1; j < nc - 1; j++)
        {
            soma = 0;
            for (y = 0; y < 3; y++)
                for (x = 0; x < 3; x++)
                    soma += peso[y][x] * In[((i + y - 1) * nc + j + x - 1)];
            //valor = soma / 9;
            soma = soma < 0 ? 0 : soma;
            soma = soma > mn ? mn : soma;
            Out[i * nc + j] = mn - soma;
        }

    // for (int i = 0; i < nc * nl; i++)
    //     Out[i] = (float)(Out[i] - min) / (max )* (*mn);

    // printf("%d %d", min, max);
    // *mn = max;
}

void msg(char *s)
{
    printf("\nImage negative");
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
    printf("\nImage negative");
    img_info(argv[1], nr, nc, ml);
    Out = img_alloc(nr, nc);

    /*-- transformation --*/
    tranf_local(In, Out, nr, nc, ml);

    printf("nivel max %d", ml);

    //sprintf(name, "%s-%s", argv[1], "negative.pgm");
    img_writepgm(Out, "saida.pgm", nr, nc, ml);
    // sprintf(command, "%s %s &", VIEW, name);
    // system(command);
    img_free(In);
    img_free(Out);
    return 0;
}
