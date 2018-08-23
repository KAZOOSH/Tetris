#version 120


varying vec2 texCoordVarying;

void main()
{
    gl_Position = ftransform();
}