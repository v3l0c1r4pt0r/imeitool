#define TAC_FILE_SUFFIX ".tac.csv"
#define TAC_FIELDS 4
#define TAC_F_TAC 0
#define TAC_F_VENDOR 1
#define TAC_F_MODEL 2
#define TAC_F_INTERN 3

/**
 * get Type Allocation Code data from given DB associated with TAC given
 */
char *get_tac_line_from_file(FILE *db, char tac[8]);

/**
 * get data associated with TAC from FIRST of the db files present
 */
char *get_tac_line(char tac[8]);
