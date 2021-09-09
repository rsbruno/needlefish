#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagelib.h"

void desfoque(image In, image Grd, image Out, int nl, int nc, int mn)
{
    int aux = 0;
    int i, j, y, x;
    for (int i = 1; i < nl - 1; i++)
        for (int j = 1; j < nc - 1; j++)
        {
            aux = 0;
            for (y = 0; y < 3; y++)
            {
                for (x = 0; x < 3; x++)
                {
                    if (Grd[((i + y - 1) * nc + j + x - 1)] == 255)
                        aux += In[((i + y - 1) * nc + j + x - 1)]; else aux += 0;
                    //printf("%d - ",Grd[((i + y - 1) * nc + j + x - 1)]);
                }
            }
            //printf("\n");
            Out[i * nc + j] = aux == 0 ? In[i * nc + j] : (2*aux) / 18;

            // soma = 0;
            // for (y = 0; y < 3; y++)
            //     for (x = 0; x < 3; x++)
            //         soma += peso[y][x] * In[((i + y - 1) * nc + j + x - 1)];
            // //valor = soma / 9;
            // soma = soma < 0 ? 0 : soma;
            // soma = soma > mn ? mn : soma;
            // Out[i * nc + j] = mn - soma;
        }
}


