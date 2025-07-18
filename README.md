# LabirinthOGL

LabyrinthOGL is a game in which the player finds himself in a labyrinth. Player's goal is to search a sphere in the labytinth. This game uses the OpenGL for rendering.

## Dependencies

The game uses these dependecies:

- [GLAD](https://glad.dav1d.de/)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [GoogleTest](https://github.com/google/googletest)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

## Build and compile

First, need to clone this project to your computer using `--recursive`:

```sh
$ git clone --recursive https://github.com/Suchimauzic/Diploma
```

Second, need to create a `build` folder and comile the project:

```sh
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DPROJECT_UNIT_TEST=False ..
$ make
```

## Launching the program

Program must be lauched from the `bin` folder. Otherwise, the program will not find shaders.