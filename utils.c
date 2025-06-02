#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

char* generate_pnr() {
    static char pnr[10];
    srand(time(NULL));
    snprintf(pnr, 10, "%09d", rand() % 1000000000);
    return pnr;
}
