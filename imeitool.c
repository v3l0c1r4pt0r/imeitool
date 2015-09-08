#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "err.h"
#include "imeitool.h"

char *progname;

const char help_format[] =
    "Syntax: %s [OPTIONS]\n"
    "OPTIONS can be one of the following:\n"
    "  -h,  --help\tprint this help message and exit\n"
    "  -q,  --query IMEI|TAC\tquery databases for given IMEI or TAC\n"
    "  -n,  --new\tgenerate random IMEI\n"
    "  -v,  --vendor VENDOR\tgenerate IMEI with TAC allocated by VENDOR\n"
    "  -m,  --model MODEL\trestrict generation to specific MODEL\n"
    "       --rbi RBI\tgenerate IMEI using specific RBI\n"
    "\nDISCLAIMER:\n"
    "This program is intended to be used for educational purposes only and it\n"
    "should not be used to help user in any illegal activity. Author takes no\n"
    "responsibility for such actions.\n";

int main(int argc, char **argv)
{
    progname = argv[0];
    int c;
    int digit_optind = 0;
    struct options program_options = OPTIONS_NEW;

    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] =
        {
            {"help",     0,                 0, 'h'    },
            {"query",    required_argument, 0, 'q'    },
            {"new",      0,                 0, 'n'    },
            {"vendor",   required_argument, 0, 'v'    },
            {"model",    required_argument, 0, 'm'    },
            {"rbi",      required_argument, 0, OPT_RBI},
            {0,          0,                 0,  0     }
        };

        c = getopt_long(argc, argv, "h",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
                printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("option %c\n", c);
            break;

        case 'h':
            printf(help_format, argv[0]);
            exit(0);
            break;

        case 'q':
            program_options.mode = MOD_QUERY;
            program_options.imei = optarg;
            break;

        case 'n':
            program_options.mode = MOD_NEW;
            break;

        case 'v':
            program_options.vendor = optarg;
            break;

        case 'm':
            program_options.model = optarg;
            break;

        case OPT_RBI:
            program_options.rbi = optarg;
            printf("rbi:%s\n",optarg);
            break;

        case '?':
            exit(-1);
            break;

        default:
            error("getopt returned character code 0%o", c);
        }
    }
}
