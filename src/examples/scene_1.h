const std::shared_ptr<hittable> getScene1() {
    auto scene = std::make_shared<hittable_vector>();

    scene->add(std::make_shared<sphere>(/* center */ point3( 0, 1, 0 )    ,/* radius */ 1.0  /* material */));
    scene->add(std::make_shared<sphere>(/* center */ point3( -4, 1, 0 )   ,/* radius */ 1.0  /* material */));
    scene->add(std::make_shared<sphere>(/* center */ point3( 4, 1, 0 )    ,/* radius */ 1.0  /* material */));

    return scene;
}

color3matrix renderScene1(std::shared_ptr<hittable> scene) {
    camera cam;

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 1920;
    cam.samples_per_pixel   = 100;
    cam.max_depth           = 50;

    cam.vfov                = 90;

    cam.lookfrom            = point3(-4, 4, 3);
    cam.lookat              = point3(0, 0, -1);
    cam.vup                 = vec3(0, 1, 0);

    return cam.render(scene);
}
