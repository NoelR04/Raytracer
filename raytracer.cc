#include "math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>
//added 
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
    int width, height;
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


int main(void) {
  // Bildschirm erstellen
  Screen screen(800, 600);
  std::vector<Object> cornellBox;

  // Große Kugeln als Wände, Boden, Decke
  Sphere<float, 3> floorSphere(Vector<float,3>({0.0f, -1000.0f, 0.0f}), 1000.0f);
  Sphere<float, 3> ceilingSphere(Vector<float,3>({0.0f, 1002.0f, 0.0f}), 1000.0f);
  Sphere<float, 3> leftWallSphere(Vector<float,3>({-1002.0f, 0.0f, 0.0f}), 1000.0f);
  Sphere<float, 3> rightWallSphere(Vector<float,3>({1002.0f, 0.0f, 0.0f}), 1000.0f);
  Sphere<float, 3> backWallSphere(Vector<float,3>({0.0f, 0.0f, -1002.0f}), 1000.0f);

  screen.setPixel(0, 0, 255, 0, 0); // Setze Pixel (0,0) auf rot
  screen.setPixel(1, 0, 0, 255, 0); // Setze Pixel (1,0) auf grün
  screen.setPixel(2, 0, 0, 0, 255); // Setze Pixel (2,0) auf blau


  // Beispiel Materialien
  Material red(
    Vector3df({1.0f, 0.0f, 0.0f}),  // ambient
    Vector3df({1.0f, 0.0f, 0.0f}),  // diffuse
    Vector3df({0.1f, 0.1f, 0.1f})   // reflective
  );
  
  Material green(
    Vector3df({0.0f, 1.0f, 0.0f}),  // ambient
    Vector3df({0.0f, 1.0f, 0.0f}),  // diffuse
    Vector3df({0.1f, 0.1f, 0.1f})   // reflective
  );
  
  Material white(
    Vector3df({1.0f, 1.0f, 1.0f}),  // ambient
    Vector3df({1.0f, 1.0f, 1.0f}),  // diffuse
    Vector3df({0.1f, 0.1f, 0.1f})   // reflective
  );
  
  Material blue(
    Vector3df({0.0f, 0.0f, 1.0f}),  // ambient
    Vector3df({0.0f, 0.0f, 1.0f}),  // diffuse
    Vector3df({0.1f, 0.1f, 0.1f})   // reflective
  );
  


  cornellBox.emplace_back(white, floorSphere);
  cornellBox.emplace_back(white, ceilingSphere);
  cornellBox.emplace_back(red, leftWallSphere);
  cornellBox.emplace_back(green, rightWallSphere);
  cornellBox.emplace_back(white, backWallSphere);

  Camera camera(
    Vector3df({0.0f, 1.0f, 5.0f}), // Position
    Vector3df({0.0f, 1.0f, 0.0f}), // Blickrichtung
    Vector3df({0.0f, 1.0f, 0.0f}), // Up-Vektor
    45.0f,                         // FOV
    screen.width, screen.height    // Auflösung
);

  // Kugeln in der Cornellbox
  cornellBox.emplace_back(red, Sphere<float, 3>(Vector<float, 3>({-2.0f, 1.0f, 0.0f}), 1.0f));  // Rote Kugel links
  cornellBox.emplace_back(blue, Sphere<float, 3>(Vector<float, 3>({0.0f, 1.0f, 0.0f}), 1.0f)); // Weiße Kugel in der Mitte
  cornellBox.emplace_back(green, Sphere<float, 3>(Vector<float, 3>({2.0f, 1.0f, 0.0f}), 1.0f)); // Grüne Kugel rechts
  // Kamera erstellen
  // Für jede Pixelkoordinate x,y
  //   Sehstrahl für x,y mit Kamera erzeugen
  //   Farbe mit raytracing-Methode bestimmen
  //   Beim Bildschirm die Farbe für Pixel x,y, setzten


  screen.saveAsPPM("output.ppm"); // Speichere das Bild als PPM-Datei
  return 0;
}   


