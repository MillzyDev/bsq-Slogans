#include "Config/RandomString.hpp"


std::string Slogans::Config::generateString(const int len) {
    // String generator by Ates Goral (https://stackoverflow.com/users/23501/ates-goral)
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}
