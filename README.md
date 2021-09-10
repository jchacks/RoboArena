# RoboArena

A RoboCode inspired battle simulation written in C++, with python bindings written in Cython.

## Getting Started

We use `premake5` to build the project and related projects.

### Linux

To generate the `Makefile`s run:

```bash
premake5 gmake
```

Next run:

```bash
make
```

### Windows

Windows usage has not been tested.  In theory premake should be able to generate VS project files.
To generate a VS project file run:

```bash
premake5 vs2017
```

## Features

* Separated `Engine` class with no UI for fast simulations (AI/RL etc)

## Todo

* RoboCode like API
* Separate the UI nicely
  * Maybe complie RoboArena as SharedLib and link into UI
