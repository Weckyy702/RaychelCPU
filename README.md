<h1>Raychel: A rendering engine based on the ray marching algorithm</h1>

What is ray marching?
-
In ray marching, every object is defined by a so called **signed distance function**, short SDF.
These functions return the distance to an objects surface, negative on the inside.
To trace a ray in a certain direction, we take the minimum of all the SDFs in the scene and move by that amount. That is repeated until we have hit an object.
Then we just apply the rendering equation to get the shaded color of that point.

Why render on the CPU?
-
I don't want to implement Compute Shaders. Wait for RaychelGPU

What are the features?
-
Raychel is still very much WIP and there are most certainly many many bugs left to squash.
  * Currently supported are:
    * Materials:
      <!-- * Diffuse
      * Reflective
      * Refractive
      * Emissive
      * Volumetric [WIP] -->
    
    * Lighting:
      <!-- * Lamp lighting [WIP]
      * Global illumination
      * Object lighting -->

     * Geometric bodies such as:
        * Spheres
        <!-- * Cubes
        * Any Body for which an SDF can be defined
        * *More primitives will follow soon!* -->
     
     * Rendering:
       * Freely moveable and rotatable Camera

    * Note:
      The older version of Raychel supported many more types of materials, but an engine rewrite comes at a great cost
      
General Information
-
RaychelCPU is written in standard C++17 using the C++ Guideline Suport Library  at https://github.com/Microsoft/GSL.
I try to keep all the code as standard and "C++17-ish" as possible.
I have not tested Compiler compatibility aside from clang and GCC, so please report any issues to me.

Library Credit
-
Credit where credit is due. I am using the following libraries:
* C++ Guideline Suport Library by Microsoft: https://github.com/Microsoft/GSL
* PNG++ is a modern wrapper around libPNG: https://github.com/mecwerks/png-plusplus
* libPNG is the official library to create PNG images: https://github.com/glennrp/libpng
* ncurses is an API allowing for GUI-like programs in the terminal https://github.com/mirror/ncurses ()

I found a bug!!!
-
Nicely done! Please report it in the issues tab or at weckyy702@gmail.com
