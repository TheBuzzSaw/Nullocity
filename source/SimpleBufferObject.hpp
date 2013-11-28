#ifndef SIMPLEBUFFEROBJECT_HPP
#define SIMPLEBUFFEROBJECT_HPP

#include "SimpleBuilder.hpp"

class SimpleBufferObject
{
    public:
        SimpleBufferObject();
        SimpleBufferObject(const SimpleBuilder& builder);
        SimpleBufferObject(SimpleBufferObject&& other);
        ~SimpleBufferObject();

        SimpleBufferObject& operator=(SimpleBufferObject&& other);

        void Draw(GLint positionAttribute, GLint colorAttribute) const;

    protected:
    private:
        SimpleBufferObject(const SimpleBufferObject&) = delete;
        SimpleBufferObject& operator=(const SimpleBufferObject&) = delete;

        GLuint _buffer;
        GLsizei _count;
};

#endif
