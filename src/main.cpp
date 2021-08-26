#include "main.hpp"
#include "Components/RainbowText.hpp"
#include "Config/Config.hpp"
#include "UI/FlowCoordinators/SlogansFlowCoordinator.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "custom-types/shared/register.hpp"
#include "custom-types/shared/coroutine.hpp"

#include <cmath>

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "GlobalNamespace/CoreGameHUDController.hpp"

#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
using namespace QuestUI;

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Mathf.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static auto* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getModConfig().Init(info);
    getConfig().Reload();
    getConfig().Write();
    getLogger().info("Completed setup!");
}

UnityEngine::GameObject* canvas;
TMPro::TextMeshProUGUI* slogan;

void CreateSlogan() {
    if (UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("SloganCanvas"))) return;

    canvas = BeatSaberUI::CreateCanvas();
    canvas->set_name(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("SloganCanvas"));
    UnityEngine::Object::DontDestroyOnLoad(canvas);

    auto* transform = canvas->GetComponent<UnityEngine::RectTransform*>();
    transform->set_position(getModConfig().TextPos.GetValue());
    transform->set_eulerAngles(getModConfig().TextRot.GetValue());

    UnityEngine::UI::VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(transform);

    slogan = BeatSaberUI::CreateText(layout->get_transform(), getModConfig().TextContent.GetValue());
    slogan->get_gameObject()->set_name(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Temporary>("Slogan"));

    slogan->set_fontSize(getModConfig().TextSize.GetValue());
    slogan->set_color(getModConfig().TextColor.GetValue());

    if (getModConfig().IsRainbow.GetValue()) slogan->get_gameObject()->AddComponent<Slogans::Components::RainbowText*>();
}

MAKE_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate,
    void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling
)   {

    if (!UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("SloganCanvas"))) {
        CreateSlogan();
    }

    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(StandardLevelDetailViewController_DidActivate, &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
    void, GlobalNamespace::StandardLevelDetailViewController* self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling
) {
    if (!UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("SloganCanvas"))) {
        CreateSlogan();
    }

    StandardLevelDetailViewController_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);
}

MAKE_HOOK_MATCH(CoreGameHUDController_Start, &GlobalNamespace::CoreGameHUDController::Start,
    void, GlobalNamespace::CoreGameHUDController* self
) {
    auto* sloganCanvas = UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("SloganCanvas"));

    if (!getModConfig().IsInLevel.GetValue() && sloganCanvas) {
        UnityEngine::GameObject::Destroy(sloganCanvas);
    }

    CoreGameHUDController_Start(self);
}

 
// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    QuestUI::Init();

    getLogger().info("Installing hooks...");

    INSTALL_HOOK(getLogger(), MainFlowCoordinator_DidActivate);
    INSTALL_HOOK(getLogger(), StandardLevelDetailViewController_DidActivate);
    INSTALL_HOOK(getLogger(), CoreGameHUDController_Start);


    getLogger().info("Installed all hooks!");

    custom_types::Register::AutoRegister();

    QuestUI::Register::RegisterModSettingsFlowCoordinator<Slogans::UI::FlowCoordinators::SlogansFlowCoordinator*>(modInfo);
}