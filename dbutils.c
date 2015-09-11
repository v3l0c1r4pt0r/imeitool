#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbutils.h"

char *get_line_from_file(FILE *db, char *id)
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
        //FIXME: compare first column instead of const num of bytes
        if(strncmp(id, line, 8) == 0)
        {
            return line;
        }
    }
    return NULL;
}

char *get_line(char *id, char *filesuffix)
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
            if((needleptr = strstr(dir->d_name, filesuffix)) == NULL)
            {
                continue;
            }
            if(*(needleptr + strlen(filesuffix)) != '\0')
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
            ret = get_line_from_file(tacfile, id);
            if(ret != NULL)
                break;
        }

        closedir(d);
    }

    return ret;
}
