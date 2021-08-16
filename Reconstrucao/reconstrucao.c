/*----------------------------------------------------
 * PROCESSAMENTO DE IMAGEM
 *  Imagens binárias - Morfologia Matemática
 *  Reconstrucao Geodesica
 *  Luiz Eduardo da Silva
 *----------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CREATOR "# Imagem criada por Luiz Eduardo da Silva\n"

typedef unsigned char *image;

image alloc_memo(int nl, int nc)
{
    return (image)malloc(nl * nc * sizeof(char));
}

int free_memo(image I)
{
    free(I);
}

void info_image(char *name, int nl, int nc)
{
    printf("\nInformacoes:");
    printf("\n--------------------------\n");
    printf("Nome do arquivo.............: %s \n", name);
    printf("Numero de linhas............: %d \n", nl);
    printf("Numero de colunas...........: %d \n\n", nc);
}

void error(char *s)
{
    puts(s);
    exit(10);
}

image read_pbm(char *name, int *nl, int *nc)
{
    int i, px;
    char line[100];
    image Img;
    FILE *arq;
    if (!(arq = fopen(name, "r")))
        error("Erro na ABERTURA do arquivo\n\n");
    fgets(line, 90, arq);
    if (!strstr(line, "P1"))
        error("Erro no FORMATO do arquivo\n\n");
    do
        fgets(line, 90, arq);
    while (line[0] == '#');
    sscanf(line, "%d %d", nc, nl);
    if (*nl == 0 || *nc == 0)
        error("Erro nas DIMENSOES do arquivo\n\n");
    if (!(Img = alloc_memo(*nl, *nc)))
        error("Erro na ALOCAÇÃO da imagem \n\n");
    for (i = 0; i < (*nl) * (*nc); i++)
    {
        fscanf(arq, "%d", &px);
        if (px < 0 && px > 1)
            error("Erro nos DADOS da imagem\n\n");
        Img[i] = px;
    }
    fclose(arq);
    return Img;
}

void write_pbm(image Img, char *name, int nl, int nc)
{
    int i, count, perLine = 50;
    FILE *arq;
    if ((arq = fopen(name, "wt")) == NULL)
        error("Erro na CRIACAO do arquivo\n\n");
    fputs("P1\n", arq);
    fputs(CREATOR, arq);
    fprintf(arq, "%d %d\n", nc, nl);
    count = 0;
    for (i = 0; i < nl * nc; i++)
    {
        fprintf(arq, "%d ", Img[i]);
        if (++count > perLine)
        {
            fprintf(arq, "\n");
            count = 0;
        }
    }
    fclose(arq);
}

// erosao por elemento estruturante 25 x 1
void erosao1(image In, image Out, int nl, int nc)
{
    int i, j, y, x, min;
    for (i = 0; i < nl; i++)
        for (j = 0; j < nc; j++)
        {
            min = 1000;
            for (y = -11; y <= 11; y++)
            {
                int pi = i + y;
                int pj = j;
                if (pi >= 0 && pi < nl && pj >= 0 && pj < nc)
                    if (In[pi * nc + pj] < min)
                        min = In[pi * nc + pj];
            }
            Out[i * nc + j] = min;
        }
}

// Reconstrucao geodesica
image reconstrucao(image In, int nl, int nc)
{
    int i, j, y, x, max, changed, count = 1;
    image Mark = alloc_memo(nl, nc);
    image Out = alloc_memo(nl, nc);
    image tmp;
    erosao1(In, Mark, nl, nc);
    for (i = 0; i < nl * nc; i++)
        Out[i] = 0;
    do
    {
        printf("count = %d\n", count++);
        changed = 0;
        for (i = 0; i < nl; i++)
            for (j = 0; j < nc; j++)
            {
                max = -1;
                for (y = -1; y <= 1; y++)
                    for (x = -1; x <= 1; x++)
                    {
                        int pi = i + y;
                        int pj = j + x;
                        if (pi >= 0 && pi < nl && pj >= 0 && pj < nc)
                            if (Mark[pi * nc + pj] > max)
                                max = Mark[pi * nc + pj];
                    }
                if (max && In[i * nc + j] && !Out[i * nc + j])
                {
                    changed = 1;
                    Out[i * nc + j] = 1;
                }
            }
        if (changed)
        {
            tmp = Mark;
            Mark = Out;
            Out = tmp;
        }
    } while (changed);
    free_memo(Mark);
    return Out;
}

void msg(char *s)
{
    printf("\nMorfologia Matemática binaria");
    printf("\n-----------------------------");
    printf("\nUSO.:  %s  <IMG.PBM>", s);
    printf("\nONDE:\n");
    printf("    <IMG.PBM>  Arquivo da imagem em formato PBM ASCII\n\n");
    exit(10);
}

/*--------------------------------------
 * P R O G R A M A    P R I N C I P A L 
 *--------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nl;
    char name[100];
    char comm[100];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    In = read_pbm(argv[1], &nl, &nc);
    printf("\nMorfologia Matemática");
    info_image(argv[1], nl, nc);

    Out = reconstrucao(In, nl, nc);

    sprintf(name, "%s-%s", argv[1], "reconstrucao.pbm");
    write_pbm(Out, name, nl, nc);
    sprintf(comm, "eog %.90s &", name);
    system(comm);
    free_memo(In);
    free_memo(Out);
    return 0;
}
