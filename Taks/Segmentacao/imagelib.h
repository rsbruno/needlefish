#define CREATOR "# CREATOR: Image Processing usind C-Ansi - ByDu\n"

typedef int *image;

#define ERROR(x, y) \
    if (x)          \
    y

#if defined(_WIN32) || defined(__WIN64__) || defined(__CYGWIN__)
#define VIEW "./i_view32"
#elif defined(__linux__)
#define VIEW "eog"
#endif

void errormsg(char *, ...);
image img_alloc(int, int);
int img_free(image);
void img_info(char *, int, int, int);
image img_readpgm(char *, int *, int *, int *);
void img_writepgm(image, char *, int, int, int);
image img_readppm(char *, int *, int *, int *);
void img_writeppm(image, char *, int, int, int);