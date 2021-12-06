/**
 * @author Gregory Lerbret
 * @brief Fichier de traces
 * @version 1.0.0
 * @copyright MIT license
 */

#include "traces.h"
#include "processus.h"
#include "print.h"
#include "date.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define TRACE_NAME	    "Fichier de traces"
#define TRACE_VERS_MAJ  1
#define TRACE_VERS_MIN  0
#define TRACE_VERS_BRCH 0
#define TRACE_ID		TRACE_NAME " - Version " xstr(TRACE_VERS_MAJ) "." xstr(TRACE_VERS_MIN) "." xstr(TRACE_VERS_BRCH)

const char* TRACE_Identifier(void)
{
    return TRACE_ID;
}

int TRACE_Version(void)
{
    return TRACE_VERS_MAJ * 10000 + TRACE_VERS_MIN * 100 + TRACE_VERS_BRCH;
}

void TRACE_ReportTrace(TRACE_Niveau_e level, const char* format, ... )
{
    va_list ap;
    pid_t pid;
    char msg[10000];
    char msg2[10000];
    char levelName[15];
    FILE* dst;
    char date[41];
    char debugFileName[256];
    const char fileName[] = "Log";
    const char fileExt[] = ".txt";

    va_start(ap, format);

    /* Creation du nom du fichier */
    DATE_GetTodayDate(date, sizeof date, "%Y%m%d");
    PRINT_snprintf(debugFileName, sizeof debugFileName, "%s%s%s", fileName, date, fileExt);

    /* Construction de la chaine */
    DATE_GetTodayDate(date, sizeof date, "%d/%m/%Y %H:%M:%S");
    PRINT_vsnprintf(msg2, sizeof msg2, format, ap);
    pid = PROCESS_getpid();

    levelName[0] = '\0';
    switch(level)
    {
#define GEN(a, b)             \
      case TRACE_ ## a:       \
         strncat(levelName, b, sizeof levelName - 1); \
         break;
#include "traces.gen"
#undef GEN

    default :
        strncat(levelName, "UNKN!!! :", sizeof levelName - 1);
        break;
    }
    PRINT_snprintf(msg, sizeof msg, "%s : <%d> %s %s\n", date, (int)pid, levelName, msg2);

    /* Ajout de la trace dans le fichier */
    dst = fopen(debugFileName, "a");
    if(dst != NULL)
    {
        fwrite(msg, strlen(msg), 1, dst);
        fclose(dst);
    }
    va_end(ap);
}
