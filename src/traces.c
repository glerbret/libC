/**
 * @author Gregory Lerbret
 * @brief Fichier de traces
 * @date 07/04/2005
 * @version 1.0.0
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

void TRACE_ReportTrace(TRACE_Niveau_e eNiveau, const char *pcFormat, ... )
{
    va_list ap;
    pid_t Pid;
    char acMsg[10000];
    char acMsg2[10000];
    char acLevel[15];
    FILE* fDest;
    char acDate[41];
    char acDebugFilName[256];
    const char acFileName[] = "Log";
    const char acFileExt[] = ".txt";

    va_start(ap, pcFormat);

    /* Creation du nom du fichier */
    DATE_GetTodayDate(acDate, sizeof acDate, "%Y%m%d");
    PRINT_snprintf(acDebugFilName, sizeof acDebugFilName, "%s%s%s", acFileName, acDate, acFileExt);

    /* Construction de la chaine */
    DATE_GetTodayDate(acDate, sizeof acDate, "%d/%m/%Y %H:%M:%S");
    PRINT_vsnprintf(acMsg2, sizeof acMsg2, pcFormat, ap);
    Pid = PROCESS_getpid();

    acLevel[0] = '\0';
    switch(eNiveau)
    {
#define GEN(a, b)             \
      case TRACE_ ## a:       \
         strncat(acLevel, b, sizeof acLevel - 1); \
         break;
#include "traces.gen"
#undef GEN

    default :
        strncat(acLevel, "UNKN!!! :", sizeof acLevel - 1);
        break;
    }
    PRINT_snprintf(acMsg, sizeof acMsg, "%s : <%d> %s %s\n", acDate, (int)Pid, acLevel, acMsg2);

    /* Ajout de la trace dans le fichier */
    fDest = fopen(acDebugFilName, "a");
    if(fDest != NULL)
    {
        fwrite(acMsg, strlen(acMsg), 1, fDest);
        fclose(fDest);
    }
    va_end(ap);
}
