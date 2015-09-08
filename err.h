#ifndef ERR_H
# define ERR_H

#include <stdlib.h>
#include <stdio.h>

extern char *progname;

# define error_(msg, code, ...) { \
    fprintf(stderr, "%s: " msg "\n", progname, ##__VA_ARGS__); exit(code); }
# define error(msg, ...) error_(msg,-1, ##__VA_ARGS__)

# define warn(msg, ...) { \
    fprintf(stderr, "%s: " msg "\n", progname, ##__VA_ARGS__); }

#endif // ERR_H
