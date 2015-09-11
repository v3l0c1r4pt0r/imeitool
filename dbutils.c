#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbutils.h"

char *get_value_from_line(char *line, unsigned int n)
{
    char *ret;
    if(n == 0)
    {
        size_t idlng = strchr(line, DELIM) - line;
        ret = (char*)malloc(idlng);
        strncpy(ret, line, idlng);
        return ret;
    }
    else
    {
        //TODO
        return NULL;
    }
}

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
        char *lineid = get_value_from_line(line, 0);
        if(strncmp(id, lineid, strlen(lineid)) == 0)
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
