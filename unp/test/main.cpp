#include "../net.h"

int main()
{
    int n;
    rio_t rio;
    char res[10000];
    rio_init(&rio, STDIN_FILENO, 5);
    rio.rio_ptr = (char *) malloc(sizeof(char) * 5);

    //n = rio_readline(&rio, res, 20);
    //printf("get %d", n);

    while((n = rio_readline(&rio, res, 20))!= 0)
    {
        sendn(STDOUT_FILENO, res, n);
        printf("\n");
    }
}
