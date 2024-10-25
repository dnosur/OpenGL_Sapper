#version 330 core
out vec4 color;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 ourColor;

void main()
{
    // Получение цвета текстуры и умножение на заданный цвет
    color = texture(ourTexture, TexCoord) * ourColor;
}
