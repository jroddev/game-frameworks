#include "spdlog/spdlog.h"
#include <dummy/dummy.h>

int main() {
    spdlog::info("Starting Tic-Tac-Toe ({})", dummy<std::string>(10));
    return 0;
}
