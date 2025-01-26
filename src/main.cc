#include <iostream>
#include <string>
#include <vector>

#include <png.h> // Python PNG Generator for C++ environment
#include <stb.h> // stab image for diagonal color gradient
#include <ray.h>

#include "vec3.h"
#include "color.h"
#include "material.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

int main(int argc, char* argv[]) {
    for (int index = 0; index < argc; ++index) {
        std::cout << "Argument " << index << ": " << argv[index] << std::endl;
    }

    std::cout << "[RayTracer v1.0.3] running..." << std::endl;

    // Just for PNG generator testing, see import stb.h
    create_png(StabImage(), StabOutput());

    return 0;
}
