#include "ModelLoader.hpp"

const std::string ModelLoader::Cube = "Cube";
const std::string ModelLoader::Pyramid = "Pyramid";
const std::string ModelLoader::SquarePyramid = "SquarePyramid";

ModelLoader::ModelLoader()
{
    _modelFunctions[Cube] = BuildCube;
    _modelFunctions[Pyramid] = BuildPyramid;
    _modelFunctions[SquarePyramid] = BuildSquarePyramid;

    std::string defaultModelName = Cube;
    SimpleBufferObject* defaultModel = new SimpleBufferObject(_modelFunctions[defaultModelName]());
    _models[defaultModelName] = std::unique_ptr<SimpleBufferObject>(defaultModel);
}

SimpleBufferObject& ModelLoader::GetModel(std::string modelName)
{
    SimpleBufferObject* result = new SimpleBufferObject(_modelFunctions[Cube]());

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
