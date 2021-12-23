#pragma once

#include "custom-types/shared/macros.hpp"

#include "custom-types/shared/coroutine.hpp"
using namespace custom_types::Helpers;

#include "HMUI/ViewController.hpp"
using namespace HMUI;

#include "UnityEngine/Transform.hpp"
using namespace UnityEngine;

#include <vector>
#include <string>

#include "Config/SlogansConfig.hpp"
using namespace Slogans::Config;

#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()

DECLARE_CLASS_CODEGEN(Slogans::UI::ViewControllers, SloganSelectionViewController, ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, GET_FIND_METHOD(&ViewController::DidActivate), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, GET_FIND_METHOD(&ViewController::DidDeactivate), bool removedFromHierarchy, bool screenSystemDisabling);

public:
    custom_types::Helpers::Coroutine LoadSlogans(Transform *parent);
)