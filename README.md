# exe-as-dll-loader
Library for loading an exe as a dll.

## Why this project?
 See the blog post below.
 * [Using a PyInstaller made Exe as a DLL](https://www.kannon.link/free/2017/10/18/using-a-pyinstaller-made-exe-as-a-dll/)

## Planned phases
 In a big picture, we are planning the follwing two phases.
 1. Make embedding Python (Numpy and Matplotlib) easier in C# (we are currently here)
 2. Make it distributable with Pyinstaller (yet to be done)

## References
 Listed below are the pages we learned to get ideas or tools for this project.
 1. Phase1
  * [pythonnet - Python for .NET](https://github.com/pythonnet/pythonnet)
 2. Phase2
  * [Load EXE as DLL: Mission Possible](https://www.codeproject.com/Articles/1045674/Load-EXE-as-DLL-Mission-Possible)
  * [Building the Bootloader](https://pyinstaller.readthedocs.io/en/stable/bootloader-building.html)
