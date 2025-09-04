### Ray Tracer

This is a simple realization of a [ray tracing algorithm](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)).

![pic-1](src/renders/metal-diffuse-metal-sky.png)

![pic-1](src/renders/metal-2-metal.png)

##### Build Renderer

```bash
$ cmake -B build
$ cmake --build build
```

##### Run Renderer

```bash
$ ./build/rt
```

### Todo

- [ ] implement defocus blur
- [ ] implement multithreading
- [ ] implement triangle mesh
- [ ] implement obj/mtl file reader
- [ ] implement texturing
- [ ] debug util: print all objects which intersect row path

