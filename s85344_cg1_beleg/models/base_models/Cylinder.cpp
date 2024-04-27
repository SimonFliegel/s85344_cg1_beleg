#include <iostream>

#include "Cylinder.h"

// @see: http://www.songho.ca/opengl/gl_cylinder.html

std::vector<glm::vec3> Cylinder::getUnitCircleVertices() {
    float sectorStep = 2 * PI / RESOLUTION;
    float sectorAngle;

    std::vector<glm::vec3> unitCircleVertices;
    float x, y;
    float z = 0.0f; // z value is zero for all vertices on XY-plane

    for (int i = 0; i <= RESOLUTION; ++i)
    {
        sectorAngle = i * sectorStep;
        x = cos(sectorAngle); // x
        y = sin(sectorAngle); // y
        unitCircleVertices.push_back(glm::vec3(x, y, z));
    }
    return unitCircleVertices;
}

void Cylinder::createVertices() {
    // clear memory of prev arrays
    std::vector<Vertex>().swap(vertices);

    // get unit circle vectors on XY-plane
    std::vector<glm::vec3> unitVertices = getUnitCircleVertices();

    float x, y, z;
    float normalX, normalY, normalZ;
    float textureX, textureY;

    // put side vertices to arrays
    for (int i = 0; i < 2; ++i)
    {
        float h = -HEIGHT / 2.0f + i * HEIGHT;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        for (int j = 0; j <= RESOLUTION; ++j)
        {
            float ux = unitVertices[j].x;
            float uy = unitVertices[j].y;
            float uz = unitVertices[j].z;
            // position vector
            x = ux * RADIUS;
            y = uy * RADIUS;
            z = h;
            // normal vector
            normalX = ux;
            normalY = uy;
            normalZ = uz;
            // texture coordinate
            textureX = ((float)j / RESOLUTION);
            textureY = t;

            Vertex v;
            v.position = glm::vec3(x, y, z);
            v.normal = glm::vec3(normalX, normalY, normalZ);
            v.texCoord = glm::vec2(textureX, textureY);
            vertices.push_back(v);
        }
    }

    // the starting index for the base/top surface
    //NOTE: it is used for generating indices later
    baseCenterIndex = vertices.size();
    topCenterIndex = baseCenterIndex + RESOLUTION + 1; // include center vertex

    // put base and top vertices to arrays
    for (int i = 0; i < 2; ++i)
    {
        float h = -HEIGHT / 2.0f + i * HEIGHT;           // z value; -h/2 to h/2
        float nz = -1 + i * 2;                           // z value of normal; -1 to 1

        // center point
        Vertex v;
        v.position = glm::vec3(0, 0, h);
        v.normal = glm::vec3(0, 0, nz);
        v.texCoord = glm::vec2(0.5f, 0.5f);
        vertices.push_back(v);

        for (int j = 0; j < RESOLUTION; ++j)
        {
            float ux = unitVertices[j].x;
            float uy = unitVertices[j].y;
            // position vector
            x = ux * RADIUS;
            y = uy * RADIUS;
            z = h;
            // normal vector
            normalX = 0;
            normalY = 0;
            normalZ = nz;
            // texture coordinate
            textureX = (-ux * 0.5f + 0.5f);
            textureY = (-uy * 0.5f + 0.5f);

            v.position = glm::vec3(x, y, z);
            v.normal = glm::vec3(normalX, normalY, normalZ);
            v.texCoord = glm::vec2(textureX, textureY);
            vertices.push_back(v);
        }
    }
}

void Cylinder::createIndices(int topCenterIndex, int baseCenterIndex) {
    // generate CCW index list of cylinder triangles
    int k1 = 0;                         // 1st vertex index at base
    int k2 = RESOLUTION + 1;           // 1st vertex index at top

    // indices for the side surface
    for (int i = 0; i < RESOLUTION; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        indices.push_back(k1);
        indices.push_back(k1 + 1);
        indices.push_back(k2);

        // k2 => k1+1 => k2+1
        indices.push_back(k2);
        indices.push_back(k1 + 1);
        indices.push_back(k2 + 1);
    }

    // indices for the base surface
    //NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
    //      please see the previous code snippet
    for (int i = 0, k = baseCenterIndex + 1; i < RESOLUTION; ++i, ++k)
    {
        if (i < RESOLUTION - 1)
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else // last triangle
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(baseCenterIndex + 1);
            indices.push_back(k);
        }
    }

    // indices for the top surface
    for (int i = 0, k = topCenterIndex + 1; i < RESOLUTION; ++i, ++k)
    {
        if (i < RESOLUTION - 1)
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else // last triangle
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(topCenterIndex + 1);
        }
    }
}

void Cylinder::createShape() {
    createVertices();
    createIndices(topCenterIndex, baseCenterIndex); // has to be called after createVertices()
} 

Cylinder::Cylinder() {
	createShape();
}
