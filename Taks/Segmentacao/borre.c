/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
    ∗ UNIFAL − Universidade Federal de Alfenas.
    ∗ BACHARELADO EM CIENCIA DA COMPUTACAO.
    ∗ Trabalho  . . .  : Watershed - Borramento de Fundo
    ∗ Disciplina. . .  : Processamento de Imagens
    ∗ Professor . . .  : Luiz Eduardo da Silva
    ∗ Aluno . . . . .  : Burno Roberto Santos
    ∗ Data  . . . . .  : 09/09/2021
∗−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#include "watershed.h"
#include "black_white.h"
#include "desfoque.h"

void msg(char *s)
{
    printf("\nBorramento de fundo");
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
    int nc, nl, mn;
    char name[100];
    char command[110];
    image In, Out, Grd;
    if (argc < 2)
        msg(argv[0]);
    In = img_readppm(argv[1], &nl, &nc, &mn);
    Out = img_alloc(nc, nl);

    printf("\nBorramento de fundo");
    img_info(argv[1], nl, nc, mn);

    //Devolve uma imagem preto e branco da imagem de entrada
    black_and_white(In, Out, nl, nc, mn);

    sprintf(name, "_imageBW.pgm");
    img_writepgm(Out, name, nl, nc, mn);

    Grd = img_alloc(nl, nc);

    //Nesse momento "Out" é uma imagem preto e branco da entrada
    //Devolve o gradiente de formas da imagem de entrada
    gradient(Out, Grd, nl, nc, mn, 1);

    //"Grd" tem os contornos presentes na imagem de entrada
    //Devolve uma imagem com o objeto principal separado
    watershed(Grd, Out, nl, nc, mn, 247, 196);

    sprintf(name, "_mask1.pgm");
    img_writepgm(Out, name, nl, nc, mn);

    img_free(Grd);//Não precisamos mais do gradiente

    //Nesse momento "Out" é a máscara de separação do objeto a ser mantido
    //Devolve na variável de entrada "In" a imagem com fundo borrado
    desfoque(In, Out, nl, nc, mn);

    sprintf(name, "saida.ppm");
    img_writeppm(In, name, nl, nc, mn);

    sprintf(command, "%s %s &", VIEW, name);
    system(command);
    img_free(Out);
    img_free(In);
    return 0;
}
