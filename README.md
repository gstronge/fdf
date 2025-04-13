# fdf

**fdf** is a project from the 42 curriculum that introduces you to basic graphics programming by rendering 3D wireframe models using a 2D isometric projection. The project uses the MiniLibX library to open a window, draw the model, and handle user interactions.

---

## Project Overview

The program reads a map of coordinates from a `.fdf` file, where each number represents a point’s altitude. It then draws a 3D wireframe landscape using an isometric projection, connecting points with lines to simulate depth and elevation.

This project is an introduction to computer graphics, coordinate transformation, and event-driven programming.


## Rules and Constraints

- The **MiniLibX** graphical library must be used.
- Input is a single `.fdf` file containing a grid of integers.
- Each point has an `(x, y, z)` coordinate where `z` is the altitude.
- The program must open a graphical window and render the wireframe in **isometric projection**.
- ESC key or window close button must exit the program cleanly.
- The map file is assumed to be correctly formatted — no advanced error parsing is required.
- No global variables allowed.


## Window & Controls

- Opens a window with the rendered 3D wireframe.
- **ESC** key: exits the program.
- Clicking the **close (X)** button on the window exits the program.
- Window must handle minimizing, switching, and redrawing smoothly.


## Concepts & Learning Goals

- Understanding how to represent and project 3D data in 2D space
- Using **MiniLibX** to create graphical applications
- Implementing isometric projection
- Drawing with algorithms like Bresenham’s line algorithm
- Reading and parsing structured input files
- Writing clean, modular, and memory-safe C code

## .fdf File Format

- Each .fdf file contains a grid of integers.
- The column index represents the x coordinate.
- The row index represents the y coordinate.
- Each integer represents the z coordinate (altitude).

Example .fdf file:

```
0 0 0 0 0
0 0 10 0 0
0 10 20 10 0
0 0 10 0 0
0 0 0 0 0
```

## Compilation

To compile and run the project:

```bash
$ make
$ ./fdf <map_file.fdf>
```


