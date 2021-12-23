#include "Config/SlogansConfig.hpp"
#include "Config/RandomString.hpp"
using namespace Slogans::Config;

#include "main.hpp"
using namespace rapidjson;

#include <utility>
#include <filesystem>
#include <algorithm>

/**
 * Used for creating new slogans ONLY!
 */
SloganConfig::SloganConfig() {
    std::vector<std::string> ids = GetAllIds();
    this->id = "";
    // do-while, will always at least run once
    // generating a random string and checking it doesnt exist with std::find, if there is a match: it loops again
    do {
        this->id = generateString(length);
    } while(std::find(ids.begin(), ids.end(), this->id) != ids.end());
}

SloganConfig::SloganConfig(Color color, Dimension position, Dimension rotation, std::string text, float fontSize,
    int shownInScenes, bool rainbow, bool pulse, bool bloom, bool wobble
) {
    this->color = color;
    this->position = position;
    this->rotation = rotation;
    this->text = text;
    this->fontSize = fontSize;
    this->shownInScenes = shownInScenes;
    this->rainbow = rainbow;
    this->pulse = pulse;
    this->bloom = bloom;
    this->wobble = wobble;
}

SloganConfig::SloganConfig(Document doc) {

    if (doc.HasMember("bloom") && doc["bloom"].IsBool())
        this->bloom = doc["bloom"].GetBool();

    if (doc.HasMember("pulse") && doc["pulse"].IsBool())
        this->pulse = doc["pulse"].GetBool();

    if (doc.HasMember("rainbow") && doc["rainbow"].IsBool())
        this->rainbow = doc["rainbow"].GetBool();

    if (doc.HasMember("wobble") && doc["wobble"].IsBool())
        this->rainbow = doc["wobble"].GetBool();

    if (doc.HasMember("shownInScenes") && doc["shownInScenes"].IsInt())
        this->shownInScenes = doc[shownInScenes].GetInt();

    if (doc.HasMember("fontSize") && doc["fontSize"].IsFloat())
        this->fontSize = doc["fontSize"].GetFloat();

    if (doc.HasMember("text") && doc["text"].IsString())
        this->text = doc["text"].GetString();

    if (doc.HasMember("position") && doc["position"].IsObject()) {
        Value o(kObjectType);

        if (o.HasMember("x") && o["x"].IsFloat())
            this->position.x = o["x"].GetFloat();

        if (o.HasMember("y") && o["y"].IsFloat())
            this->position.y = o["y"].GetFloat();

        if (o.HasMember("z") && o["z"].IsFloat())
            this->position.z = o["z"].GetFloat();
    }

    if (doc.HasMember("rotation") && doc["rotation"].IsObject()) {
        Value o(kObjectType);

        if (o.HasMember("x") && o["x"].IsFloat())
            this->rotation.x = o["x"].GetFloat();

        if (o.HasMember("y") && o["y"].IsFloat())
            this->rotation.y = o["y"].GetFloat();

        if (o.HasMember("z") && o["z"].IsFloat())
            this->rotation.z = o["z"].GetFloat();
    }

    if (doc.HasMember("color") && doc["color"].IsObject()) {
        Value o(kObjectType);

        if (o.HasMember("r") && o["r"].IsFloat())
            this->color.r = o["r"].GetFloat();

        if (o.HasMember("g") && o["g"].IsFloat())
            this->color.g = o["g"].GetFloat();

        if (o.HasMember("b") && o["b"].IsFloat())
            this->color.b = o["b"].GetFloat();

        if (o.HasMember("a") && o["a"].IsFloat())
            this->color.a = o["a"].GetFloat();
    }
}

SloganConfig *SloganConfig::Load(std::string id) {
    if (!direxists(slogansPath.c_str())) {
        int makePath = mkpath(slogansPath.c_str());
        if (makePath == -1) {
            getLogger().info("Failed to make mod data dir");
            return nullptr;
        }
    }

    std::string filePath = slogansPath + id +".json";
    std::string file = readfile(filePath);
    if (file.length() == 0) {
        getLogger().info("File %s is empty", filePath.c_str());
        return nullptr;
    }

    Document doc;
    doc.Parse(file);

    if (!doc.IsObject()) {
        getLogger().warning("Json file contents is not an object.");
        deletefile(filePath);
        getLogger().info("Deleting malformed file...");
        return nullptr;
    }

    SloganConfig *config = new SloganConfig(std::move(doc));
    config->id = id;
    return config;
}

void SloganConfig::Save() {
    Document doc;
    doc.SetObject();
    auto &all = doc.GetAllocator();

    doc.AddMember("bloom", this->bloom, all);
    doc.AddMember("pulse", this->pulse, all);
    doc.AddMember("rainbow", this->rainbow, all);
    doc.AddMember("wobble", this->wobble, all);
    doc.AddMember("shownInScenes", this->shownInScenes, all);
    doc.AddMember("fontSize", this->fontSize, all);
    doc.AddMember("text", this->text, all);

    Value pos(kObjectType);
    pos.AddMember("x", this->position.x, all);
    pos.AddMember("y", this->position.y, all);
    pos.AddMember("z", this->position.z, all);
    doc.AddMember("position", pos, all);

    Value rot(kObjectType);
    rot.AddMember("x", this->rotation.x, all);
    rot.AddMember("y", this->rotation.y, all);
    rot.AddMember("z", this->rotation.z, all);
    doc.AddMember("rotation", rot, all);

    Value col(kObjectType);
    col.AddMember("r", this->color.r, all);
    col.AddMember("g", this->color.g, all);
    col.AddMember("b", this->color.b, all);
    col.AddMember("a", this->color.a, all);
    doc.AddMember("color", col, all);


    if (!direxists(slogansPath.c_str())) {
        int makePath = mkpath(slogansPath.c_str());
        if (makePath == -1) {
            getLogger().info("Failed to make mod data dir");
            return;
        }
    }

    StringBuffer buffer;
    buffer.Clear();

    PrettyWriter<StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string json = std::string(buffer.GetString());
    getLogger().info("%s", json.c_str());
    writefile(string_format("%s/%s.json", slogansPath.c_str(), this->id.c_str()), json);
}

std::vector<std::string> SloganConfig::GetAllIds() {
    std::vector<std::string> ids = std::vector<std::string>();
    for (const auto &entry : std::filesystem::directory_iterator(slogansPath)) {
        std::string str = entry.path().filename().string();
        str.erase(str.end() - 5, str.end());
        ids.push_back(str);
    }
    return ids;
}

void SloganConfig::SaveAll(std::vector<SloganConfig *> configs) {
    for (SloganConfig *config : configs) {
        config->Save();
    }
}

std::vector<SloganConfig *> SloganConfig::LoadAllConfigs() {
    std::vector<SloganConfig *> configs = std::vector<SloganConfig *>();
    for (std::string id : GetAllIds()) {
        configs.push_back(Load(id));
    }
    return configs;
}
