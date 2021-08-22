#pragma once

#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

#include "UI/ViewControllers/PositioningViewController.hpp"
#include "UI/ViewControllers/TextMeshSettingsViewController.hpp"
#include "UI/ViewControllers/ExtraSettingsViewController.hpp"
#include "UI/ViewControllers/ColoringViewController.hpp"
using namespace Slogans::UI;

#include "custom-types/shared/macros.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()

DECLARE_CLASS_CODEGEN(Slogans::UI::FlowCoordinators, SlogansFlowCoordinator, HMUI::FlowCoordinator,
                      DECLARE_INSTANCE_FIELD(ViewControllers::PositioningViewController*, PositioningViewController);
                      DECLARE_INSTANCE_FIELD(ViewControllers::TextMeshSettingsViewController*, TextMeshSettingsViewController);
                      DECLARE_INSTANCE_FIELD(ViewControllers::ExtraSettingsViewController*, ExtraSettingsViewController);
                      DECLARE_INSTANCE_FIELD(ViewControllers::ColoringViewController*, ColoringViewController);

                      DECLARE_INSTANCE_METHOD(void, Awake);

                      DECLARE_OVERRIDE_METHOD(void, DidActivate, GET_FIND_METHOD(&HMUI::FlowCoordinator::DidActivate), bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling);
                      DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, GET_FIND_METHOD(&HMUI::FlowCoordinator::BackButtonWasPressed), HMUI::ViewController* topViewController);
                      )