#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>

#include "err.h"
#include "imei.h"
#include "rbi.h"
#include "tac.h"
#include "dbutils.h"
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
    "       --rbi RBI\tgenerate IMEI using specific RBI (cannot be used along\n"
    "       \t\t\twith -v and -m)\n"
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

        c = getopt_long(argc, argv, "hq:nv:m:",
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
            break;

        case '?':
            exit(-1);
            break;

        default:
            error("getopt returned character code 0%o", c);
        }
    }

    switch(program_options.mode)
    {
    case MOD_QUERY:
    {
        result_t ret = validate(program_options.imei);
        if(ret == RES_IMEI)
        {
            imei_t imei = *(imei_t*)program_options.imei;
            uint8_t chk = luhn(imei);
            char *line = get_line(imei.eu.tac, TAC_FILE_SUFFIX);
            char *vendor = "(unknown)", *model = "(unknown)";
            if(line)
            {
                vendor = get_value_from_line(line, TAC_F_VENDOR);
                model = get_value_from_line(line, TAC_F_MODEL);
            }
            printf("RBI: %.2s [%s]\n"
                   "TAC: %.8s\n"
                   "Vendor: %s\n"
                   "Model: %s\n"
                   "Serial Number: %.6s\n"
                   "Type: %s\n"
                   "Checksum: %s",
                   imei.present.rbi,
                   get_rbi_description(imei.present.rbi),
                   imei.eu.tac,
                   vendor,
                   model,
                   imei.eu.sn,
                   "IMEI",
                   (chk == (imei.eu.luhn & 0x0f) ? "valid" : "invalid"));
            if(chk != (imei.eu.luhn & 0x0f))
            {
                printf(" (valid: %d)\n", chk);
            }
            else
            {
                printf("\n");
            }
        }
        else if(ret == RES_IMEISV)
        {
            imeisv_t imeisv = *(imeisv_t*)program_options.imei;
            char *line = get_line(imeisv.eu.tac, TAC_FILE_SUFFIX);
            char *vendor = "(unknown)", *model = "(unknown)";
            if(line)
            {
                vendor = get_value_from_line(line, TAC_F_VENDOR);
                model = get_value_from_line(line, TAC_F_MODEL);
            }
            printf("RBI: %.2s [%s]\n"
                   "TAC: %.8s\n"
                   "Vendor: %s\n"
                   "Model: %s\n"
                   "Serial Number: %.6s\n"
                   "Type: %s\n"
                   "SVN: %.2s\n",
                   imeisv.present.rbi,
                   get_rbi_description(imeisv.present.rbi),
                   imeisv.eu.tac,
                   vendor,
                   model,
                   imeisv.eu.sn,
                   "IMEISV",
                   imeisv.eu.svn);
        }
        else if(ret == RES_IMEI_LNG_INVALID)
        {
            size_t lng = strlen(program_options.imei);
            if(lng >= 2 && lng <= 8)
            {
                //only TAC given
                char *line = get_line(program_options.imei, TAC_FILE_SUFFIX);
                char *vendor = "(unknown)", *model = "(unknown)";
                if(line)
                {
                    vendor = get_value_from_line(line, TAC_F_VENDOR);
                    model = get_value_from_line(line, TAC_F_MODEL);
                }
                printf("RBI: %.2s [%s]\n"
                       "Vendor: %s\n"
                       "Model: %s\n"
                       "Type: %s\n",
                       program_options.imei,
                       get_rbi_description(program_options.imei),
                       vendor,
                       model,
                       "TAC");
            }
            else
            {
                error("Validation returned error %d",ret);
            }
        }
        else
        {
            error("Validation returned error %d",ret);
        }
        break;
    }
    case MOD_NEW:
    {
        srand(time(NULL));
        int i;
        char **tac_pool = NULL;
        unsigned int pool_size;
        if(program_options.rbi != NULL)
        {
            pool_size = 1;
            tac_pool = malloc(sizeof(char *));
            *tac_pool = program_options.rbi;
        }
        else
        {
            pool_size = fill_tac_pool(&tac_pool,
                                      program_options.vendor,
                                      program_options.model);
        }
        imei_t imei;
        char *outimei = (char*)&imei;
        unsigned int randtac = rand() % pool_size;
        size_t tacsize = strlen(tac_pool[randtac]);
        memcpy(imei.eu.tac, tac_pool[randtac], tacsize);
        char sn[sizeof(imei.eu.sn) + sizeof(imei.eu.tac) - tacsize];
        for(i = 0; i < sizeof(imei.eu.sn) + sizeof(imei.eu.tac) - tacsize; i++)
        {
            sn[i] = rand() % 10 | '0';
        }
        memcpy(outimei + tacsize, sn, sizeof(sn));
        imei.eu.luhn = luhn(imei) | '0';
        printf("%s\n", outimei);
        break;
    }
    default:
        error("You have to use query or new mode");
    }
}
