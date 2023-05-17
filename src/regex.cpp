#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::string hello = "hello.txt";
    std::string reg0 = R"([a-z]+\.txt)";
    std::string reg1 = "[a-z]+\\.txt";      /*不用原始字符串的话需要用 \\ 来转义 \ */

    SPDLOG_INFO("match[{}]", std::regex_match(hello, std::regex(reg0)));
    SPDLOG_INFO("match[{}]", std::regex_match(hello, std::regex(reg1)));

    return 0;
}