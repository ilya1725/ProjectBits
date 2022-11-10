//

#include <stdio.h>

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <array>

#include "tlgr.hpp"

int main(int argc, char ** argv)
{
    using namespace std::literals::chrono_literals;

    tlgr::Tlgr logger{"/tmp/logger_test.txt"};

    logger.init();
    logger.timestamp().log("some test str").endl();

    std::array<uint8_t, 12> data{3};
    logger.timestamp().log("").log(data.cbegin(), data.cend()).endl();

    return 0;
}
