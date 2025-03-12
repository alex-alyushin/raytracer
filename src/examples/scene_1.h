const std::shared_ptr<collection> getScene1() {
    auto scene = std::make_shared<collection>();

    auto mtl = std::make_shared<metal>(
        color3(0.8, 0.8, 0.8),
        0
    );

    scene->add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, mtl, "0"));
    scene->add(std::make_shared<sphere>(point3(-2, 1, 0), 1.0, mtl, "1"));
    scene->add(std::make_shared<sphere>(point3(+0, 1, 0), 1.0, mtl, "2"));
    scene->add(std::make_shared<sphere>(point3(+2, 1, 0), 1.0, mtl, "3"));
    scene->add(std::make_shared<sphere>(point3(+4, 1, 0), 1.0, mtl, "4"));

    return scene;
}

color3matrix renderScene1(std::shared_ptr<collection> scene) {
    camera cam;

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 1800;
    cam.samples_per_pixel   = 1;
    cam.max_depth           = 50;
    cam.vfov                = 90;

    cam.lookfrom            = point3(-4, 4, 3);
    cam.lookat              = point3(0, 0, -1);
    cam.vup                 = vec3(0, 1, 0);

    return cam.render(scene);
}
