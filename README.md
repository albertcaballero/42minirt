# MiniRT
This project aims to create a simple Ray Tracer using the CPU.

## What it does
- Camera placement
- 5 basic objects: Plane, Sphere, Cylinder, Cone, Paraboloid
- Ambient light and point lights, both colored
- Anti-Aliasing

## How to use
The program reads .rt files that specify objects and lights properties and placements. There are many .rt examples in the ```scenes``` directory.
The program is compiled with ```make``` and executed via ```./minirt [scene.rt]```

To change the Antialiasing level, through ```inc/minirt.h``` SAMPLES macro.

The program uses the Minilibx graphic library (compiled with the program)

## Examples
![Colored Disks](https://github.com/user-attachments/assets/0a1e39ed-d3a5-4ca2-bd0e-2ba21dce7f97)
![Seamoon](https://github.com/user-attachments/assets/084c60f7-097e-4287-9038-c936ffa5d344)
