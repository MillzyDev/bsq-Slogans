#pragma once

#include "main.hpp"
using namespace rapidjson;

#include <string>

#define SLOGAN_PATH_FORMAT "/sdcard/ModData/%s/Mods/Slogans/"

namespace Slogans::Config {
    class SloganConfig {
    public:

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

        Color color;
        Dimension position;
        Dimension rotation;
        std::string text = "deez nuts";
        float fontSize = 60.0f;
        // 0 Menu, 1 Song, 2+ Both
        int shownInScenes = 0;
        bool rainbow = false;
        bool pulse = false;
        bool bloom = false;

        SloganConfig();
        SloganConfig(Color color, Dimension position, Dimension rotation, std::string text, float fontSize, int shownInScenes, bool rainbow, bool pulse, bool bloom);
        explicit SloganConfig(Document document);

        void Save();
        static SloganConfig *Load(std::string id);

        inline static std::string slogansPath = string_format(SLOGAN_PATH_FORMAT, Modloader::getApplicationId().c_str());
    };
}