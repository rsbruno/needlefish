#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "imagelib.h"

/*-------------------------------------------------------------------------
 * Image allocation and free routines
 *   nr = number of rows
 *   nc = number of columns
 *-------------------------------------------------------------------------*/
image img_alloc(int nr, int nc)
{
    return (image)malloc(nr * nc * sizeof(int));
}

int img_free(image Im)
{
    free(Im);
}

/*-------------------------------------------------------------------------
 * Display image information
 *   name = file name image
 *   nr = number of rows
 *   nc = number os columns
 *   ml = max grayscale level
 *-------------------------------------------------------------------------*/
void img_info(char *name, int nr, int nc, int ml)
{
    printf("\nImage Informations:");
    printf("\n--------------------------\n");
    printf("Image file name.............: %s \n", name);
    printf("Number of rows..............: %d \n", nr);
    printf("Number of columns...........: %d \n", nc);
    printf("Max grayscale level.........: %d \n\n", ml);
}

/*-------------------------------------------------------------------------
 * Error message
 *   str - string message control
 *   ... - parameters
 *-------------------------------------------------------------------------*/
void errormsg(char *str, ...)
{
    char format[255];
    va_list arg;
    va_start(arg, str);
    sprintf(format, "ERROR: %s\n\n", str);
    vprintf(format, arg);
    va_end(arg);
    exit(1);
}

/*-------------------------------------------------------------------------
 * Read pgm image
 * Params:
 *   img = image
 *   name = image file name
 *   nr = number of rows
 *   nc = number of columns
 *   ml = max grayscale level
 * 
 * PGM format:
 * -----------
 * P2
 * # CREATOR: Image Processing usind C-Ansi
 * 124 122
 * 255
 * 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255
 * 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255
 *  (...)
 * Line 1: P2 identify PGM ASCII file
 * Line 2: Lines begins with # are comment
 * Line 3: Numbers of columns and rows
 * Line 4: Max grayscale value
 * Line 5 (...): Pixels values of image
 *-------------------------------------------------------------------------+*/
image img_readpgm(char *name, int *nr, int *nc, int *ml)
{
    int i, j, k;
    char c, lines[100];
    image img;
    FILE *fimg;
    ERROR((fimg = fopen(name, "r")) == NULL, errormsg("File open error: <%s>", name));
    /*--- PGM = "P2" ---*/
    fgets(lines, 80, fimg);
    ERROR(!strstr(lines, "P2"), errormsg("File image format error: <%s>", name));
    /*--- Comment lines ---*/
    fgets(lines, 80, fimg);
    while (strchr(lines, '#'))
        fgets(lines, 80, fimg);
    sscanf(lines, "%d %d", nc, nr);
    fscanf(fimg, "%d", ml);
    ERROR(*nc == 0 || *nr == 0 || *ml == 0, errormsg("Image dimensions error: <%s>", name));
    img = img_alloc(*nr, *nc);
    ERROR(!img, errormsg("Image allocation error: %s\n\n img_readpgm routine", name));
    for (i = 0; i < *nr; i++)
        for (j = 0; j < *nc; j++)
        {
            fscanf(fimg, "%d", &k);
            ERROR(k > *ml, errormsg("Max grayscale image error: <%s>", name));
            img[i * (*nc) + j] = k;
        }
    fclose(fimg);
    return img;
}

/*-------------------------------------------------------------------------
 * Write pgm image
 * Params:
 *   img = image
 *   name = image file name
 *   nr = number of rows
 *   nc = number of columns
 *   ml = max grayscale level
 *-------------------------------------------------------------------------*/
void img_writepgm(image img, char *name, int nr, int nc, int ml)
{
    int i, j, x, k, values_per_lines = 16;
    FILE *fimg;
    ERROR((fimg = fopen(name, "wt")) == NULL, errormsg("Image creation error: <%s>", name));
    fputs("P2\n", fimg);
    fputs(CREATOR, fimg);
    fprintf(fimg, "%d  %d\n", nc, nr);
    fprintf(fimg, "%d\n", ml);
    for (i = 0, k = 0; i < nr; i++)
        for (j = 0; j < nc; j++)
        {
            x = img[i * nc + j];
            fprintf(fimg, "%3d ", x);
            k++;
            if (k > values_per_lines)
            {
                fprintf(fimg, "\n");
                k = 0;
            }
        }
    fclose(fimg);
}

/*-------------------------------------------------------------------------
 * Read ppm image
 *-------------------------------------------------------------------------*/
image img_readppm(char *name, int *nr, int *nc, int *ml)
{
    int i, j, r, g, b;
    char c, lines[100];
    image Img;
    FILE *fimg;
    ERROR((fimg = fopen(name, "r")) == NULL, errormsg("File open error: <%s>", name));
    /*--- PPM = "P3" ---*/
    fgets(lines, 80, fimg);
    ERROR(!strstr(lines, "P3"), errormsg("File image format error: <%s>", name));
    /*--- Comment lines ---*/
    fgets(lines, 80, fimg);
    while (strchr(lines, '#'))
        fgets(lines, 80, fimg);
    sscanf(lines, "%d %d", nc, nr);
    fscanf(fimg, "%d", ml);
    ERROR(*nc == 0 || *nr == 0 || *ml == 0, errormsg("Image dimensions error: <%s>", name));

    Img = img_alloc(*nr, *nc);
    ERROR(!(Img), errormsg("Image allocation error: %s\n\n img_readppm routine", name));
    for (i = 0; i < *nr; i++)
    {
        for (j = 0; j < *nc; j++)
        {
            fscanf(fimg, "%d %d %d", &r, &g, &b);
            ERROR(r > *ml || r < 0 || g > *ml || g < 0 || b > *ml || b < 0,
                  errormsg("Max color image error: <%s>", name));
            Img[i * (*nc) + j] = (r << 16) + (g << 8) + b;
        }
    }
    fclose(fimg);
    return Img;
}

/*-------------------------------------------------------------------------
 * Write ppm image
 *-------------------------------------------------------------------------*/
void img_writeppm(image In, char *name, int nr, int nc, int ml)
{
    int i, j, x, r, g, b, k, values_per_lines = 8;
    FILE *fimg;
    ERROR((fimg = fopen(name, "wt")) == NULL, errormsg("Image creation error: <%s>", name));
    fputs("P3\n", fimg);
    fputs(CREATOR, fimg);
    fprintf(fimg, "%d  %d\n", nc, nr);
    fprintf(fimg, "%d\n", ml);
    for (i = 0, k = 0; i < nr; i++)
        for (j = 0; j < nc; j++)
            for (j = 0; j < nc; j++)
            {
                r = (In[i * nc + j] >> 16) & 0xFF;
                g = (In[i * nc + j] >> 8) & 0xFF;
                b = In[i * nc + j] & 0xFF;
                fprintf(fimg, "%3d %3d %3d ", r, g, b);
                k++;
                if (k > values_per_lines)
                {
                    fprintf(fimg, "\n");
                    k = 0;
                }
            }
    fclose(fimg);
}
