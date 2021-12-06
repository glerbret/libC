#include "test.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
    int result = 0;

    if(TstLuhn() != 0)
    {
        result = 1;
    }
    if(TstStr() != 0)
    {
        result = 1;
    }
    if(TstIni() != 0)
    {
        result = 1;
    }
    if(TstDate() != 0)
    {
        result = 1;
    }
    if(TstOpt() != 0)
    {
        result = 1;
    }
    if(TstBcd() != 0)
    {
        result = 1;
    }
    if(TstStack() != 0)
    {
        result = 1;
    }
    if(TstQueue() != 0)
    {
        result = 1;
    }
    if(TstList() != 0)
    {
        result = 1;
    }
    if(TstCList() != 0)
    {
        result = 1;
    }
    if(TstModulus97() != 0)
    {
        result = 1;
    }
    if(TstBits() != 0)
    {
        result = 1;
    }

    if(result == 0)
    {
        printf("\n\nTests OK\n");
    }
    else
    {
        printf("\n\nTests echoues\n");
    }

    return 0;
}
