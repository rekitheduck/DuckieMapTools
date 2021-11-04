#pragma once

#include <glm/vec3.hpp>
#include <string>
#include <utility>
#include <vector>

namespace MapTools {

    class Plane;
    class Polygon;

    class Brush
    {
    public:
        Brush();
        void pushPlane(Ref<Plane> plane);

        void createPolygons();

        std::pair<bool, glm::vec3> getIntersection(size_t plane1, size_t plane2, size_t plane3);

        bool isValid(); // A brush needs to be at least 4 planes to be considered valid (among other requirements)
        bool isVertexInPolygon(size_t polygon, const glm::vec3& vertex);
    private:
        std::vector<Ref<Plane>> m_planes;
        std::vector<Ref<Polygon>> m_polygons;
    };
}
