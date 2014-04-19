#include "ModelLoader.hpp"

const std::string ModelLoader::Cube = "Cube";
const std::string ModelLoader::Pyramid = "Pyramid";
const std::string ModelLoader::SquarePyramid = "SquarePyramid";

ModelLoader::ModelLoader()
{
    _models[Cube] = BuildCube;
    _models[Pyramid] = BuildPyramid;
    _models[SquarePyramid] = BuildSquarePyramid;
}

ModelLoadFunction ModelLoader::GetModelLoadFunction(std::string modelName)
{
    ModelLoadFunction result = nullptr;

    const auto modelIterator = _models.find(modelName);

    if (modelIterator == _models.cend())
        result = modelIterator->second;

    return _models[modelName];
}
