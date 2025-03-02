const std::shared_ptr<hittable> getScene() {
    auto scene = std::make_shared<hittable_vector>();

    auto lambert = std::make_shared<lambertian>(
        color3(0.4, 0.2, 0.1)
    );

    scene->add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, lambert));
    scene->add(std::make_shared<sphere>(point3(-2, 1, 0), 1.0, lambert));
    scene->add(std::make_shared<sphere>(point3(+0, 1, 0), 1.0, lambert));
    scene->add(std::make_shared<sphere>(point3(+2, 1, 0), 1.0, lambert));
    scene->add(std::make_shared<sphere>(point3(+4, 1, 0), 1.0, lambert));

    return scene;
}

color3matrix renderScene(std::shared_ptr<hittable> scene) {
    camera cam;

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 1920;

    // = 100 for release
    cam.samples_per_pixel   = 5;

    cam.max_depth           = 50;

    cam.vfov                = 90;

    cam.lookfrom            = point3(-4, 4, 3);
    cam.lookat              = point3(0, 0, -1);
    cam.vup                 = vec3(0, 1, 0);

    return cam.render(scene);
}
