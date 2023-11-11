#include "Math/Math.h"

#include <stdexcept>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

Ray Math::RayUnderCursor(const glm::vec3& cameraPos, const glm::mat4& viewProjection, const glm::vec2& cursorPos, const glm::vec2& viewportSize)
{
    Ray out;
    out.origin = cameraPos;

    float mouseX = 2.f * cursorPos.x / viewportSize.x - 1.f;
    float mouseY = 2.f * cursorPos.y / viewportSize.y - 1.f;

    glm::mat4 invVP = glm::inverse(viewProjection);
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.f, 1.f);
    glm::vec4 worldPos = invVP * screenPos;

    out.direction = glm::normalize(glm::vec3(worldPos));

    return out;
}

HitResult Math::RayCastWithMesh(const Ray& ray, const Mesh& mesh)
{
    HitResult out;
    out.hasHit = false;

    const std::vector<Vertex>& vertices = mesh.getVertices();
    const std::vector<unsigned int>& indices = mesh.getIndices();

    for (size_t i = 0; i < indices.size(); i += 3)
    {
        unsigned int iA = indices[i], iB = indices[i+1], iC = indices[i+2];
        // Positions of points of triangle
        glm::vec3 A = { vertices[iA].position.x, vertices[iA].position.y, vertices[iA].position.z };
        glm::vec3 B = { vertices[iB].position.x, vertices[iB].position.y, vertices[iB].position.z };
        glm::vec3 C = { vertices[iC].position.x, vertices[iC].position.y, vertices[iC].position.z };

        glm::vec3 n = glm::cross(B - A, C - A);

        // Test with plane of triangle ABC
        float depth = glm::dot(n, A - ray.origin) / glm::dot(n, ray.direction);

        // If depth is negative : triangle is behind the ray
        // Even before checking if ray intersected the triangle, we can already check depths
        if(depth < 0 || (out.hasHit == true && out.depth < depth)) continue;

        // Test if point belongs to the triangle
        /** 
         * My way of doing it : 
         * We have a triangle ABC and a point P. We want to determine whether P belongs to triangle ABC.
         * If P is inside, it is easy to observe that AB x AP, BC x BP, and CA x CP (where 'x' denotes
         * the cross product) result in three collinear vectors, all pointing in the same direction.
         * However, if P is outside the triangle, one of these cross products will inevitably change
         * direction, while another will remain unchanged. The direction of the third cross product
         * will depend on the position of point P.
        */

        glm::vec3 P = ray.origin + depth * ray.direction; // P is the intersection point

        glm::vec3 cp1 = glm::cross(B-A, P-A);
        glm::vec3 cp2 = glm::cross(C-B, P-B);

        if(!AreVectorsOfSameDirection(cp1, cp2)) continue;

        glm::vec3 cp3 = glm::cross(A-C, P-C);

        if(!AreVectorsOfSameDirection(cp2, cp3)) continue;
        if(!AreVectorsOfSameDirection(cp3, cp1)) continue;

        // Ray intersected triangle.

        out.hasHit = true;
        out.depth = depth;
        out.normal = glm::normalize(n);
        out.position = P;
    }

    return out;
}

bool Math::AreVectorsOfSameDirection(const glm::vec3& u, const glm::vec3& v)
{
    return v.x / u.x > 0.f;
}

glm::mat4 Math::AlignVectors(const glm::vec3& from, const glm::vec3& to)
{
    float angle = glm::acos(glm::dot(from, to) / (glm::length(from) * glm::length(to)));

    glm::vec3 n = glm::cross(from, to);

    glm::mat4 mat = glm::rotate(glm::mat4(1.f), angle, n);

    return mat;
}