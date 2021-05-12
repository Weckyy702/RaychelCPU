<h1>Raychel: A rendering engine based on the ray marching algorithm</h1>

What is ray marching?
-
In ray marching, every object is defined by a so called **signed distance function**, short SDF.
These functions return the distance to an objects surface, negative on the inside.
To trace a ray in a certain direction, just take the minimum of all the SDFs in the scene and move by that amount. That is repeated until you have hit an object.
Then just apply the rendering equation to get the shaded color of that point.

Features
-
Raychel is still very much WIP and there are most certainly many many bugs left to squash.
  * Currently supported are:
    * Materials:
      *coming soon™*
      <!-- * Diffuse
      * Reflective
      * Refractive
      * Emissive
      * Volumetric [WIP] -->
    
    * Lighting:
      *coming soon™*
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
Compilers that work for sure:
  * Clang
  * GCC
  * MSVC

How to build
-
Cmake 3.14 or later is required and the libraries marked with *required* in the list below need to be installed manually.

  * Windows
    -
    You will need CMake, Visual Studio with the C++ environment and ZLib.
    For installing Zlib, I recommend zlib.install at https://github.com/horta/zlib.install

    Run cmake, open the resulting RaychelCPU.sln in Visual Studio, right click RaychelCPU_test and click "build"

    If you would like to use ASAN, you need to enable it in the Project properties
    
  * GNU/Linux
    -
    Run cmake, then run make and you have your binaries built in the *bin* directory
    
    If any of the dependencies is not installed, it is likely easiest to just install them via your package manager


Library Credit
-
Credit where credit is due. I am using the following libraries:
* Microsofts Implementation of the C++ Core Guideline Support Library: 
  https://github.com/Microsoft/GSL
* PNG++ is a modern wrapper around libPNG: 
  https://github.com/mecwerks/png-plusplus
* libPNG is the official library to create PNG images: 
  https://github.com/glennrp/libpng  
* zlib is a general purpose data compression library: 
  https://github.com/madler/zlib  *required*
* ncurses is an API allowing for GUI-like programs in the terminal
  https://github.com/mirror/ncurses *optional*

I found a bug!!!
-
Nicely done! Please report it in the Issues tab or at weckyy702@gmail.com
