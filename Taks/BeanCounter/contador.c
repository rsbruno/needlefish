/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Mediana from grayscale image
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "imagelib.h"
#include "equivalencia.h"

void msg(char *s)
{
    printf("\nImage Mediana");
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
    int nc, nr, ml, rotulo = 0;

    int r, t;
    image In;
    if (argc < 2)
        msg(argv[0]);

    In = img_readpgm(argv[1], &nr, &nc, &ml);

    //Digo ao algoritmo qual a tonalidade é branco
    int white = 0;

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
    for (int i = 0; i < nc * nr; i++)
    {
        if (i % 20 == 0)
            printf("\n");
        printf("%4d", In[i]);
    }
    //printList();
    printf("\n%d elementos\n", length());

    // //print_list(list_eqvl->list);
    // printf("%d", list_eqvl->count);

    //printf("\nImage Mediana");
    //img_info(argv[1], nr, nc, ml);
    //Out = img_alloc(nr, nc);

    /*-- transformation --*/
    //counter(In, Out, nr, nc, ml);

    //printf("nivel max %d", ml);

    //sprintf(name, "%s-%s", argv[1], "Mediana.pgm");
    //img_writepgm(Out, "saida.pgm", nr, nc, ml);
    // sprintf(command, "%s %s &", VIEW, name);
    // system(command);
    //img_free(In);
    // img_free(Out);
    return 0;
}
