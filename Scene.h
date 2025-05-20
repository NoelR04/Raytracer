#pragma once

#include <vector>
#include "math.h"     // Vector Template
#include "geometry.h" // Sphere, Intersection_Context

template <typename FLOAT, size_t N>
struct Ray {
    Vector<FLOAT, N> origin;
    Vector<FLOAT, N> direction;

    Ray() = default;
    Ray(const Vector<FLOAT, N>& o, const Vector<FLOAT, N>& d) : origin(o), direction(d) {}
};

using Vector3f = Vector<float, 3>;
using Ray3f = Ray<float, 3>;

struct IntersectionRecord {
    const Sphere<float, 3>* object = nullptr;
    Intersection_Context<float, 3> context;
};

class Scene {
public:
    std::vector<Sphere<float, 3>> spheres;
    std::vector<Vector3f> light_positions; // punktförmige Lichtquellen (weiß)

    // Füge Kugel hinzu
    void add_sphere(const Sphere<float, 3>& sphere) {
        spheres.push_back(sphere);
    }

    // Füge Lichtquelle hinzu
    void add_light(const Vector3f& light_pos) {
        light_positions.push_back(light_pos);
    }

    // Findet das nächstgelegene sichtbare Objekt eines Rays
    IntersectionRecord find_nearest_intersection(const Ray3f& ray) const;

    // Lambertian-Shading für ein Objekt an Punkt p mit Normal n
    Vector3f lambertian_shading(const Vector3f& p, const Vector3f& n) const;

    // Raytracing Methode, mit max Rekursionstiefe
    Vector3f trace_ray(const Ray3f& ray, int depth = 0, int max_depth = 5) const;
};
