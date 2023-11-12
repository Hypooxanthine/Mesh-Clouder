#version 450 core

out vec4 fragColor;

in vec4 fragPos;

vec2 tileSize = vec2(1.f, 1.f);
vec2 gridSize = vec2(50.f, 50.f);
float lineWidth = 0.02f;
vec4 xColor = vec4(0.5, 0.0, 0.0, 0.5);
vec4 yColor = vec4(0.0, 0.5, 0.0, 0.5);
vec4 xyColor = clamp(xColor + yColor, vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 0.5));
vec4 pColor = vec4(0.2, 0.2, 0.2, 0.5);

bool IsInXLine()
{
    float r = fragPos.x;

    return abs(r) < lineWidth;
}

bool IsInYLine()
{
    float r = fragPos.z;

    return abs(r) < lineWidth;
}

bool IsInXParallelLine()
{
    float r = fragPos.x;
    
    if(r > 0)
        while(r - tileSize.x > 0) r -= tileSize.x;
    else
        while(r + tileSize.x < 0) r += tileSize.x;

    return abs(r) < lineWidth;
}

bool IsInYParallelLine()
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
    bool x = IsInXLine();
    bool y = IsInYLine();
    bool xp = IsInXParallelLine();
    bool yp = IsInYParallelLine();

    if(x && y) fragColor = xyColor;
    else if(x) fragColor = xColor;
    else if(y) fragColor = yColor;
    else if(xp || yp) fragColor = pColor;
    else fragColor = vec4(0.0, 0.0, 0.0, 0.0);
}