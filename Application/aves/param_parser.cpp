#define _CRT_SECURE_NO_WARNINGS

#include <zstack.h>

#include <3rdparty/getopt.h>

#include "main.h"

enum {
    OPTION_VERSION = 1,
    OPTION_HELP,
    OPTION_LOG,
    OPTION_CHANNEL,
};

static struct option opts[] = {
    {"version", no_argument, 0, OPTION_VERSION},
    {"help", no_argument, 0, OPTION_HELP},
    {"log", required_argument, 0, OPTION_LOG},
    {"channel", required_argument, 0, OPTION_CHANNEL},
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
            log_info("Version: %s\n", version);
            return -1;
        case OPTION_HELP:
            log_info(usage);
            return -1;
        case OPTION_LOG:
            if (strlen(optarg) >= LOG_CONFIG_LENGTH) {
                log_info("log config out of range (0, %d)\n", LOG_CONFIG_LENGTH);
                return -1;
            }
            strncpy(app->param.log_config, optarg, LOG_CONFIG_LENGTH);
            break;
        case OPTION_CHANNEL:
            app->param.channel = atoi(optarg);
            break;
        default:
            return -1;
        }
    }

    if (optind < argc) {
        if (strlen(argv[optind]) >= IP_LENGTH)
            return -1;
        memcpy(app->param.ip, argv[optind], strlen(argv[optind]));
    }

    if (optind + 1 < argc) {
        if (strlen(argv[optind+1]) >= FILENAME_MAX)
            return -1;
        memcpy(app->param.filename, argv[optind+1], strlen(argv[optind+1]));
    }

    // Do param validation

    if ('\0' != app->param.filename[0]) {
        app->param.dump_flag = 1;
    }

    if (app->param.channel > 2) {
        return -1;
    }

    return 0;
}
