#pragma once

#include "custom-types/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
using namespace HMUI;

#include "UnityEngine/Transform.hpp"
using namespace UnityEngine;

#include <vector>
#include <string>

#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()

namespace Slogans::Config {
    class SloganConfig;
}
using namespace Slogans::Config;


DECLARE_CLASS_CODEGEN(Slogans::UI::ViewControllers, SlogansViewController, ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, GET_FIND_METHOD(&ViewController::DidActivate), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, GET_FIND_METHOD(&ViewController::DidDeactivate), bool removedFromHierarchy, bool screenSystemDisabling);

    DECLARE_INSTANCE_METHOD(void, LoadSlogans, Transform *parent);

public:
    std::vector<SloganConfig *> SerialiseConfigs(std::string path);
)