#pragma once
#include "main.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

namespace Slogans {
    class Hooks {
    private:
        inline static std::vector<void (*)(Logger &logger)> installFuncs;
    public:
        static void AddInstallFunc(void (*installFunc)(Logger &logger)) {
            installFuncs.push_back(installFunc);
        }

        static void InstallHooks(Logger &logger) {
            for (auto installFunc : installFuncs) {
                installFunc(logger);
            }
        }
    };
}
#define SlogansInstallHooks(func) \
struct __SlogansRegister##func { \
    __SlogansRegister##func() { \
        Slogans::Hooks::AddInstallFunc(func); \
    } \
}; \
static __SlogansRegister##func __SlogansRegisterInstance##func;