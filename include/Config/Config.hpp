#pragma once

#include "main.hpp"

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,
               CONFIG_VALUE(TextContent, std::string, "Content", "Slogans By Millzy");
               CONFIG_VALUE(TextSize, float, "Size", 60.0f);
               CONFIG_VALUE(TextPos, UnityEngine::Vector3, "Position", UnityEngine::Vector3(0.0f, 10.0f, 26.0f));
               CONFIG_VALUE(TextRot, UnityEngine::Vector3, "Rotation", UnityEngine::Vector3(0.0f, 0.0f, 0.0f));
               CONFIG_VALUE(IsRainbow, bool, "Rainbow Mode", false);
               CONFIG_VALUE(TextColor, UnityEngine::Color, "Color", UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f));

                       CONFIG_INIT_FUNCTION(
                               CONFIG_INIT_VALUE(TextContent);
                               CONFIG_INIT_VALUE(TextSize);
                               CONFIG_INIT_VALUE(TextPos);
                               CONFIG_INIT_VALUE(TextRot);
                               CONFIG_INIT_VALUE(IsRainbow);
                               CONFIG_INIT_VALUE(TextColor);
                               )
               )
