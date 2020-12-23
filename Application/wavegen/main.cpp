#include <math.h>

#include <zstack.h>

#include "main.h"

#define PI              (3.1415926)
#define SAMPLE_NUMBER   4096
#define SAMPLE_FREQ     (SAMPLE_NUMBER * 2)

struct application app;

int main(int argc, char *argv[])
{
    int i;

    if (param_parser(argc, argv, &app) == -1) {
        print_usage();
        return -1;
    }

    log_init(app.param.log_config);

    app.param.number = 2048;
    app.param.freq = 48;
    app.param.sample_freq = 1024; // Hz

    app.sample = (double *)malloc(app.param.number * sizeof(double));

    wavegen(app.sample, app.param.number, app.param.freq, app.param.sample_freq);

    for (i = 0; i < app.param.number; i++) {
        log_info("%f\n", app.sample[i]);
    }

    return 0;
}
