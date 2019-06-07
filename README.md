# RT

Final Computer Graphic branch project in UNIT Factory/42 School
This is a group six week project project

## Description

Ray tracing is a technique for rendering images by simulating the path of light through an image plane. 

The goal was to create a fully featured Raytracer with lot of functions, such as simple Graphic User Interface, 
texture mapping, reflective and tranctarent surfaces, using just pure C and SDL Framework for visualization.

![alt tag](https://github.com/vbespalk/RT_00/blob/master/media/gui/wlp.jpg)

More about project: [Subject](https://github.com/vbespalk/RT_00/blob/master/rt.en.pdf)

## Features

- JSON File Input
- Keyboard Input
- Live GUI
  - Moving / rotating camera / objects
  - Transforming objects
  - Modifying objects propetries
  - Texturing objects
  - Removing objects
  - Add / remove skybox
  - Negagtives
- Resizable GUI
- Objects
   - sphere
   - cone
   - plane
   - cylinder
   - paraboloid
   - cube
   - torus
   - disk
   - limited objects
   - composed elements
- Negative objects
- Lambertian Shading
- Direct, point, ambiant lightning
- Phong Shading
- Reflections
- Refractions
- Transparency
- Both transparent & specular blur
- Texturing all objects
- Color disruption
  - checkerboard
  - Perlin noise
  - marble material
  - light disruption
- Anti-aliasing
- Screenshots
- Color filtering: sepia, bw, inverse, negative

## Install & launch

```
https://github.com/vbespalk/RT_00.git ~/rt
cd ~/rt && make
./RT scenes/alternative.json
./RT scenes/my precious.json
```
```
For MacOS all frameworks available in repo
It is also possible to build on Linux, but you must have preinstalled following packages:
-SDL2 
-SDL2_image
```

## Commands & shortcuts

- Use GUI to interact with scene
- Left mouse button - select object / select cam (if any object isn't selected)
- Right mouse button - select cam
- Mouse wheel - scale (FOV is cam mode / radius in obj mode)
```
Shortcuts
```
- Arrows - rotate (XY coord)
- PgUp/PgDn - rotate (Z coord)
- WASD - up/left/down/right translation (XY coord)
- QE - forth/back translation (Z coord)
- ZX - scale (radius in obj mode, FOV in cam mode)
- RT - scale (height in obj mode, not for all objects)
- GHUI - color modes (greyscal / negative / sepia / inverted)
- 0 - 3 - select color / texture (if available) / checkerboard / default noise texturing for object
- 4 - 9 - select noise sample
- left / right Alt - change recursion depth (transparency,reflection, supersampling) 
- esc - quit

## GIF Exploring RT (low quality)
### Scenes modeling
![alt tag](https://github.com/vbespalk/RT_00/blob/master/media/gifs/cube.gif)
### Object modification: cylinder
![alt tag](https://github.com/vbespalk/RT_00/blob/master/media/gifs/cylinder.gif)
### Object modification: torus
![alt_tag](https://github.com/vbespalk/RT_00/blob/master/media/gifs/torus.gif)
### Interacting with objects
![alt tag](https://github.com/vbespalk/RT_00/blob/master/media/gifs/figures.gif)
### Transparency & refraction
![alt_tag](https://github.com/vbespalk/RT_00/blob/master/media/gifs/transparency.gif)
### Negative sphere
![alt_tag](https://github.com/vbespalk/RT_00/blob/master/media/gifs/negative_obj.gif)

## Authors
Project done with [Dmytro Omelchenko](https://github.com/AwesomeKPIPenguin) & [Maxim Dovhopoliy](https://github.com/mdovhopo)

If you want to contact me, you can send me a mail at vbespalk@student.unit.ua

![alt tag](https://github.com/vbespalk/RT_00/blob/master/screenshots/RT%20ScreenShot%20Fri%20May%2024%2010:39:39%202019.png)
