#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbutils.h"
#include "tac.h"

char *get_tac_element(char *tac, unsigned int n)
{
    char *ret = NULL;
    char *line = get_line(tac, TAC_FILE_SUFFIX);
    if(line)
    {
        ret = get_value_from_line(line, n);
    }
    return ret;
}
