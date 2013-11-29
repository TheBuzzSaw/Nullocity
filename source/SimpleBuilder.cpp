#include "SimpleBuilder.hpp"

const std::size_t SimpleBuilder::FloatsPerVertex = 7;

SimpleBuilder::SimpleBuilder()
{
}

SimpleBuilder::SimpleBuilder(SimpleBuilder&& other)
    : _array(std::move(other._array))
{
}

SimpleBuilder::~SimpleBuilder()
{
}

SimpleBuilder& SimpleBuilder::operator=(SimpleBuilder&& other)
{
    if (this != &other)
    {
        _array = std::move(other._array);
    }

    return *this;
}

void SimpleBuilder::Add(const SDL2TK::Vector3F& position,
    const SDL2TK::Vector4F& color)
{
    _array.push_back(position.X());
    _array.push_back(position.Y());
    _array.push_back(position.Z());

    _array.push_back(color.X());
    _array.push_back(color.Y());
    _array.push_back(color.Z());
    _array.push_back(color.W());
}

void SimpleBuilder::Reserve(int vertexCount)
{
    if (vertexCount > 0)
        _array.reserve(vertexCount * FloatsPerVertex);
}

void SimpleBuilder::Clear()
{
    _array.clear();
}

void SimpleBuilder::BufferData(GLenum target, GLenum usage) const
{
    glBufferData(target, _array.size() * sizeof(GLfloat), _array.data(), usage);
}

GLsizei SimpleBuilder::Count() const
{
    return _array.size() / FloatsPerVertex;
}
