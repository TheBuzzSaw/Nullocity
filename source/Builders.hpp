#ifndef BUILDERS_HPP
#define BUILDERS_HPP

#include "SimpleBufferObject.hpp"

typedef SimpleBufferObject (*ModelLoadFunction)();

SimpleBufferObject BuildCube();
SimpleBufferObject BuildPyramid();
SimpleBufferObject BuildSquarePyramid();
SimpleBufferObject BuildLines();
SimpleBufferObject BuildSphere();

#endif
