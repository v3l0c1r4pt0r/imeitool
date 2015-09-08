#include <string.h>

#include "imei.h"

result_t validate(char *imei)
{
    int i;
    result_t ret = RES_IMEI_INVALID;
    size_t lng = strlen(imei);

    if(lng == 15)
    {
        ret = RES_IMEI;
    }
    else if(lng == 16)
    {
        ret = RES_IMEISV;
    }
    else
    {
        return RES_IMEI_LNG_INVALID;
    }

    for(i = 0; i < lng; i++)
    {
        if(imei[i] < '0' || imei[i] > '9')
            return RES_IMEI_INVALID;
    }

    return ret;
}
