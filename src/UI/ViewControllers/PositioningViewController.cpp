#include "UI/ViewControllers/PositioningViewController.hpp"
#include "main.hpp"
#include "Config/Config.hpp"
using namespace Slogans::UI;

#include "config-utils/shared/config-utils.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

#include "UnityEngine/UI/VerticalLayoutGroup.hpp"

#include "HMUI/InputFieldView.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DEFINE_TYPE(Slogans::UI::ViewControllers, PositioningViewController);

UnityEngine::UI::VerticalLayoutGroup* posLayout;

void ViewControllers::PositioningViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;
    UnityEngine::GameObject* slogan = UnityEngine::GameObject::Find(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("SloganCanvas"));

    posLayout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

    AddConfigValueIncrementVector3(posLayout->get_transform(), getModConfig().TextPos, 1, 0.1f);
    getModConfig().TextPos.AddChangeEvent([slogan](UnityEngine::Vector3 value) {
        slogan->get_transform()->set_position(value);
    });

    AddConfigValueIncrementVector3(posLayout->get_transform(), getModConfig().TextRot, 0, 10.0f);
    getModConfig().TextRot.AddChangeEvent([slogan](UnityEngine::Vector3 value) {
        slogan->get_transform()->set_eulerAngles(value);
    });
}