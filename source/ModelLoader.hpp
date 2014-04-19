#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include "SimpleBufferObject.hpp"
#include "Builders.hpp"
#include <unordered_map>
#include <memory>

class ModelLoader
{
    public:
        static const std::string Sphere;
        static const std::string Cube;
        static const std::string Pyramid;
        static const std::string SquarePyramid;

        ModelLoader();
        ~ModelLoader() = default;

        SimpleBufferObject& GetModel(const std::string& modelName);

    private:
        SimpleBufferObject* _default;
        std::unordered_map<std::string,ModelLoadFunction> _modelFunctions;
        std::unordered_map<std::string,std::unique_ptr<SimpleBufferObject>>
            _models;


};
#endif
