#include "Components/RainbowText.hpp"
#include "main.hpp"
using namespace Slogans::Components;

DEFINE_TYPE(Slogans::Components, RainbowText);

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Time.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

void RainbowText::Start() {
    text = GetComponent<TMPro::TextMeshProUGUI*>();
}

void RainbowText::Update() {
    if (text == nullptr) return;
    text->set_color(UnityEngine::Color::HSVToRGB(std::fmod(UnityEngine::Time::get_time() * 0.35f, 1), 1, 1));
}