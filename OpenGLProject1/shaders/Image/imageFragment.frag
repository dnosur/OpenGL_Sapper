#version 330 core
out vec4 color;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 ourColor;

void main()
{
    // ��������� ����� �������� � ��������� �� �������� ����
    color = texture(ourTexture, TexCoord) * ourColor;
}
