#ifndef SIMPLEBUILDER_HPP
#define SIMPLEBUILDER_HPP

#include <SDL2TK/OpenGL/glew.h>
#include <SDL2TK/Vector4.hpp>
#include <SDL2TK/Vector3.hpp>
#include <vector>

class SimpleBuilder
{
    public:
        static const std::size_t FloatsPerVertex;

        SimpleBuilder();
        SimpleBuilder(SimpleBuilder&& other);
        ~SimpleBuilder();

        SimpleBuilder& operator=(SimpleBuilder&& other);

        void Add(const SDL2TK::Vector3F& position,
            const SDL2TK::Vector4F& color);

        void Reserve(int vertexCount);

        void BufferData(GLenum target, GLenum usage) const;

        GLsizei Count() const;

    protected:
    private:
        SimpleBuilder(const SimpleBuilder&) = delete;
        SimpleBuilder& operator=(const SimpleBuilder&) = delete;

        std::vector<GLfloat> _array;
};

#endif
