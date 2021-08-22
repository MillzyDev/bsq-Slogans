#include "UI/ViewControllers/ExtraSettingsViewController.hpp"
#include "Components/RainbowText.hpp"
#include "Config/Config.hpp"
#include "main.hpp"
using namespace Slogans::UI;
using namespace Slogans::Components;

#include "config-utils/shared/config-utils.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/Toggle.hpp"

#include "UnityEngine/GameObject.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DEFINE_TYPE(Slogans::UI::ViewControllers, ExtraSettingsViewController);

UnityEngine::UI::VerticalLayoutGroup* extLayout;

UnityEngine::UI::Toggle* isRainbow;

void ViewControllers::ExtraSettingsViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;
    auto* slogan = UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("Slogan"))->GetComponent<TMPro::TextMeshProUGUI*>();

    extLayout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

    isRainbow = AddConfigValueToggle(extLayout->get_transform(), getModConfig().IsRainbow);
    getModConfig().IsRainbow.AddChangeEvent([slogan](bool value) {
        if (value && !slogan->get_gameObject()->GetComponent<RainbowText*>()) {
            slogan->get_gameObject()->AddComponent<RainbowText*>();
        } else if (!value && slogan->get_gameObject()->GetComponent<RainbowText*>()) {
            UnityEngine::GameObject::Destroy(slogan->get_gameObject()->GetComponent<RainbowText*>());
            slogan->set_color(getModConfig().TextColor.GetValue());
        }
    });
}