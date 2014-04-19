#include "ModelLoader.hpp"

const std::string ModelLoader::Cube = "Cube";
const std::string ModelLoader::Pyramid = "Pyramid";
const std::string ModelLoader::SquarePyramid = "SquarePyramid";

ModelLoader::ModelLoader()
{
    _modelFunctions[Cube] = BuildCube;
    _modelFunctions[Pyramid] = BuildPyramid;
    _modelFunctions[SquarePyramid] = BuildSquarePyramid;
}

SimpleBufferObject& ModelLoader::GetModel(std::string modelName)
{
    ModelLoadFunction result = nullptr;

    const auto modelFunctionIterator = _modelFunctions.find(modelName);

    if (modelFunctionIterator != _modelFunctions.cend())
    {
        auto modelIterator = _models.find(modelName);
        if (modelIterator == _models.cend())
        {
            _models[modelName] = new SimpleBufferObject(_modelFunctions[modelName]());
        }
        result = modelFunctionIterator->second;
    }

    return *_models[modelName];
}
