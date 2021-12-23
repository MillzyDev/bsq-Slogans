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
using namespace UnityEngine;

#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
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

DEFINE_TYPE(Slogans::UI::ViewControllers, SloganSelectionViewController);

void SloganSelectionViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;
    GameObject *container = CreateScrollableSettingsContainer(this->get_transform());
    StartCoroutine(reinterpret_cast<IEnumerator *>(CoroutineHelper::New(LoadSlogans(container->get_transform()))));
}

void SloganSelectionViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {

}

custom_types::Helpers::Coroutine SloganSelectionViewController::LoadSlogans(Transform *parent) {
    std::vector<SloganConfig *> configs = SloganConfig::LoadAllConfigs();

    for (SloganConfig *config : configs) {
        auto layout = CreateHorizontalLayoutGroup(parent);
        layout->set_spacing(3.0f);
        auto layoutTransform = config->info.layout->get_transform();
        layout->GetComponent<Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::createcsstr("round-rect-panel"), 0.5f);

        auto textLayout = CreateVerticalLayoutGroup(layoutTransform);

        auto nameText = CreateText(textLayout->get_transform(), config->text);
        auto color = config->color;
        nameText->set_color(Color(color.r, color.g, color.b, color.a));

        auto idText = CreateText(textLayout->get_transform(), config->id);

        co_yield nullptr;
    }
}
