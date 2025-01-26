### Ray Tracer

This is a simple realization of a [ray tracing algorithm](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)).

### Install, Build and Run

The entire project is written in C++. Also there is Python for generating output PNG files. Ensure that Python3 and the required libraries are installed.

```bash
$ pip3 show pillow
$ pip3 show pybind11
$ pip3 show numpy
```

Install if not

```bash
$ pip3 install pillow
$ pip3 install pybind11
$ pip3 install numpy
```

##### Build

```bash
$ cmake -B build
$ cmake --build build --config Debug
$ cmake --build build --config Release
```

##### Run Renderer

```bash
$ ./build/rt arg1 arg2 arg3
```

### Working Plan

- [x] Build and run boilerplate
- [x] Connect Python interpreter
- [x] Use Pillow to create file output.png
- [x] Use Pillow to create a color gradient in a for loop
- [x] Implement primitives: vec3, ray, sphere
- [x] Implement camera positioning
- [ ] Implement calculation of objects intersections
- [ ] [ debug ] simple
- [ ] [ debug ] depth
- [ ] [ debug ] normal
- [ ] [ debug ] release

##### January 25, 2025

Upcoming plan for the ray tracer:

- [x] Camera: initialize all parameters
- [ ] Implement ray-sphere intersection
- [ ] Build mapping of a point in the scene to the viewport
- [x] Define alias `color3 = vec3` and create utilities for writing color to a matrix

##### January 26, 2025

Upcoming plan:

- [ ] Find `OBJ` and `MTL` file in The Internet for demo
- [ ] Implement `class parser` with `std::ifstream&` interface for OBJ and MTL
- [x] Pass arguments to the executable binary file `argc argv`
