#include "bcd.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* src;
    const char* dst;
    size_t      dstSize;
} nombreBCD_s;

int TstBcd(void)
{
    int             result = 0;
    size_t          idx;
    char            asciiOut[10];
    unsigned char   bcdOut[10];

    printf("\nTest de \"%s\"\n", BCD_Identifier());

    /* test de la fonction BCD_ConvBCD2Ascii */
    {
        nombreBCD_s bcd2Ascii[] =
        {
            {"\x12\x34\x56", "123456", 6   },
            {"\x12\x34\x56", "23456", 5   },
            {"\x12\x34\x56", "1234", 4   }
        };

        /* test de la nullite */
        if(BCD_ConvBCD2Ascii(NULL, (unsigned char*)"\x12", sizeof asciiOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur de sortie NULL KO\n");
            result = 1;
        }

        if(BCD_ConvBCD2Ascii(asciiOut, NULL, sizeof asciiOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(BCD_ConvBCD2Ascii(asciiOut, (unsigned char*)"\x12", 0) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvBCD2Ascii) Test taille nulle OK\n");
        }
        else
        {
            printf("(BCD_ConvBCD2Ascii) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(bcd2Ascii) / sizeof(bcd2Ascii[0])); idx++)
        {
            if(BCD_ConvBCD2Ascii(asciiOut, (unsigned char*)bcd2Ascii[idx].src, bcd2Ascii[idx].dstSize) == BCD_OK &&
               memcmp(asciiOut, bcd2Ascii[idx].dst, bcd2Ascii[idx].dstSize) == 0)
            {
                printf("(BCD_ConvBCD2Ascii) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(BCD_ConvBCD2Ascii) test %d KO\n", (int)(idx + 1));
                result = 1;
            }
        }
    }

    /* test de la fonction BCD_ConvAscii2BCD */
    {
        nombreBCD_s ascii2Bcd[] =
        {
            {"123456", "\x12\x34\x56", 6   },
            {"12345", "\x01\x23\x45", 5   },
            {"123456", "\x12\x34", 4   }
        };

        /* test de la nullite */
        if(BCD_ConvAscii2BCD(NULL, "12", sizeof asciiOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur de sortie NULL KO\n");
            result = 1;
        }

        if(BCD_ConvAscii2BCD(bcdOut, NULL, sizeof bcdOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(BCD_ConvAscii2BCD(bcdOut, "12", 0) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvAscii2BCD) Test taille nulle OK\n");
        }
        else
        {
            printf("(BCD_ConvAscii2BCD) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(ascii2Bcd) / sizeof(ascii2Bcd[0])); idx++)
        {
            if(BCD_ConvAscii2BCD(bcdOut, ascii2Bcd[idx].src, ascii2Bcd[idx].dstSize) == BCD_OK &&
               memcmp(bcdOut, ascii2Bcd[idx].dst, (ascii2Bcd[idx].dstSize + 1) / 2) == 0)
            {
                printf("(BCD_ConvAscii2BCD) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(BCD_ConvAscii2BCD) test %d KO\n", (int)(idx + 1));
                result = 1;
            }
        }
    }

    return result;
}
