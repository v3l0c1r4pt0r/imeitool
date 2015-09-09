#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbi.h"

char *get_rbi_description(char rbi[2])
{
    char *ret = NULL;
    FILE *rbifile = fopen(RBI_FILE, "r");
    ssize_t bytesread = 0;
    char *line = NULL;
    size_t n = 0;
    if(rbifile == NULL)
    {
        perror("fopen");
        return NULL;
    }

    while((bytesread = getline(&line, &n, rbifile)) > 0)
    {
        if(line[0] == '#')
        {
            continue;
        }
        if(rbi[0] == line[0] && rbi[1] == line[1])
        {
            // explode line
            char *el[RBI_FIELDS];
            int i = 1;
            el[0] = line;
            while(i < RBI_FIELDS &&
                    (el[i] = strchr(el[i - 1], ',') + 1) != NULL)
            {
                i++;
            }
//             for(i = 0; i < RBI_FIELDS; i++)
//             {
//                 printf("i=%d,el=%.*s\n", i, (i + 1 >= RBI_FIELDS ? (strchr(el[i], '\n') - el[i]) : (el[i+1] - el[i]) - 1), el[i]);
//             }
            size_t retsize = 0;
            char *end = strchr(el[RBI_F_DESCR], '\n');
            if(end == NULL)
            {
                retsize = strlen(el[RBI_F_DESCR]);
            }
            else
            {
                retsize = end - el[RBI_F_DESCR];
            }
            ret = (char*)malloc(retsize + 1);
            strncpy(ret, el[RBI_F_DESCR], retsize);
            break;
        }
    }
    return ret;
}
