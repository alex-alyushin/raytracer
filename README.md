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
- [ ] release mode
