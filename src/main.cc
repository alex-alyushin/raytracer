#include <iostream>
#include <string>
#include <vector>

#include <png.h> // Python PNG Generator for C++ environment
#include <stb.h> // stab image for diagonal color gradient
#include <ray.h>

#include "vec3.h"
#include "material.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

int main() {
    std::cout << "[RayTracer v1.0.2]" << std::endl;

    create_png(StabImage(), StabOutput());

    return 0;
}
