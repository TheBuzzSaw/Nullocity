#include "ModelLoader.hpp"

const std::string ModelLoader::Sphere = "Sphere";
const std::string ModelLoader::Cube = "Cube";
const std::string ModelLoader::Pyramid = "Pyramid";
const std::string ModelLoader::SquarePyramid = "SquarePyramid";
const std::string ModelLoader::Icosahedron = "Icosahedron";

ModelLoader::ModelLoader()
{
    _modelFunctions[Sphere] = BuildSphere;
    _modelFunctions[Cube] = BuildCube;
    _modelFunctions[Pyramid] = BuildPyramid;
    _modelFunctions[SquarePyramid] = BuildSquarePyramid;
    _modelFunctions[Icosahedron] = BuildIcosahedron;

    _default = new SimpleBufferObject(BuildSphere());
    _models[Sphere] = std::unique_ptr<SimpleBufferObject>(_default);
}

SimpleBufferObject& ModelLoader::GetModel(const std::string& modelName)
{
    SimpleBufferObject* result = _default;

    auto i = _models.find(modelName);
    if (i == _models.end())
    {
        auto j = _modelFunctions.find(modelName);
        if (j != _modelFunctions.end())
        {
            auto modelFunction = j->second;
            result = new SimpleBufferObject((*modelFunction)());
            _models[modelName] = std::unique_ptr<SimpleBufferObject>(result);
        }
    }
    else
    {
        result = i->second.get();
    }

    return *result;
}
