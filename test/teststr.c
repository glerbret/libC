#include "str.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    const char* src;
    const char* dst;
    char        character;
} twostring_s;

int TstStr(void)
{
    int result = 0;
    size_t idx;
    char output[10];

    printf("\nTest de \"%s\"\n", STR_Identifier());

    /* test de la fonction STR_DelChar */
    {
        twostring_s delCharString[] =
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
            result = 1;
        }

        if(STR_DelChar(output, NULL, sizeof output, ':') == NULL)
        {
            printf("(STR_DelChar) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_DelChar) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_DelChar(output, "abc", 0, ':') == NULL)
        {
            printf("(STR_DelChar) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_DelChar) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(delCharString) / sizeof(delCharString[0])); idx++)
        {
            STR_DelChar(output, delCharString[idx].src, sizeof output, delCharString[idx].character);
            if(strcmp(output, delCharString[idx].dst) == 0)
            {
                printf("(STR_DelChar) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_DelChar) test %d KO\n", (int)(idx + 1));
                result = 1;
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
            result = 1;
        }

        if(STR_Strip(output, NULL, sizeof output) == NULL)
        {
            printf("(STR_Strip) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_Strip) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_Strip(output, "abc", 0) == NULL)
        {
            printf("(STR_Strip) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_Strip) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(asStripString) / sizeof(asStripString[0])); idx++)
        {
            STR_Strip(output, asStripString[idx].src, sizeof output);
            if(strcmp(output, asStripString[idx].dst) == 0)
            {
                printf("(STR_Strip) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_Strip) test %d KO\n", (int)(idx + 1));
                result = 1;
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
            result = 1;
        }

        if(STR_String2Lower(output, NULL, sizeof output) == NULL)
        {
            printf("(STR_String2Lower) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_String2Lower) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_String2Lower(output, NULL, 0) == NULL)
        {
            printf("(STR_String2Lower) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_String2Lower) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(as2LowerString) / sizeof(as2LowerString[0])); idx++)
        {
            STR_String2Lower(output, as2LowerString[idx].src, sizeof output);
            if(strcmp(output, as2LowerString[idx].dst) == 0)
            {
                printf("(STR_String2Lower) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_String2Lower) test %d KO\n", (int)(idx + 1));
                result = 1;
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
            result = 1;
        }

        if(STR_String2Upper(output, NULL, sizeof output) == NULL)
        {
            printf("(STR_String2Upper) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_String2Upper) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_String2Upper(output, "Ade", 0) == NULL)
        {
            printf("(STR_String2Upper) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_String2Upper) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(as2UpperString) / sizeof(as2UpperString[0])); idx++)
        {
            STR_String2Upper(output, as2UpperString[idx].src, sizeof output);
            if(strcmp(output, as2UpperString[idx].dst) == 0)
            {
                printf("(STR_String2Upper) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_String2Upper) test %d KO\n", (int)(idx + 1));
                result = 1;
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
            result = 1;
        }

        if(STR_LeftPadding(output, NULL, sizeof output, ' ') == NULL)
        {
            printf("(STR_LeftPadding) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_LeftPadding) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_LeftPadding(output, "abc", 0, ' ') == NULL)
        {
            printf("(STR_LeftPadding) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_LeftPadding) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(asLeftPaddingString) / sizeof(asLeftPaddingString[0])); idx++)
        {
            STR_LeftPadding(output, asLeftPaddingString[idx].src, sizeof output, asLeftPaddingString[idx].character);
            if(strcmp(output, asLeftPaddingString[idx].dst) == 0)
            {
                printf("(STR_LeftPadding) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_LeftPadding) test %d KO\n", (int)(idx + 1));
                result = 1;
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
            result = 1;
        }

        if(STR_RightPadding(output, NULL, sizeof output, ' ') == NULL)
        {
            printf("(STR_RightPadding) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_RightPadding) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_RightPadding(output, "abc", 0, ' ') == NULL)
        {
            printf("(STR_RightPadding) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_RightPadding) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(asRightPaddingString) / sizeof(asRightPaddingString[0])); idx++)
        {
            STR_RightPadding(output, asRightPaddingString[idx].src, sizeof output, asRightPaddingString[idx].character);
            if(strcmp(output, asRightPaddingString[idx].dst) == 0)
            {
                printf("(STR_RightPadding) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_RightPadding) test %d KO\n", (int)(idx + 1));
                result = 1;
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
            result = 1;
        }

        if(STR_Center(output, NULL, sizeof output, ' ') == NULL)
        {
            printf("(STR_Center) Test pointeur d'entree NULL OK\n");
        }
        else
        {
            printf("(STR_Center) Test pointeur d'entree NULL KO\n");
            result = 1;
        }

        if(STR_Center(output, "abc", 0, ' ') == NULL)
        {
            printf("(STR_Center) Test taille nulle OK\n");
        }
        else
        {
            printf("(STR_Center) Test taille nulle KO\n");
            result = 1;
        }

        /* test de conversion */
        for(idx = 0; idx < (sizeof(asCenterString) / sizeof(asCenterString[0])); idx++)
        {
            STR_Center(output, asCenterString[idx].src, sizeof output, asCenterString[idx].character);
            if(strcmp(output, asCenterString[idx].dst) == 0)
            {
                printf("(STR_Center) test %d OK\n", (int)(idx + 1));
            }
            else
            {
                printf("(STR_Center) test %d KO\n", (int)(idx + 1));
                result = 1;
            }
        }
    }

    return result;
}
