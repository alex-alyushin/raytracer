### Ray Tracer

This is a simple realization of a [ray tracing algorithm](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)).

### Building and Running

##### Build

```bash
$ cmake -B build
$ cmake --build build --config Debug
$ cmake --build build --config Release
```

##### Run Renderer

```bash
$ ./build/myRayTracer
```

### Working Plan

- [x] Build and run boilerplate
- [x] Connect Python interpreter
- [x] Use Pillow to create file output.png
- [x] Use Pillow to create a color gradient in a for loop
- [x] Implement primitives: vec3, ray, sphere
- [ ] Implement calculation of objects intersections
- [ ] Implement camera positioning
- [ ] [ debug ] simple
- [ ] [ debug ] depth
- [ ] [ debug ] normal
- [ ] [ debug ] release

##### January 25, 2025

Upcoming plan for the ray tracer:

- Camera: initialize all parameters.
- Implement ray-sphere intersection.
- Build mapping of a point in the scene to the viewport.
- Define alias `color3 = vec3` and create utilities for writing color to a matrix.
