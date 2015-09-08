/**
 * IMEI: (? - 2002)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - D
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |  RBI  |      TAC      |  FAC  |     Serial Number     |CHK|
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct
{
    char rbi[2];
    char tac[4];
    char fac[2];
    char sn[6];
    char luhn;
} imei_old_t;

/**
 * IMEISV: (? - 2002)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - E   E
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |  RBI  |      TAC      |  FAC  |     Serial Number     |  SVN  |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct
{
    char rbi[2];
    char tac[4];
    char fac[2];
    char sn[6];
    char svn[2];
} imeisv_old_t;

/**
 * IMEI: (01.01.2003 - 01.04.2004)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - D
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |  RBI  |      TAC      | 0 | 0 |     Serial Number     |CHK|
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *
 * IMEISV: (01.01.2003 - 01.04.2004)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - E   E
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |  RBI  |      TAC      | 0 | 0 |     Serial Number     |  SVN  |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */

/**
 * IMEI: (01.04.2004 - present)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - D
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |  RBI  |          TAC          |     Serial Number     |CHK|
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct
{
    char rbi[2];
    char tac[6];
    char sn[6];
    char luhn;
} imei_new_t;

/**
 * IMEISV: (01.04.2004 - present)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - E   E
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |  RBI  |          TAC          |     Serial Number     |  SVN  |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct
{
    char rbi[2];
    char tac[6];
    char sn[6];
    char svn[2];
} imeisv_new_t;

/**
 * IMEI: (01.04.2004 - present) - some countries ( mostly in Europe)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - D
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |              TAC              |     Serial Number     |CHK|
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct
{
    char tac[8];
    char sn[6];
    char luhn;
} imei_eu_t;

/**
 * IMEISV: (01.04.2004 - present) - some countries ( mostly in Europe)
 *  A    A - B   B   B   B   B   B - C   C   C   C   C   C - E   E
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |              TAC              |     Serial Number     |  SVN  |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 */
typedef struct
{
    char tac[8];
    char sn[6];
    char svn[2];
} imeisv_eu_t;

typedef union
{
    imei_old_t old;
    imei_new_t present;
    imei_eu_t eu;
} imei_t;

typedef union
{
    imeisv_old_t old;
    imeisv_new_t present;
    imeisv_eu_t eu;
} imeisv_t;

typedef enum
{
    RES_SUCCESS,
    RES_RBI_UNKNOWN,
    RES_IMEI,
    RES_IMEISV,
    RES_IMEI_LNG_INVALID,
    RES_IMEI_INVALID,
    RES_CHECKSUM_INVALID
} result_t;

/**
 * check if string is valid IMEI number
 */
result_t validate(char *imei);

/**
 * check if IMEI has valid checksum
 */
result_t luhn(imei_t imei);
