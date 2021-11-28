#include "bcd.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* pcSrc;
    const char* pcDest;
    size_t      szSize;
} nombreBCD_s;

int TstBcd(void)
{
    int             iResult = 0;
    size_t          szIdx;
    char            acASCIIOut[10];
    unsigned char   aucBCDOut[10];

    printf("\nTest de \"%s\"\n", BCD_Identifier());

    /* test de la fonction BCD_ConvBCD2Ascii */
    {
        nombreBCD_s asBCD2Ascii[] =
        {
            {"\x12\x34\x56", "123456", 6   },
            {"\x12\x34\x56", "23456", 5   },
            {"\x12\x34\x56", "1234", 4   }
        };

        /* test de la nullite */
        if(BCD_ConvBCD2Ascii(NULL, (unsigned char*)"\x12", sizeof acASCIIOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(BCD_ConvBCD2Ascii(acASCIIOut, NULL, sizeof acASCIIOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvBCD2Ascii) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(BCD_ConvBCD2Ascii(acASCIIOut, (unsigned char*)"\x12", 0) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvBCD2Ascii) Test taille nulle OK\n");
        }
        else
        {
            printf("(BCD_ConvBCD2Ascii) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asBCD2Ascii) / sizeof(asBCD2Ascii[0])); szIdx++)
        {
            if(BCD_ConvBCD2Ascii(acASCIIOut, (unsigned char*)asBCD2Ascii[szIdx].pcSrc, asBCD2Ascii[szIdx].szSize) == BCD_OK &&
               memcmp(acASCIIOut, asBCD2Ascii[szIdx].pcDest, asBCD2Ascii[szIdx].szSize) == 0)
            {
                printf("(BCD_ConvBCD2Ascii) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(BCD_ConvBCD2Ascii) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction BCD_ConvAscii2BCD */
    {
        nombreBCD_s asAscii2BCD[] =
        {
            {"123456", "\x12\x34\x56", 6   },
            {"12345", "\x01\x23\x45", 5   },
            {"123456", "\x12\x34", 4   }
        };

        /* test de la nullite */
        if(BCD_ConvAscii2BCD(NULL, "12", sizeof acASCIIOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(BCD_ConvAscii2BCD(aucBCDOut, NULL, sizeof aucBCDOut) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(BCD_ConvAscii2BCD) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(BCD_ConvAscii2BCD(aucBCDOut, "12", 0) == BCD_CONV_ERROR)
        {
            printf("(BCD_ConvAscii2BCD) Test taille nulle OK\n");
        }
        else
        {
            printf("(BCD_ConvAscii2BCD) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asAscii2BCD) / sizeof(asAscii2BCD[0])); szIdx++)
        {
            if(BCD_ConvAscii2BCD(aucBCDOut, asAscii2BCD[szIdx].pcSrc, asAscii2BCD[szIdx].szSize) == BCD_OK &&
               memcmp(aucBCDOut, asAscii2BCD[szIdx].pcDest, (asAscii2BCD[szIdx].szSize + 1) / 2) == 0)
            {
                printf("(BCD_ConvAscii2BCD) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(BCD_ConvAscii2BCD) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    return iResult;
}
