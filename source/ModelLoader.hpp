#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include "SimpleBufferObject.hpp"
#include "Builders.hpp"
#include <unordered_map>

class ModelLoader
{
    public:
        static const std::string Cube;
        static const std::string Pyramid;
        static const std::string SquarePyramid;

        ModelLoader();
        ~ModelLoader() = default;

        ModelLoadFunction GetModelLoadFunction(std::string modelName);

    private:
        std::unordered_map<std::string,ModelLoadFunction> _models;


};
#endif
