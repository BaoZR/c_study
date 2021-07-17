//往函数里传入多个参数，并把ints打印出来
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
void print_ints(int args, ...)
{
    va_list ap;
    va_start(ap, args);
    int i;
    for (i = 0; i < args; i++)
    {
        printf("argument: %i\n", va_arg(ap, int));
    }
    va_end(ap);
}
int main()
{
    print_ints(3, 22, 33, 44);
    //system("gedit");
    return 0;
}
