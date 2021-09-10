#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"

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