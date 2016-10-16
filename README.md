# cmake_project
CMake project template for cross-platform building, testing and packaging


## Features to Come
- Packaging
- Example Building
- Extended Project Macros
- Cross-plattform Workarounds
- Library setup for applications/examples
- Non-Commandline application setup

## Folder Structure

```
README.md
CMakeLists.txt
```
```
- cmake
	ProjectMacros.cmake
    CMakeLists.txt
```

```
- include
	+ Lib1Headers
	- Lib2Headers
		lib2header.h
```
```
- src
	CMakeLists.txt
    + Lib1
    + Lib2
```
Project Source
- packed in libraries

```
- applications
	CMakeLists.txt
    - app1
    	CMakeLists.txt
        app1source.cpp
```
Applications (main executables)

```
+ examples
```

```
- build
	- bin
	- src
	- lib
	- applications
	- examples
```
Build output

- bin:
- src:
- lib:
- applications:
- examples:

## Generators

### Microsoft Visual Studio


Cmake generates a Visual Studio Solution and Project file.

The solution contains at least three projects:

    ALL_BUILD
    YourProject
    ZERO_CHECK

The solution is set up so that when you build your project (by build solution, or build project) "YourProject" will be built and then ZERO_CHECK will be built, causing cmake to run and check if anything has changed. If anything has changed, the solution and project file will be regenerated and Visual Studio will ask if you would like to reload.

The compilation of your program is done by Visual Studio, as it would if you set it up manually, but Visual Studio will run cmake, and thus check if anything has changed, and the project files should be regenerated.



## Output Paths: Best Practices

## Libraries


- **Static library**: linked directly into final executable. Functions are contained in it and there is no need to have the library into the system where the executable will be deployed
- **Shared library**: linked but not embedded in the final executable. Loaded at runtime and need to be present in the system where the executable is deployed

**Linux**
- **Static library** `.a`
- **Shared library** `.so`

**Windows**

- **Static library** `.lib`: may contain code or just links to a ddl. Either way it's compiled code that you link with your program. The static library is included in your .exe at link time.
- **Dynamic Link Library** `.dll`: like a shared library(.so) on linux but there are some differences:
	- **DLL**: can define external (for dll and external modules) and internal (dll only) functions. Custom functions upon load/unload
	- **SO**: all functions externally available (besides hidden symbols)


### Installation

```cmake
# include header files
include_directories( ... )
# Specify the paths in which the linker should search for libraries to link to the executable
# find_package(...) determines absolute paths to libraries
target_link_libraries(...)
```

**Linux**
install the libraries systemwide:
- libraries under `/usr/local/lib`
- headers under `/usr/local/include`

**Windows**

The OS will use the following algorithm to locate the required DLL's:
1. The directories listed in the Application-specific Path registry key
2. **The directory where the executable module for the current process is located**
3. The current directory
4. The Windows system directory
5. The Windows directory
6. The directories listed in the PATH environment variable

Thus you have two reasonable options if you don't want to clutter the OS directories with your app-specific dll:

1. Put your DLL in the same folder as your EXE
2. Create an app-specific Path registry entry
3. Modify the PATH variable



