#version 450 core

out vec4 fragColor;

in vec4 fragPos;

vec2 tileSize = vec2(1.f, 1.f);
vec2 gridSize = vec2(50.f, 50.f);
float lineWidth = 0.02f;
vec4 xColor = vec4(0.6, 0.0, 0.0, 0.5);
vec4 yColor = vec4(0.0, 0.6, 0.0, 0.5);
vec4 xyColor = clamp(xColor + yColor, vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 0.5));
vec4 pColor = vec4(0.3, 0.3, 0.3, 0.5);

bool IsInXLine()
{
    float r = fragPos.z;

    return abs(r) < lineWidth; // Main axis are twice as thick
}

bool IsInYLine()
{
    float r = fragPos.x;

    return abs(r) < lineWidth; // Main axis are twice as thick
}

bool IsInXParallelLine()
{
    float r = mod(abs(fragPos.z) + lineWidth / 2.0, tileSize.y); // Positive

    return r < lineWidth;
}

bool IsInYParallelLine()
{
    float r = mod(abs(fragPos.x) + lineWidth / 2.0, tileSize.x); // Positive

    return r < lineWidth;
}

void main()
{
    bool x = IsInXLine();
    bool y = IsInYLine();

    if(x && y) fragColor = xyColor;
    else if(x) fragColor = xColor;
    else if(y) fragColor = yColor;
    else
    {
        bool xp = IsInXParallelLine();
        bool yp = IsInYParallelLine();

        if(xp || yp) fragColor = pColor;
        else fragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}