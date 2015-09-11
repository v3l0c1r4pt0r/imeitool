#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tac.h"

char *get_tac_line_from_file(FILE *db, char tac[8])
{
    ssize_t bytesread = 0;
    char *line = NULL;
    size_t n = 0;

    while((bytesread = getline(&line, &n, db)) > 0)
    {
        if(line[0] == '#')
        {
            continue;
        }
        if(strncmp(tac, line, 8) == 0)
        {
            return line;
        }
    }
    return NULL;
}

char *get_tac_line(char tac[8])
{
    char *ret = NULL;
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            char *needleptr = NULL;
            if((needleptr = strstr(dir->d_name, TAC_FILE_SUFFIX)) == NULL)
            {
                continue;
            }
            if(*(needleptr + sizeof(TAC_FILE_SUFFIX) - 1) != '\0')
            {
                continue;
            }

            // is valid TAC db, search
            FILE *tacfile = fopen(dir->d_name, "r");
            if(tacfile == NULL)
            {
                perror("fopen");
                continue;
            }
            ret = get_tac_line_from_file(tacfile, tac);
            if(ret != NULL)
                break;
        }

        closedir(d);
    }

    return ret;
}
