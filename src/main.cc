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
#include "hittable_vector.h"
#include "sphere.h"
#include "camera.h"

const std::shared_ptr<hittable> getScene() {
    auto scene = std::make_shared<hittable_vector>();

    scene->add(std::make_shared<sphere>(/* center */ point3( 0, 1, 0 )    ,/* radius */ 1.0  /* material */));
    scene->add(std::make_shared<sphere>(/* center */ point3( -4, 1, 0 )   ,/* radius */ 1.0  /* material */));
    scene->add(std::make_shared<sphere>(/* center */ point3( 4, 1, 0 )    ,/* radius */ 1.0  /* material */));

    return scene;
}

color3matrix renderScene(std::shared_ptr<hittable> scene) {
    camera cam;

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 1920;
    cam.samples_per_pixel   = 100;
    cam.max_depth           = 50;

    cam.vfov                = 90;

    cam.lookfrom            = point3(-4, 4, 3);
    cam.lookat              = point3(0, 0, -1);
    cam.vup                 = vec3(0, 1, 0);

    return cam.render(*scene);
}

int main(int argc, char* argv[]) {
    for (int index = 0; index < argc; ++index) {
        std::cout << "Argument " << index << ": " << argv[index] << std::endl;
    }

    std::cout << "[RayTracer v1.1.0] running..." << std::endl;

    // step 1: generate any .png file to test Python binding
    // create_png(StabImage(), StabOutput());

    // step 2: render black-and-white simple scene
    auto matrix = renderScene(getScene());
    create_png(matrix, "simple.png");

    // step next...

    return 0;
}
