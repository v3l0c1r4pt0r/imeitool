#include <limits.h>

#define OPT_RBI UCHAR_MAX+1

#define OPTIONS_NEW {MOD_NOP, NULL, NULL, NULL, NULL}

typedef enum
{
    MOD_NOP,
    MOD_QUERY,
    MOD_NEW
} progmode_t;

struct options
{
    progmode_t mode;
    char *imei;
    char *vendor;
    char *model;
    char *rbi;
};