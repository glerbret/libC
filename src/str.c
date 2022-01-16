/**
 * @brief Gestion des chaines de caracteres.
 * @version 1.0.0.
 * @copyright MIT license.
 * @author Gregory Lerbret.
 */

#include "str.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define xstr(s) str(s)
#define str(s) #s

#define STR_NAME	    "Gestion des chaines de caracteres"
#define STR_VERS_MAJ    1
#define STR_VERS_MIN    0
#define STR_VERS_BRCH   0
#define STR_ID		    STR_NAME " - Version " xstr(STR_VERS_MAJ) "." xstr(STR_VERS_MIN) "." xstr(STR_VERS_BRCH)

const char* STR_Identifier(void)
{
  return STR_ID;
}

int STR_Version(void)
{
  return STR_VERS_MAJ * 10000 + STR_VERS_MIN * 100 + STR_VERS_BRCH;
}

char* STR_DelChar(char* dst, const char* src, size_t dstSize, char char2Delete)
{
  assert(dst);
  assert(src);
  assert(dstSize);

  for(; *src != '\0' && dstSize > 1; src++)
  {
    if(*src != char2Delete)
    {
      /* Le caractere courant doit etre conserve */
      *dst = *src;
      dst++;
      dstSize--;
    }
  }

  /* Une chaine se termine par un 0 */
  *dst = '\0';
  return dst;
}

char* STR_Strip(char* dst, const char* src, size_t dstSize)
{
  char* saveDst = dst;

  assert(dst);
  assert(src);
  assert(dstSize);

  /* Recherche du premier caractere non blanc de la chaine */
  for(; isspace(*src) != 0 && *src != '\0'; src++)
  {
    /* NOP */
  }

  /* Suppression des espaces superflux en debut de chaine */
  for(; *src != '\0' && dstSize > 1; src++, dstSize--, dst++)
  {
    *dst = *src;
  }

  /* Suppression des espaces superflux en fin de chaine
     Si rien n'a ete copie dans la chaine resultante (chaine initiale ne
     contenant que des espaces ou longueur de la chaine resultante de 1),
     on ne fait rien */
  for(; saveDst != dst && isspace(*(dst - 1)) != 0; dst--)
  {
    /* NOP */
  }

  /* Une chaine se termine par un 0 */
  *dst = '\0';
  return saveDst;
}

char* STR_String2Lower(char* dst, const char* src, size_t dstSize)
{
  assert(dst);
  assert(src);
  assert(dstSize);

  /* Parcours iteratif de la chaine de caractere avec conversion en minuscule */
  for(; *src != '\0' && dstSize > 1; dstSize--, dst++, src++)
  {
    *dst = (char)tolower(*src);
  }

  /* Une chaine se termine par un 0 */
  *dst = '\0';
  return dst;
}

char* STR_String2Upper(char* dst, const char* src, size_t dstSize)
{
  assert(dst);
  assert(src);
  assert(dstSize);

  /* Parcours iteratif de la chaine de caractere avec conversion en majuscule */
  for(; *src != '\0' && dstSize > 1; dstSize--, dst++, src++)
  {
    *dst = (char)toupper(*src);
  }

  /* Une chaine se termine par un 0 */
  *dst = '\0';
  return dst;
}

char* STR_LeftPadding(char* dst, const char* src, size_t dstSize, char padding)
{
  size_t srcSize = strlen(src);

  assert(dst);
  assert(src);
  assert(dstSize);

  if(srcSize >= dstSize)
  {
    /* La chaine intiale est trop longue, on tronque */
    memcpy(dst, src, dstSize - 1);
  }
  else
  {
    /* On remplit le buffer avec le caractere de padding ... */
    memset(dst, padding, dstSize - 1);

    /* ... et on copie la chaine initiale a la bonne position */
    memcpy(dst + dstSize - srcSize - 1, src, srcSize);
  }

  /* Une chaine se termine par un 0 */
  dst[dstSize - 1] = '\0';
  return dst;
}

char* STR_RightPadding(char* dst, const char* src, size_t dstSize, char padding)
{
  size_t srcSize = strlen(src);

  assert(dst);
  assert(src);
  assert(dstSize);

  if(srcSize >= dstSize)
  {
    /* La chaine intiale est trop longue, on tronque */
    memcpy(dst, src, dstSize - 1);
  }
  else
  {
    /* On remplit le buffer avec le caractere de padding ... */
    memset(dst, padding, dstSize - 1);

    /* ... et on copie la chaine initiale a la bonne position */
    memcpy(dst, src, srcSize);
  }

  /* Une chaine se termine par un 0 */
  dst[dstSize - 1] = '\0';
  return dst;
}

char* STR_Center(char* dst, const char* src, size_t dstSize, char padding)
{
  size_t srcSize = strlen(src);

  assert(dst);
  assert(src);
  assert(dstSize);

  if(srcSize >= dstSize)
  {
    /* La chaine intiale est trop longue, on tronque */
    memcpy(dst, src, dstSize - 1);
  }
  else
  {
    /* On remplit le buffer avec le caractere de padding ... */
    memset(dst, padding, dstSize - 1);

    /* ... et on copie la chaine initiale a la bonne position */
    memcpy(dst + ((dstSize - 1 - srcSize) / 2), src, srcSize);
  }

  /* Une chaine se termine par un 0 */
  dst[dstSize - 1] = '\0';
  return dst;
}

char* STR_StrDup(const char* src)
{
  assert(src);

  char* dst = malloc(strlen(src) + 1);
  if(dst != NULL)
  {
    strcpy(dst, src);
  }

  return dst;
}
