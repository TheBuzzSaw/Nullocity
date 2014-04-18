#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include "SimpleBufferObject.hpp"
#include "Builders.hpp"
#include <map>

class ModelLoader
{
    public:
        static const std::string Cube;
        static const std::string Pyramid;
        static const std::string SquarePyramid;

        ModelLoader();
        ~ModelLoader() = default;

        ModelLoadFunction GetModelLoadFunction(std::string modelName) {return _models[modelName];}

    private:
        std::map<std::string,ModelLoadFunction> _models;


};
#endif
