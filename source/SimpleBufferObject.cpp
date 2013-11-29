#include "SimpleBufferObject.hpp"

static constexpr GLvoid* Offset(size_t offset)
{
    return (GLfloat*)0 + offset;
}

SimpleBufferObject::SimpleBufferObject()
    : _buffer(0)
    , _count(0)
{
}

SimpleBufferObject::SimpleBufferObject(const SimpleBuilder& builder)
    : _buffer(0)
    , _count(builder.Count())
{
    if (_count > 0)
    {
        glGenBuffers(1, &_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, _buffer);
        builder.BufferData(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
}

SimpleBufferObject::SimpleBufferObject(SimpleBufferObject&& other)
    : _buffer(other._buffer)
    , _count(other._count)
{
    other._buffer = 0;
    other._count = 0;
}

SimpleBufferObject::~SimpleBufferObject()
{
    glDeleteBuffers(1, &_buffer);
}

SimpleBufferObject& SimpleBufferObject::operator=(SimpleBufferObject&& other)
{
    if (this != &other)
    {
        glDeleteBuffers(1, &_buffer);
        _buffer = other._buffer;
        _count = other._count;
        other._buffer = 0;
        other._count = 0;
    }

    return *this;
}

void SimpleBufferObject::Draw(GLenum mode, GLint positionAttribute,
    GLint colorAttribute) const
{
    const GLsizei stride = sizeof(GLfloat) * SimpleBuilder::FloatsPerVertex;

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, stride,
        Offset(0));
    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, stride,
        Offset(3));

    glDrawArrays(mode, 0, _count);
}
