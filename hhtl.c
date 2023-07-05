#include <stdio.h>
#include "hhtl.h"

//#ifdef HHTL_EXEC
int main(int argc, char *argv[])
{
    hhtl_info_show();
    hash_test(10000000, 5, true);

    return 0;
}
//#endif
