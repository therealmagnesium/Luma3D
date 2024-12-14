#pragma once
#include "Graphics/Model.h"

#include <unordered_map>

namespace Core
{
    class AssetManager
    {
    public:
        static Graphics::Model GetModel(const char* name);
        static void GetAllModelNames(const char** dest);
        static u32 GetModelCount();

        static void AddModel(const char* name, const char* path);
        static void ReplaceModel(const char* name, Graphics::Model& model);

        static void Clean();

    private:
        static std::unordered_map<std::string, Graphics::Model> s_models;
    };
}
