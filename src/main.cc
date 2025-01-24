#include <iostream>
#include <string>
#include <vector>

#include <png.h>
#include <stb.h>


int main() {
    std::cout << "[RayTracer v1.0.2]" << std::endl;

    create_png(StabImage(), StabOutput());

    return 0;
}
