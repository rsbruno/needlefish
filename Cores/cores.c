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

double min(double a, double b, double c)
{
    if (a < b && a < c)
        return a;
    else if (b < c)
        return b;
    else
        return c;
}

void rgb2hsi(double R, double G, double B, double *H, double *S, double *I)
{
    double num, den, theta;
    num = .5 * ((R - G) + (R - B));
    den = pow((R - G) * (R - G) + (R - B) * (G - B), .5);
    theta = acos(num / (den + 0.00001)) / (2 * M_PI) * 360;
    *H = (B > G) ? 360 - theta : theta;
    *S = 1 - 3.0 / (R + G + B + 0.00001) * min(R, G, B);
    *I = 1 / 3.0 * (R + G + B);
}

void hsi2rgb(double H, double S, double I, double *R, double *G, double *B)
{
    if (H < 120)
    {
        *B = I * (1 - S);
        *R = I * (1 + S * cos(H / 360 * 2 * M_PI) / cos((60 - H) / 360 * 2 * M_PI));
        *G = 3 * I - (*R + *B);
    }
    else if (H < 240)
    {
        H = H - 120;
        *R = I * (1 - S);
        *G = I * (1 + S * cos(H / 360 * 2 * M_PI) / cos((60 - H) / 360 * 2 * M_PI));
        *B = 3 * I - (*R + *G);
    }
    else
    {
        H = H - 240;
        *G = I * (1 - S);
        *B = I * (1 + S * cos(H / 360 * 2 * M_PI) / cos((60 - H) / 360 * 2 * M_PI));
        *R = 3 * I - (*G + *B);
    }
    *R = (*R > 1) ? 1 : *R;
    *G = (*G > 1) ? 1 : *G;
    *B = (*B > 1) ? 1 : *B;
}

void clareia(image In, int nl, int nc, int mn)
{
    int j, r, g, b;
    double h, s, i, x, y, z;

    for (j = 0; j < nl * nc; j++)
    {
        // Transforma RGB -> HSI
        r = (In[j] >> 16) & 0xFF;
        g = (In[j] >> 8) & 0xFF;
        b = In[j] & 0xFF;
        x = ((double)r / mn);
        y = ((double)g / mn);
        z = ((double)b / mn);
        rgb2hsi(x, y, z, &h, &s, &i);

        // Altera intensidade
        i = (double)pow(i, 2);

        // Transforma HSI -> RGB
        hsi2rgb(h, s, i, &x, &y, &z);
        r = x * mn;
        g = y * mn;
        b = z * mn;
        In[j] = (r << 16) + (g << 8) + b;
    }
}

void transforma(image In, int nl, int nc, int mn)
{
    int i, r, g, b;
    double expo = 2; // 2 = escurece, 0.5 = clareia
    for (i = 0; i < nl * nc; i++)
    {
        r = (In[i] >> 16) & 0xFF;
        g = (In[i] >> 8) & 0xFF;
        b = (In[i]) & 0xFF;

        // r = (double)pow(r, expo) / pow(255, expo) * mn;
        // g = (double)pow(g, expo) / pow(255, expo) * mn;
        // b = (double)pow(b, expo) / pow(255, expo) * mn;

        /*--- Negativo da imagem colorida --*/
        r = mn - r;
        g = mn - g;
        b = mn - b;

        In[i] = (r << 16) + (g << 8) + b;
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
    image In;
    if (argc < 2)
        msg(argv[0]);
    In = img_readppm(argv[1], &nl, &nc, &mn);
    printf("\nImage Color Processing");
    img_info(argv[1], nl, nc, mn);

    // transforma(In, nl, nc, mn);
    clareia(In, nl, nc, mn);

    sprintf(name, "%s-%s", argv[1], "transforma.ppm");
    img_writeppm(In, name, nl, nc, mn);
    sprintf(command, "%s %s &", VIEW, name);
    system(command);
    img_free(In);
    return 0;
}
