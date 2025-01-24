Building and Running
--------------------

$ cmake -B build
$ cmake --build build --config Debug
$ cmake --build build --config Release

$ ./build/myRayTracer

[WIP] Working Plan
------------------

[*] Build and run boilerplate
[*] Connect Python interpreter
[*] Use Pillow to create file output.png
[*]  Use Pillow to create a color gradient in a for loop
[]  Implement primitives: vec3, ray, triangle, sphere
[]  Implement calculation of objects intersections
[]  Implement camera positioning
[]  Raytracer: debug
[]  Raytracer: normals
[]  Raytracer: release
