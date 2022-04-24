#include "UI/ViewControllers/SloganSelectionViewController.hpp"
using namespace Slogans::UI::ViewControllers;

#include "Config/SlogansConfig.hpp"
using namespace Slogans::Config;

#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
using namespace QuestUI;

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI::BeatSaberUI;

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform_Axis.hpp"
using namespace UnityEngine;

#include "UnityEngine/Events/UnityAction.hpp"
using namespace UnityEngine::Events;

#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/Image.hpp"
using namespace UnityEngine::UI;

#include "GlobalNamespace/LevelBar.hpp"
using namespace GlobalNamespace;

#include "TMPro/TextMeshProUGUI.hpp"
using namespace TMPro;

#include "System/Collections/IEnumerator.hpp"
using namespace System::Collections;

#include <filesystem>
#include <string>
using namespace std;

#define MakeDelegate(DelegateType, varName) (il2cpp_utils::MakeDelegate<DelegateType>(classof(DelegateType), varName))

DEFINE_TYPE(Slogans::UI::ViewControllers, SloganSelectionViewController);

void SloganSelectionViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;
    GameObject *container = CreateScrollableSettingsContainer(this->get_transform());
    StartCoroutine(CoroutineHelper::New(LoadSlogans(container->get_transform())));
}

void SloganSelectionViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {

}

/*
 * TODO: Anchors for child alignment
 */
custom_types::Helpers::Coroutine SloganSelectionViewController::LoadSlogans(Transform *parent) {
    std::vector<SloganConfig *> configs = SloganConfig::LoadAllConfigs();

    for (SloganConfig *config : configs) {
        auto layout = CreateHorizontalLayoutGroup(parent);
        layout->set_padding(RectOffset::New_ctor(2, 2, 0, 0));
        layout->set_childForceExpandWidth(false);
        layout->GetComponent<LayoutElement *>()->set_minWidth(85.0f);
        auto layoutTransform = layout->get_transform();
        layout->GetComponent<Backgroundable *>()->ApplyBackgroundWithAlpha("round-rect-panel", 0.5f);

        auto textLayout = CreateVerticalLayoutGroup(layoutTransform);
        textLayout->set_childAlignment(TextAnchor::MiddleLeft);
        textLayout->set_spacing(0.2f);

        auto nameText = CreateText(textLayout->get_transform(), config->text);
        nameText->set_fontSize(5.0f);
        auto color = config->color;
        nameText->set_color(Color(color.r, color.g, color.b, color.a));

        auto idText = CreateText(textLayout->get_transform(), config->id);
        idText->set_fontSize(3.0f);

        auto selectButton = CreateUIButton(layout->get_transform(), "Select",
        [config]() {

        });

        co_yield nullptr;
    }
    co_return;
}
