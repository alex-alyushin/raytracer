const std::shared_ptr<collection> getScene4() {
    auto scene = std::make_shared<collection>();

    auto material_ground = std::make_shared<lambertian>(color3(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(color3(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<dielectric>(1.00 / 1.33);
    auto material_right  = std::make_shared<metal>(color3(0.8, 0.6, 0.2), 0);

    scene->add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground, "ground"));
    scene->add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center, "center"));
    scene->add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left, "left"));
    scene->add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right, "right"));

    return scene;
}

color3matrix renderScene4(std::shared_ptr<collection> scene) {
    camera cam;

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 1800;
    cam.samples_per_pixel   = 50;
    cam.max_depth           = 50;
    cam.vfov                = 90;

    cam.lookfrom            = point3(-1.6, 0, 0.2);
    cam.lookat              = point3(0, 0, -1.2);
    cam.vup                 = vec3(0, 1, 0);

    return cam.render(scene);
}
