#version 450 core

out vec4 fragColor;

in vec4 fragPos;

vec2 tileSize = vec2(1.f, 1.f);
vec2 gridSize = vec2(50.f, 50.f);
float lineWidth = 0.01f;

bool IsInXLine()
{
    float r = fragPos.x;
    
    if(r > 0)
        while(r - tileSize.x > 0) r -= tileSize.x;
    else
        while(r + tileSize.x < 0) r += tileSize.x;

    return abs(r) < lineWidth;
}

bool IsInYLine()
{
    float r = fragPos.z;

    if(r > 0)
        while(r - tileSize.y > 0) r -= tileSize.y;
    else
        while(r + tileSize.y < 0) r += tileSize.y;

    return abs(r) < lineWidth;
}

void main()
{
    fragColor = vec4(0.f, 0.f, 0.f, 0.f);

    bool x = IsInXLine();
    bool y = IsInYLine();
    if(x) fragColor += vec4(0.5f, 0.f, 0.f, 0.f);
    if(y) fragColor += vec4(0.f, 0.5f, 0.f, 0.f);
    if(x || y) fragColor += vec4(0.f, 0.f, 0.f, 1.f);
}