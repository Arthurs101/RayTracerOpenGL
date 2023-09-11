#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aClr;

out vec3 color;
// Controls the scale of the vertices
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   color = aClr;
}