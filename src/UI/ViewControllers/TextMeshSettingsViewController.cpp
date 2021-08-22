#include "UI/ViewControllers/TextMeshSettingsViewController.hpp"
#include "Config/Config.hpp"
#include "main.hpp"
using namespace Slogans::UI;

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/UI/Button.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "HMUI/InputFieldView.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

DEFINE_TYPE(Slogans::UI::ViewControllers, TextMeshSettingsViewController);

UnityEngine::UI::VerticalLayoutGroup* textLayout;

QuestUI::IncrementSetting* textSize;

HMUI::InputFieldView* sloganText;

UnityEngine::UI::Button* capitalise;

void ViewControllers::TextMeshSettingsViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;
    auto* slogan = UnityEngine::GameObject::Find(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Slogan"))->GetComponent<TMPro::TextMeshProUGUI*>();

    textLayout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

    textSize = AddConfigValueIncrementFloat(textLayout->get_transform(), getModConfig().TextSize, 0, 1.0f, 0.0f, 200.0f);
    getModConfig().TextSize.AddChangeEvent([slogan](float value) {
        slogan->set_fontSize(value);
    });

    sloganText = AddConfigValueStringSetting(textLayout->get_transform(), getModConfig().TextContent);
    getModConfig().TextContent.AddChangeEvent([slogan](std::string value) {
        slogan->set_text(il2cpp_utils::newcsstr(value));
    });
}