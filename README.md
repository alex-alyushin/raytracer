### Ray Tracer

This is a simple realization of a [ray tracing algorithm](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)).

### Install, Build and Run

The entire project is written in C++. Also there is Python for generating output PNG files. Check Python3 and pip3 versions.

```bash
$ python3 --version
Python 3.x.x

$ pip3 --version
pip 24.x.x ...
```

Ensure that dependencies are installed

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
- [x] Implement calculation of objects intersections
- [x] [ debug ] simple mode
- [x] [ debug ] in-depth mode
- [x] [ debug ] normales mode
- [ ] [ debug ] release mode

##### January 25, 2025

- [x] Camera: initialize all parameters
- [x] Implement ray-sphere intersection
- [x] Build mapping of a point in the scene to the viewport
- [x] Define alias `color3 = vec3` and create utilities for writing color to a matrix

##### January 26, 2025

- [ ] Find `OBJ` and `MTL` file in The Internet for demo
- [ ] Implement `class parser` with `std::ifstream&` interface for OBJ and MTL
- [x] Pass arguments to the executable binary file `argc argv`

##### January 31, 2025

- [x] In-Depth rendering
- [ ] Implement triangles

##### February 1, 2025

- [x] Calculate distance to intersection
- [x] Color in-depth `= 255 * exp(-dist)`
- [x] Color normales `= 255 * (rec.normal.x() + 1) / 2,`

##### February 2, 2025

- [ ] Reflection
- [ ] Refraction
- [ ] Metal *.mtl
- [ ] Filestream parse
- [ ] Run with GDB
- [ ] Log time benchmarks
