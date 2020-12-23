#define _CRT_SECURE_NO_WARNINGS

#include <zstack.h>

#include <3rdparty/getopt.h>

#include "main.h"

enum {
    OPTION_VERSION = 1,
    OPTION_HELP,
    OPTION_LOG,
};

static struct option opts[] = {
    {"version", no_argument, 0, OPTION_VERSION},
    {"help", no_argument, 0, OPTION_HELP},
    {"log", required_argument, 0, OPTION_LOG},
    {0, 0, 0, 0}
};

int param_parser(int argc, char *argv[], struct application *app)
{
    int c;

    if (argc <= 1)
        return -1;

    while((c=getopt_long(argc, argv, "", opts, NULL))!=-1){
        switch (c) {
        case OPTION_VERSION:
            log(LOG_USER, "Version: %s\n", version);
            break;
        case OPTION_HELP:
            log(LOG_USER, usage);
            break;
        case OPTION_LOG:
            if (strlen(optarg) >= LOG_CONFIG_LENGTH) {
                log(LOG_USER, "log config out of range (0, %d)\n", LOG_CONFIG_LENGTH);
                return -1;
            }
            strncpy(app->param.log_config, optarg, LOG_CONFIG_LENGTH);
            break;
        default:
            return -1;
        }
    }

    if (argc >= 3) {
        if (strlen(argv[optind]) >= IP_LENGTH)
            return -1;
        memcpy(app->param.ip, argv[optind], strlen(argv[optind]));

        if (strlen(argv[optind+1]) >= FILENAME_MAX)
            return -1;
        memcpy(app->param.filename, argv[optind+1], strlen(argv[optind+1]));
    }

    // Do param validation

    return 0;
}