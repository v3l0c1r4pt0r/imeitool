#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbutils.h"
#include "tac.h"

unsigned int fill_tac_pool(char ***pool, char *vendor, char *model)
{
    if(vendor == NULL && model == NULL)
        return 0;

    *pool = malloc(TAC_POOL_SIZE * sizeof(char*));
    memset(*pool, '\xa5', TAC_POOL_SIZE * sizeof(char*));
//     bzero(*pool, TAC_POOL_SIZE * sizeof(char*));
    (*pool)[TAC_POOL_SIZE - 1] = (char*)-1;
    unsigned int ret = 0;
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
            ret += fill_tac_pool_from_file(*pool + ret, vendor, model, tacfile);
            if(ret == TAC_POOL_SIZE)
                break;
        }

        closedir(d);
    }
    return ret;
}

unsigned int fill_tac_pool_from_file(char **pool, char *vendor, char *model,
                                     FILE *file)
{
    ssize_t bytesread = 0;
    char *line = NULL;
    size_t n = 0;
    unsigned int ret = 0;

    if(vendor == NULL && model == NULL)
        return 0;

    while((bytesread = getline(&line, &n, file)) > 0)
    {
        if(*pool == (char*)-1)
        {
            break;
        }

        if(line[0] == '#')
        {
            continue;
        }

        char *lineid = get_value_from_line(line, TAC_F_TAC);
        size_t lng = strlen(lineid);
        if(lng < 1)
        {
            continue;
        }

        char *ven = get_value_from_line(line, TAC_F_VENDOR);
        char *mod = get_value_from_line(line, TAC_F_MODEL);

        if((vendor == NULL || strcmp(ven, vendor) == 0) &&
                (model == NULL || strcmp(mod, model) == 0))
        {
            *pool = lineid;
            pool++;
            ret++;
        }

        free(ven);
        free(mod);
    }
    return ret;
}
