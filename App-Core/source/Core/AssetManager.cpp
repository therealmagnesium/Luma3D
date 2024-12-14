#include "Core/AssetManager.h"
#include "Core/Log.h"

#include "Graphics/Model.h"

namespace Core
{
    static std::vector<std::string> modelNames;
    std::unordered_map<std::string, Graphics::Model> AssetManager::s_models;

    Graphics::Model AssetManager::GetModel(const char* name)
    {
        if (s_models.find(name) == s_models.end())
        {
            WARN("Failed to get model %s because it hasn't been added to the asset manager!", name);
            return (Graphics::Model){};
        }

        return s_models[name];
    }

    void AssetManager::GetAllModelNames(const char** dest)
    {
        u32 i = 0;
        for (auto& [name, model] : s_models)
        {
            dest[i] = name.c_str();
            i++;
        }
    }

    u32 AssetManager::GetModelCount()
    {
        return s_models.size();
    }

    void AssetManager::AddModel(const char* name, const char* path)
    {
        if (s_models.find(name) != s_models.end())
        {
            WARN("Cannot add model %s to asset manager because it has already been added!", name);
            return;
        }

        s_models[name] = Graphics::LoadModel(path);
        s_models[name].name = name;
    }

    void AssetManager::ReplaceModel(const char* name, Graphics::Model& model)
    {
        if (s_models.find(name) == s_models.end())
        {
            WARN("Cannot replace model %s from the asset manager because it can't be found!", name);
            return;
        }

        s_models[name] = model;
    }

    void AssetManager::Clean()
    {
        for (auto& [name, model] : s_models)
            Graphics::UnloadModel(model);

        s_models.clear();
    }
}
