#version 430
in vec3 outColor;
out vec4 fragColor;
uniform vec3 ambientColor;
void main() {
   fragColor = vec4(outColor,1.0f);
    fragColor = vec4(outColor * ambientColor, 1.0f); // Ambiyans ışığını uygula
}

