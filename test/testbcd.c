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
  int result = 0;

  printf("\nTest de \"%s\"\n", BCD_Identifier());

  /* test de la fonction BCD_ConvBCD2Ascii */
  {
    nombreBCD_s bcd2Ascii[] =
    {
      {"\x12\x34\x56", "123456", 6   },
      {"\x12\x34\x56", "23456", 5   },
      {"\x12\x34\x56", "1234", 4   }
    };

    /* test de conversion */
    for(size_t idx = 0; idx < (sizeof(bcd2Ascii) / sizeof(bcd2Ascii[0])); idx++)
    {
      char asciiOut[10];

      BCD_ConvBCD2Ascii(asciiOut, (unsigned char*)bcd2Ascii[idx].src, bcd2Ascii[idx].dstSize);
      if(memcmp(asciiOut, bcd2Ascii[idx].dst, bcd2Ascii[idx].dstSize) == 0)
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

    /* test de conversion */
    for(size_t idx = 0; idx < (sizeof(ascii2Bcd) / sizeof(ascii2Bcd[0])); idx++)
    {
      unsigned char bcdOut[10];

      BCD_ConvAscii2BCD(bcdOut, ascii2Bcd[idx].src, ascii2Bcd[idx].dstSize);
      if(memcmp(bcdOut, ascii2Bcd[idx].dst, (ascii2Bcd[idx].dstSize + 1) / 2) == 0)
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
