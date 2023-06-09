#include "3rdparty.h"

int main()
{
    spdlog_init();

    SPDLOG_INFO("__cplusplus[{}]", __cplusplus);

    return 0;
}