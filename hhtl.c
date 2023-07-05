#include "hhtl.h"

//#ifdef HHTL_EXEC
int main(int argc, char *argv[])
{
    hhtl_info_show();
    hash_test(10000000);
    return 0;
}
//#endif
