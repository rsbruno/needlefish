#include <stdio.h>
#include <stdlib.h>

#include "thresholding.h"

image thresholding(image In, int nl, int nc, int mn)
{
    int half = (int)mn / 2;
    for (int i = 0; i < nl * nc; i++)
        In[i] = (In[i] < half) ? 0 : 255;
    return In;
}