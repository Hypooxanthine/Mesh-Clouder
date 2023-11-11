#pragma once

#include "Data/Mesh.h"

class MeshGenerator
{
public:
    static Mesh GenCircle(unsigned int samples);
    static Mesh GenQuad();
};