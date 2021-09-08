#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"

void ponto(image In, image Out, int nl, int nc, int mn)
{
    int i, j;
    int mask[3][3] = {
        -1, -1, -1,
        0, 0, 0,
        1, 1, 1};
    for (i = 0; i < nl - 1; i++)
        for (j = 0; j < nc - 1; j++)
        {
            int y, x, peso, soma = 0;
            for (y = -1; y <= 1; y++)
                for (x = -1; x <= 1; x++)
                {
                    // if (!y && !x)
                    //     peso = 8;
                    // else
                    //     peso = -1;
                    peso = mask[y + 1][x + 1];
                    soma += peso * In[(i + y) * nc + j + x];
                }
            if (abs(soma) > (255))
                Out[i * nc + j] = 255;
            else
                Out[i * nc + j] = 0;
        }
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
    ponto(In, Out, nr, nc, ml);

    printf("nivel max %d", ml);

    //sprintf(name, "%s-%s", argv[1], "negative.pgm");
    img_writepgm(Out, "saida.pgm", nr, nc, ml);
    // sprintf(command, "%s %s &", VIEW, name);
    // system(command);
    img_free(In);
    img_free(Out);
    return 0;
}
