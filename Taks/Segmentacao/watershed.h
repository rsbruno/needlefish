#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "imagelib.h"

void gradient(image In, image Out, int nl, int nc, int mn, int raio);
void watershed(image In, image Out, int nl, int nc, int mn, int y, int x);