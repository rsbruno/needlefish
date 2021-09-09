/*---------------------------------------------------------
 * PROCESSAMENTO DE IMAGEM -
 * -----------------------  
 * Processamento de imagens coloridas
 * Por Luiz Eduardo da Silva.
 *---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#include "watershed.h"
#include "desfoque.h"

void black_and_white(image In, image Out, int nl, int nc, int mn)
{
    int i, r, g, b;
    for (i = 0; i < nl * nc; i++)
    {
        r = (In[i] >> 16) & 0xFF;
        g = (In[i] >> 8) & 0xFF;
        b = (In[i]) & 0xFF;

        Out[i] = (r + g + b) / 3;
    }
}

void msg(char *s)
{
    printf("\nImage Color Processing");
    printf("\n-------------------------------");
    printf("\nUSO.:  %s  <IMG.PPM>", s);
    printf("\nONDE:\n");
    printf("    <IMG.PPM>  Arquivo da imagem em formato PPM ASCII\n\n");
    exit(20);
}

/*+------------------------------------------------------+
  |        P R O G R A M A    P R I N C I P A L          |
  +------------------------------------------------------+*/
int main(int argc, char *argv[])
{
    int OK, nc, nl, mn;
    char name[100];
    char command[110];
    image In, Out, Grd, Img_BW, Mask;
    if (argc < 2)
        msg(argv[0]);
    In = img_readppm(argv[1], &nl, &nc, &mn);
    Out = img_alloc(nc, nl);

    // printf("\nImage Color Processing");
    // img_info(argv[1], nl, nc, mn);

    black_and_white(In, Out, nl, nc, mn);

    sprintf(name, "_imageBW.pgm");
    img_writepgm(Out, name, nl, nc, mn);

    Grd = img_alloc(nl, nc);

    int bw_nl, bw_nc, bw_mn;

    Img_BW = img_readpgm("_imageBW.pgm", &bw_nl, &bw_nc, &bw_mn);

    gradient(Img_BW, Grd, nl, nc, mn, 1);
    watershed(Grd, Out, nl, nc, mn, 247, 196);

    sprintf(name, "_mask1.pgm");
    img_writepgm(Out, name, nl, nc, mn);

    img_free(Img_BW);
    img_free(Grd);

    int Msk_nl, Msk_nc, Msk_mn;
    Mask = img_readpgm(name, &Msk_nl, &Msk_nc, &Msk_mn);

    desfoque(In, Mask, Out, nl, nc, mn);

    sprintf(name, "_notebook.ppm");
    img_writeppm(Out, name, nl, nc, mn);

    // sprintf(command, "%s %s &", VIEW, name);
    // system(command);
    //img_free(In);
    return 0;
}
