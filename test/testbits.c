#include "bits.h"
#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
  unsigned char originalByte;
  unsigned char finalByte;
  size_t        bitNumber;
  bool          bitPresent;
} TestBits_s;

int TstBits(void)
{
  int result = 0;

  /* Test de la fonction BITS_SetBit */
  {
    TestBits_s setBits[] =
    {
      {0x00,  0x01, 0,  false},
      {0x03,  0x83, 7,  false},
      {0x03,  0x03, 1,  false}
    };

    for(size_t idx = 0; idx < (sizeof(setBits) / sizeof(setBits[0])); idx++)
    {
      if(BITS_SetBit(setBits[idx].originalByte, setBits[idx].bitNumber) == setBits[idx].finalByte)
      {
        printf("(BITS_SetBit) test %d OK\n", (int)(idx + 1));
      }
      else
      {
        printf("(BITS_SetBit) test %d KO\n", (int)(idx + 1));
        result = 1;
      }
    }
  }

  /* Test de la fonction BITS_ClearBit */
  {
    TestBits_s clearBits[] =
    {
      {0x01,  0x00, 0,  false},
      {0x83,  0x03, 7,  false},
      {0x80,  0x80, 1,  false}
    };

    for(size_t idx = 0; idx < (sizeof(clearBits) / sizeof(clearBits[0])); idx++)
    {
      if(BITS_ClearBit(clearBits[idx].originalByte, clearBits[idx].bitNumber) == clearBits[idx].finalByte)
      {
        printf("(BITS_ClearBit) test %d OK\n", (int)(idx + 1));
      }
      else
      {
        printf("(BITS_ClearBit) test %d KO\n", (int)(idx + 1));
        result = 1;
      }
    }
  }

  /* Test de la fonction BITS_TestBit */
  {
    TestBits_s testBits[] =
    {
      {0x01,  0x01, 0,  true},
      {0x03,  0x03, 7,  false}
    };

    for(size_t idx = 0; idx < (sizeof(testBits) / sizeof(testBits[0])); idx++)
    {
      if(BITS_TestBit(testBits[idx].originalByte, testBits[idx].bitNumber) == testBits[idx].bitPresent)
      {
        printf("(BITS_TestBit) test %d OK\n", (int)(idx + 1));
      }
      else
      {
        printf("(BITS_TestBit) test %d KO\n", (int)(idx + 1));
        result = 1;
      }
    }
  }

  /* Test de la fonction BITS_ReverseBit */
  {
    TestBits_s reverseBits[] =
    {
      {0x80,  0x01, 0,  false},
      {0xF0,  0x0F, 0,  false},
      {0x0C,  0x30, 0,  false},
      {0x00,  0x00, 0,  false},
      {0xFF,  0xFF, 0,  false}
    };

    for(size_t idx = 0; idx < (sizeof(reverseBits) / sizeof(reverseBits[0])); idx++)
    {
      if(BITS_ReverseBit(reverseBits[idx].originalByte) == reverseBits[idx].finalByte)
      {
        printf("(BITS_ReverseBit) test %d OK\n", (int)(idx + 1));
      }
      else
      {
        printf("(BITS_ReverseBit) test %d KO\n", (int)(idx + 1));
        result = 1;
      }
    }
  }

  return result;
}
