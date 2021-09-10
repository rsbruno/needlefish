#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"

void desfoque(image In, image Grd, int nl, int nc, int mn)
{
    int i, j, y, x, r, g, b;
    for (int i = 1; i < nl - 1; i++)
        for (int j = 1; j < nc - 1; j++)
        {
            r = 0, g = 0, b = 0;
            int kernel_blur = 5;
            for (y = 0; y < kernel_blur; y++)
                for (x = 0; x < kernel_blur; x++)
                {
                    if (Grd[((i + y - 1) * nc + j + x - 1)] == 255)
                    {
                        r += (In[((i + y - 1) * nc + j + x - 1)] >> 16) & 0xFF;
                        g += (In[((i + y - 1) * nc + j + x - 1)] >> 8) & 0xFF;
                        b += (In[((i + y - 1) * nc + j + x - 1)]) & 0xFF;
                    }
                    else
                    {
                        r += 0;
                        g += 0;
                        b += 0;
                    }
                }
            int Blur = pow(kernel_blur, 2);
            In[i * nc + j] = (r + g + b == 0)
                                 ? In[i * nc + j]
                                 : ((r / Blur) << 16) + ((g / Blur) << 8) + (b / Blur);
        }
}
