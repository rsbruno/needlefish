/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
2 * UNIFAL − Universidade Federal de Alfenas.
3 * BACHARELADO EM CIENCIA DA COMPUTACAO.
4 * Trabalho . . : Marca D’ agua invisivel
5 * Disciplina . : Processamento de Imagens
6 * Professor. . : Luiz Eduardo da Silva
7 * Aluno . .  . : Bruno Roberto Santos
8 * Data  . .  . : 27/07/2021
9 *−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"

void waterMark(image In, image Out, int nl, int nc, int mn, image ORG)
{
    int i, j;
    for (i = 0; i < nl; i++)
        for (j = 0; j < nc; j++)
            Out[i * nc + j] = ((In[i * nc + j] & 0x03) | (ORG[i * nc + j] & 0x03)) * 85;
}

void msg(char *s)
{
    printf("\nWaterMark");
    printf("\n-------------------------------");
    printf("\nUsage:  %s  <IMG.PGM>\n\n", s);
    printf("    <IMG.PGM> is pgm image file \n\n");
    exit(1);
}

// void invisibleWaterMark(image In, int nl, int nc, image Mk, int nlmk, int ncmk, int mnmk,image Out)
// {
//     int i, j, alpha = 0.2;
//     for (i = 0; i < nlmk; i++)
//         for (j = 0; j < ncmk; j++)
//         {
//             //Out[i * nc + j] = round((1-alpha) * In[i * nc + j] + alpha *Mk[i * ncmk + j]);
//             In[i * nc + j] = ((In[i * nc + j] & 0xfa) ^ (Mk[i * ncmk + j] >> 6));
//         }
// }

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int OK, nc, nr, ml,
        nc_mk, nr_mk, ml_mk,
        nc_org, nr_org, ml_org;
    char name[100];
    char command[110];
    image In, Out, Original,Mark;
    if (argc < 2)
        msg(argv[0]);

    In = img_readpgm(argv[2], &nr, &nc, &ml);
    Original = img_readpgm(argv[1], &nc_org, &nr_org, &ml_org);
    //Mark = img_readpgm("minhamarca.pgm", &nc_mk, &nr_mk, &ml_mk);

    printf("\nWaterMark");
    img_info(argv[1], nr, nc, ml);
    Out = img_alloc(nr, nc);

    /*-- transformation --*/
    waterMark(In, Out, nr, nc, ml, Original);
    //invisibleWaterMark(In,nr,nc,Mark,nr_mk,nc_mk,ml_mk,Out);

    sprintf(name, "%s-%s", argv[1], "saida.pgm");
    img_writepgm(Out, name, nr, nc, ml);
    sprintf(command, "%s %s &", VIEW, name);
    system(command);

    img_free(In);
    img_free(Out);
    return 0;
}
