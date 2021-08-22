#include "UI/ViewControllers/ColoringViewController.hpp"
#include "Config/Config.hpp"
#include "main.hpp"
using namespace Slogans::UI;

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"
using namespace QuestUI;

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/UI/VerticalLayoutGroup.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DEFINE_TYPE(Slogans::UI::ViewControllers, ColoringViewController);

UnityEngine::UI::VerticalLayoutGroup* clrLayout;

QuestUI::IncrementSetting* alpha;

UnityEngine::GameObject* textColor;

void ViewControllers::ColoringViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
    if (!firstActivation) return;
    auto* slogan = UnityEngine::GameObject::Find(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Slogan"))->GetComponent<TMPro::TextMeshProUGUI*>();

    clrLayout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

    textColor = AddConfigValueColorPicker(clrLayout->get_transform(), getModConfig().TextColor);
    getModConfig().TextColor.AddChangeEvent([slogan](UnityEngine::Color value) {
        slogan->set_color(value);
    });

    alpha = BeatSaberUI::CreateIncrementSetting(clrLayout->get_transform(), "Opacity", 1, 0.1f, getModConfig().TextColor.GetValue().a, 0.0f, 1.0f, [slogan](float value) {
        UnityEngine::Color color = getModConfig().TextColor.GetValue();

        slogan->set_color(UnityEngine::Color(color.r, color.g, color.b, value));
        getModConfig().TextColor.SetValue(UnityEngine::Color(color.r, color.g, color.b, value));
    });


}