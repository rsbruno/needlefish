#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagelib.h"

void convert_hexadecimal(image In, int nc, int nl)
{
    char hexa[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char *hexadecimal;

    for (int i = 0; i < nc * nl; i+=3)
    {
        hexadecimal = "";
        //itoa(hexa[2 / 16],hexadecimal,10);
        sprintf(hexadecimal,"%d",5);
        

        printf("%s", hexadecimal);
    }

    // unsigned int px = 0x00DA865D;
    // //#DA865d
    // //rgb(218,25,1)
    // int R, G, B;
    // R = (px >> 16) & 0x0FF;
    // G = (px >> 6) & 0x0FF;
    // B = (px) && 0x0FF;

    // int n = 196;
    // printf("%c%c", hexa[n / 16], hexa[n % 16]);
}

int main(int argc, char *argv[])
{

    int OK, nc, nl, mn;
    char name[100];
    char command[110];
    image In;
    // if (argc < 2)
    //     msg(argv[0]);
    In = img_readppm(argv[1], &nl, &nc, &mn);
    //printf("\nImage Color Processing");
    //img_info(argv[1], nl, nc, mn);

    convert_hexadecimal(In, nc, nl);

    // sprintf(name, "%s-%s", argv[1], "transforma.ppm");
    // img_writeppm(In, name, nl, nc, mn);
    // sprintf(command, "%s %s &", VIEW, name);
    // system(command);
    img_free(In);

    return 0;
}