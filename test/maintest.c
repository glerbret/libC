#include <stdio.h>
#include <string.h>
#include "test.h"

int main(void)
{
   int   iResult=0;

   if(TstLuhn() != 0)
   {
      iResult = 1;
   }
   if(TstStr() != 0)
   {
      iResult = 1;
   }
   if(TstIni() != 0)
   {
      iResult = 1;
   }
   if(TstDate() != 0)
   {
      iResult = 1;
   }
   if(iTstOpt() != 0)
   {
      iResult = 1;
   }
   if(TstBcd() != 0)
   {
      iResult = 1;
   }
   if(TstStack() != 0)
   {
      iResult = 1;
   }
   if(TstQueue() != 0)
   {
      iResult = 1;
   }
   if(TstList() != 0)
   {
      iResult = 1;
   }
   if(TstCList() != 0)
   {
      iResult = 1;
   }
   if(TstModulus97() != 0)
   {
      iResult = 1;
   }
   if(TstBits() != 0)
   {
      iResult = 1;
   }

   if(iResult==0)
   {
      printf("\n\nTests OK\n");
   }
   else
   {
      printf("\n\nTests echoues\n");
   }

   return 0;
}
