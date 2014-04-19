#include "ModelLoader.hpp"

const std::string ModelLoader::Sphere = "Sphere";
const std::string ModelLoader::Cube = "Cube";
const std::string ModelLoader::Pyramid = "Pyramid";
const std::string ModelLoader::SquarePyramid = "SquarePyramid";

ModelLoader::ModelLoader()
{
    _modelFunctions[Sphere] = BuildSphere;
    _modelFunctions[Cube] = BuildCube;
    _modelFunctions[Pyramid] = BuildPyramid;
    _modelFunctions[SquarePyramid] = BuildSquarePyramid;

    _default = new SimpleBufferObject(BuildSphere());
    _models[Sphere] = std::unique_ptr<SimpleBufferObject>(_default);
}

SimpleBufferObject& ModelLoader::GetModel(const std::string& modelName)
{
    SimpleBufferObject* result = _default;

    const auto modelFunctionIterator = _modelFunctions.find(modelName);

    if (modelFunctionIterator != _modelFunctions.cend())
    {
        auto modelIterator = _models.find(modelName);
        if (modelIterator == _models.cend())
        {
            result = new SimpleBufferObject(_modelFunctions[modelName]());
            _models[modelName] = std::unique_ptr<SimpleBufferObject>(result);
        }
    }

    return *result;
}
