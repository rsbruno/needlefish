#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagelib.h"

/*------------------------------------------------
 * Fila de prioridade
 *------------------------------------------------*/
typedef struct no *ptno;
typedef struct no
{
    int i, j;
    ptno next;
} no;

/*-----------------------------------------------
 *  init   *Q      new     init         *Q
 *  [a:]->[b:]-+   [c:]  ->[a:]->[b:]->[c:]-+
 *   ^---------+             ^--------------+
 *----------------------------------------------*/
void insQ(ptno *Q, int i, int j)
{
    ptno new = malloc(sizeof(no));
    new->i = i;
    new->j = j;
    if (!(*Q))
        new->next = new;
    else
    {
        new->next = (*Q)->next;
        (*Q)->next = new;
    }
    *Q = new;
}

/*-----------------------------------------------
 *  init         *Q                    *Q
 *  [a:]->[b:]->[c:]-+    [a:]  [b:]->[c:]-+
 *    ^--------------+            ^--------+
 *----------------------------------------------*/
void remQ(ptno *Q, int *i, int *j)
{
    ptno init = (*Q)->next;
    *i = init->i;
    *j = init->j;
    if (*Q == init)
        *Q = NULL;
    else
        (*Q)->next = init->next;
    free(init);
}

int isEmpty(ptno *Q)
{
    return *Q == NULL;
}

void initQPrior(ptno *QPrior, int mn)
{
    int i;
    for (i = 0; i < mn; i++)
        QPrior[i] = NULL;
}

void insert(ptno *QPrior, int i, int j, int p)
{
    insQ(QPrior + p, i, j);
}

int pop(ptno *QPrior, int *i, int *j, int *maxPrior, int mn)
{
    while (*maxPrior < mn && isEmpty(QPrior + *maxPrior))
        (*maxPrior)++;
    if (*maxPrior == mn)
        return 1;
    remQ(QPrior + *maxPrior, i, j);
    return 0;
}

/*------------------------------------------------
 * Calcula o gradient da imagem PGM
 *------------------------------------------------*/
void gradient(image In, image Out, int nl, int nc, int mn, int raio)
{
    int i, j, y, x, max, min;
    for (i = 0; i < nl; i++)
        for (j = 0; j < nc; j++)
        {
            max = -1;
            min = mn + 1;
            for (y = -raio; y <= raio; y++)     // -1 0 1
                for (x = -raio; x <= raio; x++) // -1 0 1
                {
                    int pi = i + y;
                    int pj = j + x;
                    if (pi >= 0 && pi < nl && pj >= 0 && pj < nc)
                    {
                        if (abs(x) + abs(y) <= raio && In[pi * nc + pj] > max)
                            max = In[pi * nc + pj];
                        if (abs(x) + abs(y) <= raio && In[pi * nc + pj] < min)
                            min = In[pi * nc + pj];
                    }
                }
            Out[i * nc + j] = max - min;
        }
}

/*------------------------------------------------
 * Calcula o Watershed da imagem
 *------------------------------------------------*/
void watershed(image In, image Out, int nl, int nc, int mn, int y, int x)
{
    int i, j, k, maxPrior = 0, stop = 0;
    ptno qPrior[mn];
    image mark = img_alloc(nl, nc);
    enum
    {
        NONE,
        QUEUE,
        WSHED,
        MARK1,
        MARK2,
    };
    struct
    {
        int i, j;
    } n4[4] =
        {0, 1,   //vizinho da direita
         1, 0,   //vizinho de baixo
         0, -1,  //vizinho da esquerda
         -1, 0}; //vizinho de cima

    initQPrior(qPrior, mn);

    // Inicialização dos marcadores
    //-----------------------------
    for (i = 0; i < nl * nc; i++)
        mark[i] = NONE;

    // MARK1 = (y, x) - centro da região
    int raio = 10;
    for (i = -raio; i <= raio; i++)
        for (j = -raio; j <= raio; j++)
        {
            int pi = i + y;
            int pj = j + x;
            if (abs(i) + abs(j) <= raio)
                mark[pi * nc + pj] = MARK1;
        }

    //mark[y * nc + x] = MARK1;

    // MARK2 = borda da imagem
    for (i = 0; i < nl; i++)
    {
        mark[i * nc] = MARK2;
        mark[i * nc + nc - 1] = MARK2;
    }
    for (j = 0; j < nc; j++)
    {
        mark[j] = MARK2;
        mark[(nl - 1) * nc + j] = MARK2;
    }
    // Inicialização
    //--------------
    // Todos os vizinhos dos marcadores são colocados na fila
    // A prioridade é o nível de cinza do pixel
    for (i = 1; i < nl - 1; i++)
        for (j = 1; j < nc - 1; j++)
            if (mark[i * nc + j] == NONE)
            {
                int isAdj = 0;
                for (k = 0; k < 4; k++)
                {
                    int pi = i + n4[k].i;
                    int pj = j + n4[k].j;
                    int m = mark[pi * nc + pj];
                    if (m == MARK1 || m == MARK2)
                        isAdj = 1;
                }
                if (isAdj)
                {
                    mark[i * nc + j] = QUEUE;
                    insert(qPrior, i, j, In[i * nc + j]);
                }
            }
    // Crescimento dos Marcadores
    //---------------------------
    // Enquanto a fila de prioridade não está vazia faça
    // 1. retira um pixel da fila
    // 2. Se o pixel eh vizinho de UMA marca, recebe essa marca.
    //    Seus vizinhos sem rotulo são colocados na fila
    // 3. Se o pixel eh vizinho de DUAS marcas, ele eh WATERSHED
    while (!stop)
    {
        int m = NONE;
        int isWshed = 0;
        stop = pop(qPrior, &i, &j, &maxPrior, mn);
        if (!stop)
        {
            for (k = 0; k < 4; k++)
            {
                int pi = i + n4[k].i;
                int pj = j + n4[k].j;
                if (pi >= 0 && pi < nl && pj >= 0 && pj < nc)
                {
                    int mAdj = mark[pi * nc + pj];
                    if (mAdj == MARK1 || mAdj == MARK2)
                    {
                        if (m == NONE)
                            m = mAdj;
                        else if (m != mAdj)
                            isWshed = 1;
                    }
                }
            }
            if (isWshed)
                mark[i * nc + j] = WSHED;
            else
            {
                mark[i * nc + j] = m;
                for (k = 0; k < 4; k++)
                {
                    int pi = i + n4[k].i;
                    int pj = j + n4[k].j;
                    if (pi >= 0 && pi < nl && pj >= 0 && pj < nc)
                        if (mark[pi * nc + pj] == NONE)
                        {
                            int prior, px;
                            mark[pi * nc + pj] = QUEUE;
                            px = In[pi * nc + pj];
                            prior = (px < maxPrior) ? maxPrior : px;
                            insert(qPrior, pi, pj, prior);
                        }
                }
            }
        }
    }
    for (i = 0; i < nl * nc; i++)
        Out[i] = (mark[i] == WSHED) ? 255 : 0;
    img_free(mark);
}

void msg(char *s)
{
    printf("\nWatershed");
    printf("\n---------");
    printf("\nUSO.:  %s  <IMG.PGM>", s);
    printf("\nONDE:\n");
    printf("    <IMG.PGM>  Arquivo da imagem em formato PGM ASCII\n\n");
    exit(10);
}

/*------------------------------------------------------
 *          P R O G R A M A    P R I N C I P A L
 *------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int OK, nc, nl, mn;
    char nome[100];
    char comando[100];
    image In, Out, Grd;
    if (argc < 2)
        msg(argv[0]);

    In = img_readpgm(argv[1], &nl, &nc, &mn);
    printf("\nWatershed");
    img_info(argv[1], nl, nc, mn);
    Out = img_alloc(nl, nc);
    Grd = img_alloc(nl, nc);

    gradient(In, Grd, nl, nc, mn, 1);
    watershed(Grd, Out, nl, nc, mn, nl / 2, nc / 2);

    sprintf(nome, "%s-%s", argv[1], "watershed.pgm");
    img_writepgm(Out, nome, nl, nc, mn);
    sprintf(comando, "eog %.90s &", nome);
    system(comando);
    img_free(In);
    img_free(Grd);
    img_free(Out);
    return 0;
}
