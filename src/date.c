/**
 * @author Gregory Lerbret
 * @brief Gestion de dates
 * @version 1.0.0
 * @copyright MIT license
 */

#include "date.h"

#include <time.h>
#include <locale.h>

#define xstr(s) str(s)
#define str(s) #s

#define DATE_NAME       "Gestion des dates"
#define DATE_VERS_MAJ   1
#define DATE_VERS_MIN   0
#define DATE_VERS_BRCH  0
#define DATE_ID         DATE_NAME " - Version " xstr(DATE_VERS_MAJ) "." xstr(DATE_VERS_MIN) "." xstr(DATE_VERS_BRCH)

const char* DATE_Identifier(void)
{
  return DATE_ID;
}

int DATE_Version(void)
{
  return DATE_VERS_MAJ * 10000 + DATE_VERS_MIN * 100 + DATE_VERS_BRCH;
}

const char* DATE_GetTodayDate(char* date, size_t dateSize, const char* format)
{
  time_t dateBin;
  struct tm* dateStruct;

  setlocale(LC_ALL, "");

  /* Lecture de la date */
  if(time(&dateBin) == (time_t) -1)
  {
    return NULL;
  }

  /* Formatage de la date */
  dateStruct = localtime(&dateBin);
  if (strftime(date, dateSize, format, dateStruct) == (size_t) 0)
  {
    return NULL;
  }

  return date;
}
