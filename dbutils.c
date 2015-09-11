#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbutils.h"

char *get_value_from_line(char *line, unsigned int n)
{
    int i = 0;
    char *ret;
    char *start = line;
    size_t idlng;

    while(i != n)
    {
        char *newstart = strchr(start, DELIM) + 1;
        if(newstart == NULL)
        {
            break;
        }
        start = newstart;
        i++;
    }

    char *newstart = strchr(start, DELIM);
    if(newstart != NULL)
    {
        idlng = newstart - start;
    }
    else
    {
        idlng = strlen(start);
    }

    if(*(start + idlng - 1) == '\n')
    {
        idlng--;
    }

    ret = (char*)malloc(idlng);
    bzero(ret, idlng + 1);
    strncpy(ret, start, idlng);
    return ret;
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
