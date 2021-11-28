#include "str.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* pcSrc;
    const char* pcDest;
    char        cChar;
} twostring_s;

int TstStr(void)
{
    int iResult = 0;
    size_t szIdx;
    char acOut[10];

    printf("\nTest de \"%s\"\n", STR_Identifier());

    /* test de la fonction STR_DelChar */
    {
        twostring_s asDelCharString[] =
        {
            {"", "", ':' },
            {"  :  ", "    ", ':' },
            {"abc", "abc", ':' },
            {":abc", "abc", ':' },
            {"abc:", "abc", ':' },
            {":abc:", "abc", ':' },
            {"a:bc", "abc", ':' },
            {":a:bc", "abc", ':' },
            {"a:bc:", "abc", ':'  },
            {":a:bc:", "abc", ':' },
            {"abcdefghijk", "abcdefghi", ':' },
            {"abcdefghij:", "abcdefghi", ':' },
            {":abcdefghij", "abcdefghi", ':' },
            {"abcd:efghij", "abcdefghi", ':' }
        };

        /* test de la nullite */
        if(STR_DelChar(NULL, "abc", 0, ':') == NULL)
        {
            printf("(STR_DelChar) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_DelChar) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_DelChar(acOut, NULL, sizeof acOut, ':') == NULL)
        {
            printf("(STR_DelChar) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_DelChar) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_DelChar(acOut, "abc", 0, ':') == NULL)
        {
            printf("(STR_DelChar) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_DelChar) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asDelCharString) / sizeof(asDelCharString[0])); szIdx++)
        {
            STR_DelChar(acOut, asDelCharString[szIdx].pcSrc, sizeof acOut, asDelCharString[szIdx].cChar);
            if(strcmp(acOut, asDelCharString[szIdx].pcDest) == 0)
            {
                printf("(STR_DelChar) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_DelChar) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction STR_Strip */
    {
        twostring_s asStripString[] =
        {
            {"", "", 0   },
            {"    ", "", 0   },
            {"abc", "abc", 0   },
            {"  abc", "abc", 0   },
            {"abc   ", "abc", 0   },
            {"  abc  ", "abc", 0   },
            {"a bc", "a bc", 0   },
            {" a bc", "a bc", 0   },
            {"a bc ", "a bc", 0   },
            {" a bc ", "a bc", 0   },
            {"abcdefghijk", "abcdefghi", 0   },
            {"abcdefghij ", "abcdefghi", 0   },
            {"abcdefghij", "abcdefghi", 0   },
            {"abcdefghi ", "abcdefghi", 0   }
        };

        /* test de la nullite */
        if(STR_Strip(NULL, "abc", 0) == NULL)
        {
            printf("(STR_Strip) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_Strip) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_Strip(acOut, NULL, sizeof acOut) == NULL)
        {
            printf("(STR_Strip) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_Strip) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_Strip(acOut, "abc", 0) == NULL)
        {
            printf("(STR_Strip) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_Strip) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asStripString) / sizeof(asStripString[0])); szIdx++)
        {
            STR_Strip(acOut, asStripString[szIdx].pcSrc, sizeof acOut);
            if(strcmp(acOut, asStripString[szIdx].pcDest) == 0)
            {
                printf("(STR_Strip) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_Strip) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction STR_String2Lower */
    {
        twostring_s as2LowerString[] =
        {
            {" Ab c",   " ab c", 0   },
            {"abcdefghijk", "abcdefghi", 0   }
        };

        /* test de la nullite */
        if(STR_String2Lower(NULL, "abc", 0) == NULL)
        {
            printf("(STR_String2Lower) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_String2Lower) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_String2Lower(acOut, NULL, sizeof acOut) == NULL)
        {
            printf("(STR_String2Lower) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_String2Lower) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_String2Lower(acOut, NULL, 0) == NULL)
        {
            printf("(STR_String2Lower) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_String2Lower) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(as2LowerString) / sizeof(as2LowerString[0])); szIdx++)
        {
            STR_String2Lower(acOut, as2LowerString[szIdx].pcSrc, sizeof acOut);
            if(strcmp(acOut, as2LowerString[szIdx].pcDest) == 0)
            {
                printf("(STR_String2Lower) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_String2Lower) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction STR_String2Upper */
    {
        twostring_s as2UpperString[] =
        {
            {" Ab c", " AB C", 0   },
            {"ABcdeFghij", "ABCDEFGHI", 0   }
        };

        /* test de la nullite */
        if(STR_String2Upper(NULL, "abc", 0) == NULL)
        {
            printf("(STR_String2Upper) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_String2Upper) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_String2Upper(acOut, NULL, sizeof acOut) == NULL)
        {
            printf("(STR_String2Upper) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_String2Upper) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_String2Upper(acOut, "Ade", 0) == NULL)
        {
            printf("(STR_String2Upper) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_String2Upper) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(as2UpperString) / sizeof(as2UpperString[0])); szIdx++)
        {
            STR_String2Upper(acOut, as2UpperString[szIdx].pcSrc, sizeof acOut);
            if(strcmp(acOut, as2UpperString[szIdx].pcDest) == 0)
            {
                printf("(STR_String2Upper) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_String2Upper) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction STR_LeftPadding */
    {
        twostring_s asLeftPaddingString[] =
        {
            {"", "         ", ' ' },
            {"abc", "      abc", ' ' },
            {"abcdefghijk", "abcdefghi", ' ' },
        };

        /* test de la nullite */
        if(STR_LeftPadding(NULL, "abc", 0, ' ') == NULL)
        {
            printf("(STR_LeftPadding) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_LeftPadding) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_LeftPadding(acOut, NULL, sizeof acOut, ' ') == NULL)
        {
            printf("(STR_LeftPadding) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_LeftPadding) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_LeftPadding(acOut, "abc", 0, ' ') == NULL)
        {
            printf("(STR_LeftPadding) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_LeftPadding) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asLeftPaddingString) / sizeof(asLeftPaddingString[0])); szIdx++)
        {
            STR_LeftPadding(acOut, asLeftPaddingString[szIdx].pcSrc, sizeof acOut, asLeftPaddingString[szIdx].cChar);
            if(strcmp(acOut, asLeftPaddingString[szIdx].pcDest) == 0)
            {
                printf("(STR_LeftPadding) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_LeftPadding) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction STR_RightPadding */
    {
        twostring_s asRightPaddingString[] =
        {
            {"", "         ", ' ' },
            {"abc", "abc      ", ' ' },
            {"abcdefghijk", "abcdefghi", ' ' },
        };

        /* test de la nullite */
        if(STR_RightPadding(NULL, "abc", 0, ' ') == NULL)
        {
            printf("(STR_RightPadding) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_RightPadding) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_RightPadding(acOut, NULL, sizeof acOut, ' ') == NULL)
        {
            printf("(STR_RightPadding) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_RightPadding) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_RightPadding(acOut, "abc", 0, ' ') == NULL)
        {
            printf("(STR_RightPadding) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_RightPadding) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asRightPaddingString) / sizeof(asRightPaddingString[0])); szIdx++)
        {
            STR_RightPadding(acOut, asRightPaddingString[szIdx].pcSrc, sizeof acOut, asRightPaddingString[szIdx].cChar);
            if(strcmp(acOut, asRightPaddingString[szIdx].pcDest) == 0)
            {
                printf("(STR_RightPadding) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_RightPadding) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    /* test de la fonction STR_Center */
    {
        twostring_s asCenterString[] =
        {
            {"", "         ", ' ' },
            {"abc", "   abc   ", ' ' },
            {"abcd", "  abcd   ", ' ' },
            {"abcdefghijk", "abcdefghi", ' ' },
        };

        /* test de la nullite */
        if(STR_Center(NULL, "abc", 0, ' ') == NULL)
        {
            printf("(STR_Center) Test pointeur de sortie NULL OK\n");
        }
        else
        {
            printf("(STR_Center) Test pointeur de sortie NULL KO\n");
            iResult = 1;
        }

        if(STR_Center(acOut, NULL, sizeof acOut, ' ') == NULL)
        {
            printf("(STR_Center) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_Center) Test pointeur d'entree NULL KO\n");
            iResult = 1;
        }

        if(STR_Center(acOut, "abc", 0, ' ') == NULL)
        {
            printf("(STR_Center) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_Center) Test taille nulle KO\n");
            iResult = 1;
        }

        /* test de conversion */
        for(szIdx = 0; szIdx < (sizeof(asCenterString) / sizeof(asCenterString[0])); szIdx++)
        {
            STR_Center(acOut, asCenterString[szIdx].pcSrc, sizeof acOut, asCenterString[szIdx].cChar);
            if(strcmp(acOut, asCenterString[szIdx].pcDest) == 0)
            {
                printf("(STR_Center) test %d OK\n", (int)(szIdx + 1));
            }
            else
            {
                printf("(STR_Center) test %d KO\n", (int)(szIdx + 1));
                iResult = 1;
            }
        }
    }

    return iResult;
}
