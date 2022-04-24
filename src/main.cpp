#include "main.hpp"

#include "custom-types/shared/register.hpp"
using namespace custom_types;

#include "questui/shared/QuestUI.hpp"

#include "SlogansHooks.hpp"
using namespace Slogans;

#include "Config/SlogansConfig.hpp"
using namespace Slogans::Config;

#include "UI/ViewControllers/SloganSelectionViewController.hpp"
using namespace Slogans::UI::ViewControllers;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    if (SloganConfig::LoadAllConfigs().empty()) {
        auto config = new SloganConfig();
        config->Save();
    }


    getLogger().info("Registering types...");
    Register::AutoRegister();
    getLogger().info("Installed types...");

    QuestUI::Register::RegisterModSettingsViewController<SloganSelectionViewController *>(modInfo);

    getLogger().info("Installing Slogans hooks...");
    Hooks::InstallHooks(getLogger());
    getLogger().info("Installed Slogans hooks!");
}