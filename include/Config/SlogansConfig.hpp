#pragma once

#include "main.hpp"
using namespace rapidjson;

#include <string>

#include "UnityEngine/Transform.hpp"
using namespace UnityEngine;

#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
using namespace UnityEngine::UI;

#include "fmt/fmt/include/fmt/core.h"

#define SLOGAN_PATH_FORMAT "/sdcard/ModData/%s/Mods/Slogans/"

namespace Slogans::Config {
    class SloganConfig {
    public:
        struct Info {
            Transform* layoutTransform;
            HorizontalLayoutGroup *layout;
        };

        struct Color {
            float r = 1.0f;
            float g = 1.0f;
            float b = 1.0f;
            float a = 1.0f;
        };

        struct Dimension {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        };

        std::string id;
        Info info;

        Color color;
        Dimension position = {0.0f, 10.0f, 26.0f};
        Dimension rotation = {0.0f, 10.0f, 26.0f};
        std::string text = "deez nuts";
        float fontSize = 60.0f;
        // 0 Menu, 1 Song, 2+ Both
        int shownInScenes = 0;
        bool rainbow = false;
        bool pulse = false;
        bool bloom = false;
        bool wobble = false;

        SloganConfig();
        SloganConfig(Color color, Dimension position, Dimension rotation, std::string text, float fontSize, int shownInScenes, bool rainbow, bool pulse, bool bloom, bool wobble);
        explicit SloganConfig(Document document);

        void Save();
        static void SaveAll(std::vector<SloganConfig *> configs);
        static SloganConfig *Load(std::string id);
        static std::vector<SloganConfig *> LoadAllConfigs();

        static std::vector<std::string> GetAllIds();

        inline static std::string slogansPath = fmt::format(SLOGAN_PATH_FORMAT, Modloader::getApplicationId());
    };
}