/**
   \author Gr�gory Lerbret
   \file ebcdic.c
   \brief Gestion du chaset EBCDIC.<br>
   \date 14/12/2005
   \version 1.0.0
*/

#include "ebcdic.h"

#define xstr(s) str(s)
#define str(s) #s

#define EBCDIC_NAME           "Gestion EBCDIC"
#define EBCDIC_VERS_MAJ       1
#define EBCDIC_VERS_MIN       0
#define EBCDIC_VERS_BRCH      0
#define EBCDIC_ID             EBCDIC_NAME " - Version " xstr(EBCDIC_VERS_MAJ) "." xstr(EBCDIC_VERS_MIN) "." xstr(EBCDIC_VERS_BRCH)

#define EBCDIC_SP             0x40
#define ASCII_SP              0x20

/* Table de correspondace ASCII vers EBCDIC */
static const int aiASCII2EBCDIC[] =
{
   /*       ASCII       EBCDIC
            |           |
            |           |
            V           V */
   /*       0x00 */     0x00,
   /* SOH   0x01 */     0x01,
   /* STX   0x02 */     0x02,
   /* ETX   0x03 */     0x03,
   /* EOT   0x04 */     0x37,
   /* ENQ   0x05 */     0x2D,
   /* ACK   0x06 */     0x2E,
   /* BEL   0x07 */     0x2F,
   /* BS    0x08 */     0x16,
   /* HT    0x09 */     0x05,
   /* LF    0x0A */     0x25,
   /* VT    0x0B */     0x0B,
   /* FF    0x0C */     0x0C,
   /* CR    0x0D */     0x0D,
   /* SO    0x0E */     0x0E,
   /* SI    0x0F */     0x0F,
   /* DLE   0x10 */     0x10,
   /* DC1   0x11 */     0x11,
   /* DC2   0x12 */     0x12,
   /* DC3   0x13 */     0x13,
   /* DC4   0x14 */     0x3C,
   /* NAK   0x15 */     0x3D,
   /* SYN   0x16 */     0x32,
   /* ETB   0x17 */     0x26,
   /* CAN   0x18 */     0x18,
   /* EM    0x19 */     0x19,
   /* SUB   0x1A */     0x3F,
   /* ESC   0x1B */     0x27,
   /* FS    0x1C */     0x1C,
   /* GS    0x1D */     0x1D,
   /* RS    0x1E */     0x1E,
   /* US    0x1F */     0x1F,
   /* SP    0x20 */     0x40,
   /* !     0x21 */     0x5A,
   /*       0x22 */     0x7F,
   /* #     0x23 */     0x7B,
   /* $     0x24 */     0x5B,
   /* %     0x25 */     0x6C,
   /* &     0x26 */     0x50,
   /* �     0x27 */     0x7D,
   /* (     0x28 */     0x4D,
   /* )     0x29 */     0x5D,
   /* *     0x2A */     0x5C,
   /* +     0x2B */     0x4E,
   /* ,     0x2C */     0x6B,
   /* -     0x2D */     0x60,
   /* .     0x2E */     0x4B,
   /* /     0x2F */     0x61,
   /* 0     0x30 */     0xF0,
   /* 1     0x31 */     0xF1,
   /* 2     0x32 */     0xF2,
   /* 3     0x33 */     0xF3,
   /* 4     0x34 */     0xF4,
   /* 5     0x35 */     0xF5,
   /* 6     0x36 */     0xF6,
   /* 7     0x37 */     0xF7,
   /* 8     0x38 */     0xF8,
   /* 9     0x39 */     0xF9,
   /* :     0x3A */     0x7A,
   /* ;     0x3B */     0x5E,
   /* <     0x3C */     0x4C,
   /* =     0x3D */     0x7E,
   /* >     0x3E */     0x6E,
   /* ?     0x3F */     0x6F,
   /* @     0x40 */     0x7C,
   /* A     0x41 */     0xC1,
   /* B     0x42 */     0xC2,
   /* C     0x43 */     0xC3,
   /* D     0x44 */     0xC4,
   /* E     0x45 */     0xC5,
   /* F     0x46 */     0xC6,
   /* G     0x47 */     0xC7,
   /* H     0x48 */     0xC8,
   /* I     0x49 */     0xC9,
   /* J     0x4A */     0xD1,
   /* K     0x4B */     0xD2,
   /* L     0x4C */     0xD3,
   /* M     0x4D */     0xD4,
   /* N     0x4E */     0xD5,
   /* O     0x4F */     0xD6,
   /* P     0x50 */     0xD7,
   /* Q     0x51 */     0xD8,
   /* R     0x52 */     0xD9,
   /* S     0x53 */     0xE2,
   /* T     0x54 */     0xE3,
   /* U     0x55 */     0xE4,
   /* V     0x56 */     0xE5,
   /* W     0x57 */     0xE6,
   /* X     0x58 */     0xE7,
   /* Y     0x59 */     0xE8,
   /* Z     0x5A */     0xE9,
   /* [     0x5B */     0x4A,
   /* \     0x5C */     0xE0,
   /* ]     0x5D */     0x5A,
   /* ^     0x5E */     0x5F,
   /* _     0x5F */     0x6D,
   /* `     0x60 */     0x79,
   /* a     0x61 */     0x81,
   /* b     0x62 */     0x82,
   /* c     0x63 */     0x83,
   /* d     0x64 */     0x84,
   /* e     0x65 */     0x85,
   /* f     0x66 */     0x86,
   /* g     0x67 */     0x87,
   /* h     0x68 */     0x88,
   /* i     0x69 */     0x89,
   /* j     0x6A */     0x91,
   /* k     0x6B */     0x92,
   /* l     0x6C */     0x93,
   /* m     0x6D */     0x94,
   /* n     0x6E */     0x95,
   /* o     0x6F */     0x96,
   /* p     0x70 */     0x97,
   /* q     0x71 */     0x98,
   /* r     0x72 */     0x99,
   /* s     0x73 */     0xA2,
   /* t     0x74 */     0xA3,
   /* u     0x75 */     0xA4,
   /* v     0x76 */     0xA5,
   /* w     0x77 */     0xA6,
   /* x     0x78 */     0xA7,
   /* y     0x79 */     0xA8,
   /* z     0x7A */     0xA9,
   /* {     0x7B */     0xC0,
   /* |     0x7C */     0x6A,
   /* }     0x7D */     0xD0,
   /* ~     0x7E */     0xA1,
   /* DEL   0x7F */     0x07,
};

/* Table de correspondance EBCDIC vers ASCII */
static const int aiEBCDIC2ASCII[] =
{
   /*       EBCDIC      ASCII
            |           |
            |           |
            V           V */
   /* NUL   0x00 */     0x00,
   /* SOH   0x01 */     0x01,
   /* STX   0x02 */     0x02,
   /* ETX   0x03 */     0x03,
   /* PF    0x04 */     ASCII_SP,
   /* HT    0x05 */     0x09,
   /* LC    0x06 */     ASCII_SP,
   /* DEL   0x07 */     0x7F,
   /* GE    0x08 */     ASCII_SP,
   /* RLF   0x09 */     ASCII_SP,
   /* SMM   0x0A */     0x60,
   /* VT    0x0B */     0x0B,
   /* FF    0x0C */     0x0C,
   /* CR    0x0D */     0x0D,
   /* SO    0x0E */     0x0E,
   /* SI    0x0F */     0x0F,
   /* DLE   0x10 */     0x10,
   /* DC1   0x11 */     0x11,
   /* DC2   0x12 */     0x12,
   /* TM    0x13 */     0x13,
   /* RES   0x14 */     0x3C,
   /* NL    0x15 */     0x0A,
   /* BS    0x16 */     0x08,
   /* IL    0x17 */     ASCII_SP,
   /* CAN   0x18 */     0x18,
   /* EM    0x19 */     0x19,
   /* CC    0x1A */     ASCII_SP,
   /* CU1   0x1B */     ASCII_SP,
   /* IFS   0x1C */     0x1C,
   /* IGS   0x1D */     0x1D,
   /* IRS   0x1E */     0x1E,
   /* IUS   0x1F */     0x1F,
   /* DS    0x20 */     ASCII_SP,
   /* SOS   0x21 */     ASCII_SP,
   /* FS    0x22 */     ASCII_SP,
   /*       0x23 */     ASCII_SP,
   /* BYP   0x24 */     ASCII_SP,
   /* LF    0x25 */     0x0A,
   /* ETB   0x26 */     0x17,
   /* ESC   0x27 */     0x1B,
   /*       0x28 */     ASCII_SP,
   /*       0x29 */     ASCII_SP,
   /* SM    0x2A */     ASCII_SP,
   /* CU2   0x2B */     ASCII_SP,
   /*       0x2C */     ASCII_SP,
   /* ENQ   0x2D */     0x05,
   /* ACK   0x2E */     0x06,
   /* BEL   0x2F */     0x07,
   /*       0x30 */     ASCII_SP,
   /*       0x31 */     ASCII_SP,
   /* SYN   0x32 */     0x16,
   /*       0x33 */     ASCII_SP,
   /* PN    0x34 */     ASCII_SP,
   /* RS    0x35 */     ASCII_SP,
   /* UC    0x36 */     ASCII_SP,
   /* EOT   0x37 */     0x04,
   /*       0x38 */     ASCII_SP,
   /*       0x39 */     ASCII_SP,
   /*       0x3A */     ASCII_SP,
   /* CU3   0x3B */     ASCII_SP,
   /* DC4   0x3C */     0x14,
   /* NAK   0x3D */     0x15,
   /*       0x3E */     ASCII_SP,
   /* SUB   0x3F */     0x1A,
   /* SP    0x40 */     0x20,
   /*       0x41 */     ASCII_SP,
   /*       0x42 */     ASCII_SP,
   /*       0x43 */     ASCII_SP,
   /*       0x44 */     ASCII_SP,
   /*       0x45 */     ASCII_SP,
   /*       0x46 */     ASCII_SP,
   /*       0x47 */     ASCII_SP,
   /*       0x48 */     ASCII_SP,
   /*       0x49 */     ASCII_SP,
   /* �     0x4A */     0x5B,
   /* .     0x4B */     0x2E,
   /* <     0x4C */     0x3C,
   /* (     0x4D */     0x28,
   /* +     0x4E */     0x2B,
   /* |     0x4F */     0x21,
   /* &     0x50 */     0x26,
   /*       0x51 */     ASCII_SP,
   /*       0x52 */     ASCII_SP,
   /*       0x53 */     ASCII_SP,
   /*       0x54 */     ASCII_SP,
   /*       0x55 */     ASCII_SP,
   /*       0x56 */     ASCII_SP,
   /*       0x57 */     ASCII_SP,
   /*       0x58 */     ASCII_SP,
   /*       0x59 */     ASCII_SP,
   /* !     0x5A */     0x21,
   /* $     0x5B */     0x24,
   /* *     0x5C */     0x2A,
   /* )     0x5D */     0x29,
   /* ;     0x5E */     0x3B,
   /* ^     0x5F */     0x5E,
   /* -     0x60 */     0x2D,
   /* /     0x61 */     0x2F,
   /*       0x62 */     ASCII_SP,
   /*       0x63 */     ASCII_SP,
   /*       0x64 */     ASCII_SP,
   /*       0x65 */     ASCII_SP,
   /*       0x66 */     ASCII_SP,
   /*       0x67 */     ASCII_SP,
   /*       0x68 */     ASCII_SP,
   /*       0x69 */     ASCII_SP,
   /*       0x6A */     0x7C,
   /* ,     0x6B */     0x2C,
   /* %     0x6C */     0x25,
   /* _     0x6D */     0x5F,
   /* >     0x6E */     0x3E,
   /* ?     0x6F */     0x3F,
   /*       0x70 */     ASCII_SP,
   /*       0x71 */     ASCII_SP,
   /*       0x72 */     ASCII_SP,
   /*       0x73 */     ASCII_SP,
   /*       0x74 */     ASCII_SP,
   /*       0x75 */     ASCII_SP,
   /*       0x76 */     ASCII_SP,
   /*       0x77 */     ASCII_SP,
   /*       0x78 */     ASCII_SP,
   /*       0x79 */     0x60,
   /* :     0x7A */     0x3A,
   /* #     0x7B */     0x23,
   /* @     0x7C */     0x40,
   /* �     0x7D */     0x27,
   /* =     0x7E */     0x3D,
   /* �     0x7F */     0x22,
   /*       0x80 */     ASCII_SP,
   /* a     0x81 */     0x61,
   /* b     0x82 */     0x62,
   /* c     0x83 */     0x63,
   /* d     0x84 */     0x64,
   /* e     0x85 */     0x65,
   /* f     0x86 */     0x66,
   /* g     0x87 */     0x67,
   /* h     0x88 */     0x68,
   /* i     0x89 */     0x69,
   /*       0x8A */     ASCII_SP,
   /* {     0x8B */     0x7F,
   /* <     0x8C */     0x7F,
   /* (     0x8D */     0x7F,
   /* +     0x8E */     0x7F,
   /*       0x8F */     ASCII_SP,
   /*       0x90 */     ASCII_SP,
   /* j     0x91 */     0x6A,
   /* k     0x92 */     0x6B,
   /* l     0x93 */     0x6C,
   /* m     0x94 */     0x6D,
   /* n     0x95 */     0x6E,
   /* o     0x96 */     0x6F,
   /* p     0x97 */     0x70,
   /* q     0x98 */     0x71,
   /* r     0x99 */     0x72,
   /*       0x9A */     ASCII_SP,
   /* }     0x9B */     ASCII_SP,
   /*       0x9C */     ASCII_SP,
   /* )     0x9D */     ASCII_SP,
   /* +-    0x9E */     ASCII_SP,
   /*       0x9F */     ASCII_SP,
   /*       0xA0 */     ASCII_SP,
   /* ~     0xA1 */     0x7E,
   /* s     0xA2 */     0x73,
   /* t     0xA3 */     0x74,
   /* u     0xA4 */     0x75,
   /* v     0xA5 */     0x76,
   /* w     0xA6 */     0x77,
   /* x     0xA7 */     0x78,
   /* y     0xA8 */     0x79,
   /* z     0xA9 */     0x7A,
   /*       0xAA */     ASCII_SP,
   /*       0xAB */     ASCII_SP,
   /*       0xAC */     ASCII_SP,
   /*       0xAD */     ASCII_SP,
   /*       0xAE */     ASCII_SP,
   /*       0xAF */     ASCII_SP,
   /*       0xB0 */     ASCII_SP,
   /*       0xB1 */     ASCII_SP,
   /*       0xB2 */     ASCII_SP,
   /*       0xB3 */     ASCII_SP,
   /*       0xB4 */     ASCII_SP,
   /*       0xB5 */     ASCII_SP,
   /*       0xB6 */     ASCII_SP,
   /*       0xB7 */     ASCII_SP,
   /*       0xB8 */     ASCII_SP,
   /*       0xB9 */     ASCII_SP,
   /*       0xBA */     ASCII_SP,
   /*       0xBB */     ASCII_SP,
   /*       0xBC */     ASCII_SP,
   /*       0xBD */     ASCII_SP,
   /*       0xBE */     ASCII_SP,
   /*       0xBF */     ASCII_SP,
   /* {     0xC0 */     0x7B,
   /* A     0xC1 */     0x41,
   /* B     0xC2 */     0x42,
   /* C     0xC3 */     0x43,
   /* D     0xC4 */     0x44,
   /* E     0xC5 */     0x45,
   /* F     0xC6 */     0x46,
   /* G     0xC7 */     0x47,
   /* H     0xC8 */     0x48,
   /* I     0xC9 */     0x49,
   /*       0xCA */     ASCII_SP,
   /*       0xCB */     ASCII_SP,
   /*       0xCC */     ASCII_SP,
   /*       0xCD */     ASCII_SP,
   /*       0xCE */     ASCII_SP,
   /*       0xCF */     ASCII_SP,
   /* }     0xD0 */     0x7D,
   /* J     0xD1 */     0x4A,
   /* K     0xD2 */     0x4B,
   /* L     0xD3 */     0x4C,
   /* M     0xD4 */     0x4D,
   /* N     0xD5 */     0x4E,
   /* O     0xD6 */     0x4F,
   /* P     0xD7 */     0x50,
   /* Q     0xD8 */     0x51,
   /* R     0xD9 */     0x52,
   /*       0xDA */     ASCII_SP,
   /*       0xDB */     ASCII_SP,
   /*       0xDC */     ASCII_SP,
   /*       0xDD */     ASCII_SP,
   /*       0xDE */     ASCII_SP,
   /*       0xDF */     ASCII_SP,
   /* \     0xE0 */     0x5C,
   /*       0xE1 */     ASCII_SP,
   /* S     0xE2 */     0x53,
   /* T     0xE3 */     0x54,
   /* U     0xE4 */     0x55,
   /* V     0xE5 */     0x56,
   /* W     0xE6 */     0x57,
   /* X     0xE7 */     0x58,
   /* Y     0xE8 */     0x59,
   /* Z     0xE9 */     0x5A,
   /*       0xEA */     ASCII_SP,
   /*       0xEB */     ASCII_SP,
   /*       0xEC */     ASCII_SP,
   /*       0xED */     ASCII_SP,
   /*       0xEE */     ASCII_SP,
   /*       0xEF */     ASCII_SP,
   /* 0     0xF0 */     0x30,
   /* 1     0xF1 */     0x31,
   /* 2     0xF2 */     0x32,
   /* 3     0xF3 */     0x33,
   /* 4     0xF4 */     0x34,
   /* 5     0xF5 */     0x35,
   /* 6     0xF6 */     0x36,
   /* 7     0xF7 */     0x37,
   /* 8     0xF8 */     0x38,
   /* 9     0xF9 */     0x39,
   /*       0xFA */     ASCII_SP,
   /*       0xFB */     ASCII_SP,
   /*       0xFC */     ASCII_SP,
   /*       0xFD */     ASCII_SP,
   /*       0xFE */     ASCII_SP,
   /*       0xFF */     ASCII_SP
};

/**
   \fn const char* EBCDIC_Identifier(void)
   \brief Identification du module.
   \return L'identifiant du module (nom et version).
*/
const char* EBCDIC_Identifier(void)
{
   return EBCDIC_ID;
}

/**
   \fn int EBCDIC_Version(void)
   \brief Version du module.
   \return La version du module.
*/
int EBCDIC_Version(void)
{
   return EBCDIC_VERS_MAJ*10000 + EBCDIC_VERS_MIN*100 + EBCDIC_VERS_BRCH;
}

/**
   \fn int EBCDIC_ConvertASCII2EBCDIC(int iASCII)
   \brief Conversion ASCI vers EBCDIC.
   \param[in] iASCII le caractere au format ASCII
   \return Le caractere au format EBCDIC.
*/
int EBCDIC_ConvertASCII2EBCDIC(int iASCII)
{
   if(iASCII < (int)(sizeof aiASCII2EBCDIC / sizeof aiASCII2EBCDIC[0]))
   {
      return aiASCII2EBCDIC[iASCII];
   }
   else
   {
      /* Le caractere n'est pas present dans la table de conversion, on le remplace par un espace */
      return EBCDIC_SP;
   }
}

/**
   \fn int EBCDIC_ConvertEBCDIC2ASCII(int iEBCDIC)
   \brief Conversion EBCDIC vers ASCII.
   \param[in] iEBCDIC le caractere au format EBCDIC
   \return Le caractere au format ASCII.
*/
int EBCDIC_ConvertEBCDIC2ASCII(int iEBCDIC)
{
   if(iEBCDIC < (int)(sizeof aiEBCDIC2ASCII / sizeof aiEBCDIC2ASCII[0]))
   {
      return aiEBCDIC2ASCII[iEBCDIC];
   }
   else
   {
      /* Le caractere n'est pas present dans la table de conversion, on le remplace par un espace */
      return ASCII_SP;
   }
}