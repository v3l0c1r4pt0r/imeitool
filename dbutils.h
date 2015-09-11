/**
 * get data line from given DB associated with id given
 * \param id first column from csv file
 */
char *get_line_from_file(FILE *db, char *id);

/**
 * get data associated with id from FIRST of the db files present
 * \param id first column from csv file
 * \param filesuffix search only in files whose name ends with this
 * \return unparsed csv line
 */
char *get_line(char *id, char *filesuffix);
