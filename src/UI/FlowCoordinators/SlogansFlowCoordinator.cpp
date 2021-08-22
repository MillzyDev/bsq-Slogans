#include "main.hpp"

#include "UI/FlowCoordinators/SlogansFlowCoordinator.hpp"
#include "Config/Config.hpp"

#include "System/Action.hpp"
#include "System/Action_1.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
using namespace QuestUI;

DEFINE_TYPE(Slogans::UI::FlowCoordinators, SlogansFlowCoordinator);

void Slogans::UI::FlowCoordinators::SlogansFlowCoordinator::Awake() {
    if (!PositioningViewController) {
        PositioningViewController = BeatSaberUI::CreateViewController<ViewControllers::PositioningViewController*>();
    }
    if (!TextMeshSettingsViewController) {
        TextMeshSettingsViewController = BeatSaberUI::CreateViewController<ViewControllers::TextMeshSettingsViewController*>();
    }
    if (!ExtraSettingsViewController) {
        ExtraSettingsViewController = BeatSaberUI::CreateViewController<ViewControllers::ExtraSettingsViewController*>();
    }
    if (!ColoringViewController) {
        ColoringViewController = BeatSaberUI::CreateViewController<ViewControllers::ColoringViewController*>();
    }
}

void Slogans::UI::FlowCoordinators::SlogansFlowCoordinator::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    SetTitle(il2cpp_utils::newcsstr("Slogans Settings"), HMUI::ViewController::AnimationType::In);
    showBackButton = true;
    ProvideInitialViewControllers(TextMeshSettingsViewController, PositioningViewController, ColoringViewController, ExtraSettingsViewController, nullptr);
}

void Slogans::UI::FlowCoordinators::SlogansFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
    getModConfig().config->Write();
    this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
}