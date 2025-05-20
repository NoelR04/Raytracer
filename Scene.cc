#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "geometry.h"

// Vorausgesetzt, Vector, Sphere, Ray, Intersection_Context sind definiert und implementiert wie bei dir.

template <typename FLOAT, size_t N>
class Scene {
public:
    std::vector<Sphere<FLOAT, N>> spheres;
    std::vector<Vector<FLOAT, N>> lights;  // Positionen der Lichtquellen (weiß)

    // Findet das nächste getroffene Objekt durch den Ray
    Sphere<FLOAT, N>* find_nearest_object(const Ray<FLOAT, N>& ray, FLOAT& out_t, Intersection_Context<FLOAT, N>& out_context) {
        Sphere<FLOAT, N>* nearest = nullptr;
        out_t = std::numeric_limits<FLOAT>::max();

        for (auto& sphere : spheres) {
            Intersection_Context<FLOAT, N> context;
            if (sphere.intersects(ray, context)) {
                if (context.t < out_t && context.t > 0) {
                    out_t = context.t;
                    out_context = context;
                    nearest = &sphere;
                }
            }
        }
        return nearest;
    }

    // Lambertian Shading: gibt die diffuse Helligkeit zurück (0..1)
    FLOAT lambertian_shading(const Vector<FLOAT, N>& normal, const Vector<FLOAT, N>& point) {
        FLOAT intensity = 0;
        for (const auto& light_pos : lights) {
            Vector<FLOAT, N> light_dir = light_pos - point;
            light_dir.normalize();
            FLOAT dot = normal * light_dir;
            if (dot > 0) {
                intensity += dot;
            }
        }
        if (!lights.empty())
            intensity /= static_cast<FLOAT>(lights.size());
        return intensity;
    }

    // Rekursives Raytracing mit max Tiefe, gibt die Farbe als Vector zurück (z.B. Grauwerte)
    Vector<FLOAT, N> trace_ray(const Ray<FLOAT, N>& ray, int depth = 0, int max_depth = 5) {
        if (depth > max_depth) {
            return Vector<FLOAT, N>{0}; // Schwarz, keine weitere Berechnung
        }

        FLOAT t;
        Intersection_Context<FLOAT, N> context;
        Sphere<FLOAT, N>* hit_sphere = find_nearest_object(ray, t, context);

        if (!hit_sphere) {
            return Vector<FLOAT, N>{0}; // Hintergrundfarbe schwarz
        }

        // Diffuse Beleuchtung mit Lambertian Shading
        FLOAT diff_intensity = lambertian_shading(context.normal, context.intersection);
        Vector<FLOAT, N> base_color = Vector<FLOAT, N>{diff_intensity};

        // Hier könntest du noch Reflexionen, Transparenz, etc. ergänzen

        return base_color;
    }
};
