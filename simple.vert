#version 430
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 translateMatrix;
uniform mat4 rotateMatrix;
uniform mat4 scaleMatrix;
uniform mat4 reflectMatrix;
out vec3 outColor;

void main() {
   gl_Position = translateMatrix * rotateMatrix * scaleMatrix * reflectMatrix *  vec4(position, 1.0);
   outColor = color;
}
