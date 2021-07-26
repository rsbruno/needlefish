/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: waterMark from grayscale image
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"

void waterMark(image In, image Out, int nl, int nc, int mn, image ORG)
{
    int i, j;
    for (i = 0; i < nl; i++)
        for (j = 0; j < nc; j++)
        {
            if (In[i * nc + j] == ORG[i * nc + j])
                Out[i * nc + j] = 255;
            else
                Out[i * nc + j] = 0;
        }
}

void msg(char *s)
{
    printf("\nWaterMark");
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
    int OK, nc, nr, ml,
        nc_org, nr_org, ml_org;
    char name[100];
    char command[110];
    image In, Out, Original;
    if (argc < 2)
        msg(argv[0]);

    In = img_readpgm(argv[1], &nr, &nc, &ml);
    Original = img_readpgm("stanford.pgm", &nc_org, &nr_org, &ml_org);

    printf("\nWaterMark");
    img_info(argv[1], nr, nc, ml);
    Out = img_alloc(nr, nc);

    /*-- transformation --*/
    waterMark(In, Out, nr, nc, ml, Original);

    sprintf(name, "%s-%s", argv[1], "saida.pgm");
    img_writepgm(Out, name, nr, nc, ml);
    sprintf(command, "%s %s &", VIEW, name);
    system(command);

    img_free(In);
    img_free(Out);
    return 0;
}
