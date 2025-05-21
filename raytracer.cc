#include "math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

// Die folgenden Kommentare beschreiben Datenstrukturen und Funktionen
// Die Datenstrukturen und Funktionen die weiter hinten im Text beschrieben sind,
// hängen höchstens von den vorhergehenden Datenstrukturen ab, aber nicht umgekehrt.


// Ein "Bildschirm", der das Setzen eines Pixels kapselt
// Der Bildschirm hat eine Auflösung (Breite x Höhe)
// Kann zur Ausgabe einer PPM-Datei verwendet werden oder
// mit SDL2 implementiert werden.
class Screen {
  public:
    int width, height;
    Screen(int width, int height) : width(width), height(height) {
      pixels.resize(width * height, {0, 0, 0});
    }
    void setPixel(int x, int y, int r,  int g, int b) {
      if (x < 0 || x >= width || y < 0 || y >= height) return; // Out of bounds check
      pixels[y * width + x] = {r, g, b};
  }
    void saveAsPPM(const std::string& filename) {
      std::ofstream file(filename);
      if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
      }
      file << "P3\n" << width << " " << height << "\n255\n";
      for (const auto& pixel : pixels) {
        file << pixel.r << " " << pixel.g << " " << pixel.b << "\n";
      }
      file.close();
      std::cout << "Image saved as " << filename << "\n";
    }

  private:
    struct Pixel {
      int r, g, b;
    };
    std::vector<Pixel> pixels;
  };


// Eine "Kamera", die von einem Augenpunkt aus in eine Richtung senkrecht auf ein Rechteck (das Bild) zeigt.
// Für das Rechteck muss die Auflösung oder alternativ die Pixelbreite und -höhe bekannt sein.
// Für ein Pixel mit Bildkoordinate kann ein Sehstrahl erzeugt werden.
class Camera {
  public:
    Camera(Vector3df position, Vector3df look_at, Vector3df up_vector, float fov_deg, int image_width, int image_height)
      : pos(position), forward(look_at-position),right(forward.cross_product(up_vector)),up(right.cross_product(forward)), width(image_width), height(image_height) 
    {
        forward.normalize();
        right.normalize();
        up.normalize();
  
        float aspect = float(width) / float(height);
        float fov_rad = fov_deg * M_PI / 180.0f;
        scale = std::tan(fov_rad * 0.5f);
  
        aspect_ratio = aspect;
    }
  
    Ray3df generateRay(int x, int y) const {
        float ndc_x = (x + 0.5f) / float(width);
        float ndc_y = (y + 0.5f) / float(height);
        float screen_x = (2 * ndc_x - 1) * aspect_ratio * scale;
        float screen_y = (1 - 2 * ndc_y) * scale;
  
        Vector3df direction = forward + screen_x * right + screen_y * up;
        direction.normalize();
  
        return Ray3df{pos, direction};
    }
  
  private:
    Vector3df pos, forward, right, up;
    int width, height;
    float scale, aspect_ratio;
  };
  

// Für die "Farbe" benötigt man nicht unbedingt eine eigene Datenstruktur.
// Sie kann als Vector3df implementiert werden mit Farbanteil von 0 bis 1.
// Vor Setzen eines Pixels auf eine bestimmte Farbe (z.B. 8-Bit-Farbtiefe),
// kann der Farbanteil mit 255 multipliziert  und der Nachkommaanteil verworfen werden.

struct Color {
  float r, g, b;
  Color(float r, float g, float b) : r(r), g(g), b(b) {}

  int to8Bit(float value) const {
      return static_cast<int>(std::clamp(value * 255.0f, 0.0f, 255.0f));
  }
  void to8BitColor(int& red, int& green, int& blue) const {
      red = to8Bit(r);
      green = to8Bit(g);
      blue = to8Bit(b);
  }
};

// Das "Material" der Objektoberfläche mit ambienten, diffusem und reflektiven Farbanteil.
struct Material {
  Vector3df ambient;
  Vector3df diffuse;
  Vector3df reflective;
  Material(Vector3df ambient, Vector3df diffuse, Vector3df reflective)
    : ambient(ambient), diffuse(diffuse), reflective(reflective) {}
};


// Ein "Objekt", z.B. eine Kugel oder ein Dreieck, und dem zugehörigen Material der Oberfläche.
// Im Prinzip ein Wrapper-Objekt, das mindestens Material und geometrisches Objekt zusammenfasst.
// Kugel und Dreieck finden Sie in geometry.h/tcc

class Object {
  public:
      Object(const Material& material, const Sphere<float, 3>& sphere)
          : material(material), sphere(sphere) {}
  
      // Prüft Ray-Sphere-Intersection und gibt t & Normal zurück
      bool intersect(const Ray3df& ray, float& t, Vector3df& normal) const {
          Intersection_Context<float, 3> ctx;
          if (sphere.intersects(ray, ctx)) {
              t = ctx.t;
              normal = ctx.normal;
              return true;
          }
          return false;
      }
  
      // Getter fürs Material
      const Material& getMaterial() const { return material; }
  
  private:
      Material material;
      Sphere<float, 3> sphere;
  };
// verschiedene Materialdefinition, z.B. Mattes Schwarz, Mattes Rot, Reflektierendes Weiss, ...
// im wesentlichen Variablen, die mit Konstruktoraufrufen initialisiert werden.
struct Materials {
  static Material mattSchwarz() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.0f, 0.0f, 0.0f})); 
  }
  static Material mattRot() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.8f, 0.1f, 0.1f}), Vector3df({0.0f, 0.0f, 0.0f})); 
  }
  static Material mattGruen() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.1f, 0.8f, 0.1f}), Vector3df({0.0f, 0.0f, 0.0f})); 
  }
  static Material mattBlau() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.1f, 0.1f, 0.8f}), Vector3df({0.0f, 0.0f, 0.0f})); 
  }
  static Material mattWeiss() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.8f, 0.8f, 0.8f}), Vector3df({0.0f, 0.0f, 0.0f})); 
  }
  static Material reflektierendesSchwarz() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.8f, 0.8f, 0.8f})); 
  }
  static Material reflektierendesWeiss() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.8f, 0.8f, 0.8f}), Vector3df({0.8f, 0.8f, 0.8f})); 
  }
  static Material reflektierendesRot() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.8f, 0.1f, 0.1f}), Vector3df({0.8f, 0.8f, 0.8f})); 
  }
  static Material reflektierendesGruen() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.1f, 0.8f, 0.1f}), Vector3df({0.8f, 0.8f, 0.8f})); 
  }
  static Material reflektierendesBlau() {
     return Material(Vector3df({0.1f, 0.1f, 0.1f}), Vector3df({0.1f, 0.1f, 0.8f}), Vector3df({0.8f, 0.8f, 0.8f})); 
  }
};

// Die folgenden Werte zur konkreten Objekten, Lichtquellen und Funktionen, wie Lambertian-Shading
// oder die Suche nach einem Sehstrahl für das dem Augenpunkt am nächsten liegenden Objekte,
// können auch zusammen in eine Datenstruktur für die gesammte zu
// rendernde "Szene" zusammengefasst werden.

// Die Cornelbox aufgebaut aus den Objekten
// Am besten verwendet man hier einen std::vector< ... > von Objekten.

// Punktförmige "Lichtquellen" können einfach als Vector3df implementiert werden mit weisser Farbe,
// bei farbigen Lichtquellen müssen die entsprechenden Daten in Objekt zusammengefaßt werden
// Bei mehreren Lichtquellen können diese in einen std::vector gespeichert werden.

// Sie benötigen eine Implementierung von Lambertian-Shading, z.B. als Funktion
// Benötigte Werte können als Parameter übergeben werden, oder wenn diese Funktion eine Objektmethode eines
// Szene-Objekts ist, dann kann auf die Werte teilweise direkt zugegriffen werden.
// Bei mehreren Lichtquellen muss der resultierende diffuse Farbanteil durch die Anzahl Lichtquellen geteilt werden.

// Für einen Sehstrahl aus allen Objekte, dasjenige finden, das dem Augenpunkt am nächsten liegt.
// Am besten einen Zeiger auf das Objekt zurückgeben. Wenn dieser nullptr ist, dann gibt es kein sichtbares Objekt.

// Die rekursive raytracing-Methode. Am besten ab einer bestimmten Rekursionstiefe (z.B. als Parameter übergeben) abbrechen.


// ... Deine Includes und Klassendefinitionen bleiben unverändert ...

// Rekursive Raytracing-Funktion
Color trace(const Ray3df& ray,
  const std::vector<Object>& scene,
  const Vector3df& lightPos,
  int depth = 2)
{
static int debugCounter = 0;
if (depth == 0)
return Color(0, 0, 0); // Schwarz bei maximaler Rekursionstiefe

float minDist = std::numeric_limits<float>::max();
const Object* hitObject = nullptr;
Vector3df hitPoint({0.0f, 0.0f, 0.0f});
Vector3df hitNormal({0.0f, 0.0f, 0.0f});

// Schnittpunkt mit Szene suchen
for (const auto& object : scene) {
float t;
Vector3df normal({0.0f, 0.0f, 0.0f});
if (object.intersect(ray, t, normal)) {
  if (t < minDist && t > 0.001f) {
      minDist = t;
      hitObject = &object;
      hitNormal = normal;
      hitPoint = ray.origin + t * ray.direction;
  }
}
}

if (!hitObject)
return Color(0, 0, 0); // Kein Treffer → Hintergrund

// --- Schattenstrahl ---
Vector3df toLight = lightPos - hitPoint;
float lightDist = toLight.length();
toLight.normalize();

constexpr float shadow_epsilon = 0.001f;
Ray3df shadowRay(hitPoint + shadow_epsilon * hitNormal, toLight);
bool inShadow = false;
for (const auto& object : scene) {
    if (&object == hitObject) continue; // Self-shadowing verhindern!
    float tShadow;
    Vector3df nShadow({0.0f, 0.0f, 0.0f});
    if (object.intersect(shadowRay, tShadow, nShadow)) {
        if (tShadow > shadow_epsilon && tShadow < lightDist) {
            inShadow = true;
            if (debugCounter < 50) {
                std::cout << "Shadow ray hit object at t=" << tShadow << ", lightDist=" << lightDist << std::endl;
                debugCounter++;
            
            break;
        }
    }
}


// --- Farb-/Lichtberechnung ---
const Material& mat = hitObject->getMaterial();
Vector3df color = mat.ambient; // Ambient immer

if (!inShadow) {
float diff = std::max(0.0f, hitNormal * toLight); // Skalarprodukt
color = color + diff * mat.diffuse;
// Optional: Hier könntest du auch einen Specular-Anteil ergänzen
}

// --- Reflexion ---
if (depth > 1 &&
  (mat.reflective[0] > 0.01f || mat.reflective[1] > 0.01f || mat.reflective[2] > 0.01f)) {
  Vector3df reflDir = ray.direction - 2.0f * (ray.direction * hitNormal) * hitNormal;
  reflDir.normalize();
  Ray3df reflectRay(hitPoint + 0.001f * hitNormal, reflDir);
  Color reflected = trace(reflectRay, scene, lightPos, depth - 1);

  // Erzeuge einen Vektor aus der reflektierten Farbe (nutze geschweifte Klammern!)
  Vector3df reflColor{reflected.r, reflected.g, reflected.b};
  Vector3df temp = Vector3df({1.0f, 1.0f, 1.0f}) - mat.reflective;

  // Mischung pro Komponente ("manuell")
  for (int i = 0; i < 3; ++i) {
      color[i] = temp[i] * color[i] + mat.reflective[i] * reflColor[i];
  }
}

// Clamp auf [0,1]
for (int i = 0; i < 3; ++i)
  color[i] = std::clamp(color[i], 0.0f, 1.0f);
return Color(color[0], color[1], color[2]);
} }

int main(void) {
// --- Szeneaufbau ---
Screen screen(800, 600);
std::vector<Object> cornellBox;

// Wände (Kugeln als Box)
Sphere<float, 3> ceilingSphere(Vector<float,3>({0.0f, -1000.0f, 0.0f}), 1000.0f);
Sphere<float, 3> floorSphere(Vector<float,3>({0.0f, 1002.0f, 0.0f}), 1000.0f);
Sphere<float, 3> leftWallSphere(Vector<float,3>({-1002.0f, 0.0f, 0.0f}), 1000.0f);
Sphere<float, 3> rightWallSphere(Vector<float,3>({1002.0f, 0.0f, 0.0f}), 1000.0f);
Sphere<float, 3> backWallSphere(Vector<float,3>({0.0f, 0.0f, -1002.0f}), 1000.0f);

// Materialien
Material red(
Vector3df({0.2f, 0.0f, 0.0f}),
Vector3df({0.8f, 0.2f, 0.2f}),
Vector3df({0.0f, 0.0f, 0.0f})
);

Material green(
Vector3df({0.0f, 0.2f, 0.0f}),
Vector3df({0.2f, 0.8f, 0.2f}),
Vector3df({0.0f, 0.0f, 0.0f})
);

Material white(
Vector3df({0.2f, 0.2f, 0.2f}),
Vector3df({0.8f, 0.8f, 0.8f}),
Vector3df({0.0f, 0.0f, 0.0f})
);

Material blue(
Vector3df({0.0f, 0.0f, 0.2f}),
Vector3df({0.2f, 0.2f, 0.8f}),
Vector3df({0.0f, 0.0f, 0.0f})
);

Material mirror(
Vector3df({0.0f, 0.0f, 0.0f}),
Vector3df({0.0f, 0.0f, 0.0f}),
Vector3df({0.9f, 0.9f, 0.9f})
);

// Box zusammensetzen
cornellBox.emplace_back(white, floorSphere);
cornellBox.emplace_back(white, ceilingSphere);
cornellBox.emplace_back(red, leftWallSphere);
cornellBox.emplace_back(green, rightWallSphere);
cornellBox.emplace_back(white, backWallSphere);

// Kleine Kugeln (vor Raytracing-Schleife!)
cornellBox.emplace_back(mirror, Sphere<float, 3>(Vector<float, 3>({-1.0f, 1.0f, 0.0f}), 0.3f));  // Spiegelkugel links
cornellBox.emplace_back(blue,   Sphere<float, 3>(Vector<float, 3>({ 0.5f, 0.4f, -1.0f}), 0.3f));  // Blaukugel Mitte
cornellBox.emplace_back(green,  Sphere<float, 3>(Vector<float, 3>({ 1.0f, 1.5f, 1.5f}), 0.3f));  // Grünkugel rechts

// Kamera
Camera camera(
Vector3df({0.0f, 1.0f, 5.0f}), // Position
Vector3df({0.0f, 1.0f, 0.0f}), // Blickrichtung (nach -z)
Vector3df({0.0f, 1.0f, 0.0f}), // Up-Vektor
45.0f,
screen.width, screen.height
);

// Lichtquelle
Vector3df lightPos({0.0f, 0.05f, 2.0f});

// --- Raytracing ---
for (int y = 0; y < screen.height; ++y) {
  for (int x = 0; x < screen.width; ++x) {
    Ray3df ray = camera.generateRay(x, y);
    Color pixelColor = trace(ray, cornellBox, lightPos, 2);

    int r, g, b;
    pixelColor.to8BitColor(r, g, b);
    screen.setPixel(x, y, r, g, b);
  }
}

screen.saveAsPPM("output.ppm");
return 0;
}