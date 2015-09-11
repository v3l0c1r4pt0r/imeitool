#include <string.h>
#include <stdint.h>

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

uint8_t luhn(imei_t imei)
{
    int i;
    uint8_t cur;
    uint8_t sum = 0;
    for(i = 0; i < sizeof(imei_t) - 1; i++)
    {
        cur = ((uint8_t*)&imei)[i] & 0x0f;
        cur *= (i % 2 ? 2 : 1);
        sum += (cur % 10) + (cur / 10);
    }
    return (10 - (sum % 10)) % 10;
}
