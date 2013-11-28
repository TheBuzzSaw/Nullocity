#version 120

attribute vec3 position;
attribute vec4 color;
varying vec4 _color;

void main()
{
    _color = color;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
}

