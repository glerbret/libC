#include <stdio.h>
#include <string.h>
#include "bits.h"
#include "test.h"

typedef struct
{
   unsigned char  ucOriginalByte;
   unsigned char  ucFinalByte;
   size_t         szBitNumber;
   bool           bBitPresent;
} TestBits_s;

int TstBits(void)
{
   int               iResult=0;
   size_t            szIdx;

   /* Test de la fonction BITS_SetBit */
   {
      TestBits_s     asSetBits[] =
      {
         {0x00,   0x01,    0,    false},
         {0x03,   0x83,    7,    false},
         {0x03,   0x03,    1,    false},
         {0x00,   0x00,    9,    false}
      };

      for(szIdx=0; szIdx<(sizeof(asSetBits)/sizeof(asSetBits[0])); szIdx++)
      {
         if(BITS_SetBit(asSetBits[szIdx].ucOriginalByte, asSetBits[szIdx].szBitNumber) == asSetBits[szIdx].ucFinalByte)
         {
            printf("(BITS_SetBit) test %d OK\n", (int)(szIdx+1));
         }
         else
         {
            printf("(BITS_SetBit) test %d KO\n", (int)(szIdx+1));
            iResult=1;
         }
      }
   }

   /* Test de la fonction BITS_ClearBit */
   {
      TestBits_s     asClearBits[] =
      {
         {0x01,   0x00,    0,    false},
         {0x83,   0x03,    7,    false},
         {0x80,   0x80,    1,    false},
         {0xFF,   0xFF,    9,    false}
      };

      for(szIdx=0; szIdx<(sizeof(asClearBits)/sizeof(asClearBits[0])); szIdx++)
      {
         if(BITS_ClearBit(asClearBits[szIdx].ucOriginalByte, asClearBits[szIdx].szBitNumber) == asClearBits[szIdx].ucFinalByte)
         {
            printf("(BITS_ClearBit) test %d OK\n", (int)(szIdx+1));
         }
         else
         {
            printf("(BITS_ClearBit) test %d KO\n", (int)(szIdx+1));
            iResult=1;
         }
      }
   }

   /* Test de la fonction BITS_TestBit */
   {
      TestBits_s     asTestBits[] =
      {
         {0x01,   0x01,    0,    true},
         {0x03,   0x03,    7,    false},
         {0xFF,   0xFF,    9,    false}
      };

      for(szIdx=0; szIdx<(sizeof(asTestBits)/sizeof(asTestBits[0])); szIdx++)
      {
         if(BITS_TestBit(asTestBits[szIdx].ucOriginalByte, asTestBits[szIdx].szBitNumber) == asTestBits[szIdx].bBitPresent)
         {
            printf("(BITS_TestBit) test %d OK\n", (int)(szIdx+1));
         }
         else
         {
            printf("(BITS_TestBit) test %d KO\n", (int)(szIdx+1));
            iResult=1;
         }
      }
   }

   /* Test de la fonction BITS_ReverseBit */
   {
      TestBits_s     asReverseBits[] =
      {
         {0x80,   0x01,    0,    false},
         {0xF0,   0x0F,    0,    false},
         {0x0C,   0x30,    0,    false},
         {0x00,   0x00,    0,    false},
         {0xFF,   0xFF,    0,    false}
      };

      for(szIdx=0; szIdx<(sizeof(asReverseBits)/sizeof(asReverseBits[0])); szIdx++)
      {
         if(BITS_ReverseBit(asReverseBits[szIdx].ucOriginalByte) == asReverseBits[szIdx].ucFinalByte)
         {
            printf("(BITS_ReverseBit) test %d OK\n", (int)(szIdx+1));
         }
         else
         {
            printf("(BITS_ReverseBit) test %d KO\n", (int)(szIdx+1));
            iResult=1;
         }
      }
   }

   return iResult;
}
