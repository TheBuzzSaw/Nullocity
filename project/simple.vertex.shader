#version 120

attribute vec4 vertex;
attribute vec4 color;
varying vec4 _color;

void main()
{
    _color = color;
    gl_Position = gl_ModelViewProjectionMatrix * vertex;
}
