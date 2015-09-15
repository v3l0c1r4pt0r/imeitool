#define TAC_FILE_SUFFIX ".tac.csv"
#define TAC_FIELDS 4
#define TAC_F_TAC 0
#define TAC_F_VENDOR 1
#define TAC_F_MODEL 2
#define TAC_F_INTERN 3
#define TAC_POOL_SIZE 100

/**
 * get pool of TACs fulfilling given criteria
 * \param pool place where pool will be stored
 * \param vendor get TACs allocated by given vendor
 * \param model get TACs allocated for given model
 * \return number of TACs found
 */
unsigned int fill_tac_pool(char ***pool, char *vendor, char *model);

unsigned int fill_tac_pool_from_file(char **pool, char *vendor, char *model,
                                     FILE *file);
