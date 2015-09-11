#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbutils.h"
#include "rbi.h"

char *get_rbi_description(char rbi[2])
{
    char *ret = NULL;
    FILE *rbifile = fopen(RBI_FILE, "r");
    char *line = NULL;
    if(rbifile == NULL)
    {
        perror("fopen");
        return NULL;
    }

    line = get_line_from_file(rbifile, rbi);
    if(line != NULL)
    {
        ret = get_value_from_line(line, RBI_F_DESCR);
    }

    return ret;
}
