# Vulkan 3D Engine in C++ / Visual Studio 2022

This is a simple 3D engine using Vulkan API in C++ and Visual Studio 2022 on Windows. It is based on the Vulkan Tutorial by Brendan Galea: <https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR>.

There will be additional projects and after I progress further.

So far we have the hello triangle equivalent in Vulkan with GLFW and Vulkan SDK.

![Nokota Mustang 3](./screenshots/vulkan_1.PNG)

I have added some instructions to setup the project in Visual Studio 2022 on Windows; in addition I have some custom configuration tips and a batch script for compiling the shaders.

## VS2022 Project Setup Instructions for Vulkan and GLFW

Since Brendan doesn't focus on VS2022 or Windows I needed to setup my system first. Here is a step by step guide to setup the project.

1.  Download and install Visual Studio 2022 for <https://visualstudio.microsoft.com>. Install the following workloads: Desktop development with C++.

2.  In individual components check for the following:

    -   C++ CMake tools for Windows
    -   MSBuild
    -   MSVC v144 - VS 2022 C++ x64/x86 build tools (Latest)

3.  Create a new project in Visual Studio 2022 using c++ and Windows Desktop Wizard.

    -   Name the project.
    -   Select the project folder where you want to access it easily.
    -   I use the checkbox **Place solution and project in the same directory**.
    -   Click Create.
    -   Set the Application Type to C++ Console Application.
    -   Select the "Empty Project" Application Type,

4.  Create a new folder in your project folder called `external`, where we will store third party libraries.

5.  Download and prepare the following libraries:

    -   Vulkan SDK: <https://vulkan.lunarg.com/sdk/home>
        -   Install the Vulkan SDK.
        -   In start menu look for VulkanCube and run it to check if Vulkan is installed correctly.
        -   Browse to installation directory and copy the `Include` and `Lib` folders to a subfolder such as `external/vulkan`.
    -   GLFW: <https://www.glfw.org/download.html>
        -   Download the Windows pre-compiled binaries for 64-bit.
        -   Extract the files and copy the `include` and `lib-vc2022` folders to `external/glfw`.
    -   glm: <https://github.com/g-truc/glm/releases>
        -   Download the latest release.
        -   Copy the entire `glm` folder to `external`.

6.  The external files directory should look like this:

        external/
        ├── glfw/
        │   ├── include/
        │   │   └── GLFW/
        │   │           └glfw3.h ... etc
        │   └── lib-vc2022/
        │               └glfw3.lib ... etc
        ├── glm/
        │   └── common.hpp ... etc
        └── vulkan/
            ├── Include/
            │       └── vulkan/ ... glm/ ... sdl2/ ... etc
            └── Lib/
                └── vulkan-1.lib ... etc

7.  In Visual Studio, right click on the project and select `Properties`, where we can setup the linker.

    -   In Configuration select `All Configurations`.
    -   In Platform select `All Platforms`.
    -   In **_Configuration Properties > General_** check

        -   _Platform Toolset_ is set to `Visual Studio 2022 (v143)`
        -   _C++ standard_ is set to `ISO C++20 Standard (/std:c++17)`.

    -   In **_C/C++ > General_** add the following to the **_Additional Include Directories_**:

        -   `$(ProjectDir)external\vulkan\Include`
        -   `$(ProjectDir)external\glfw\include`
        -   `$(ProjectDir)external\glm`

    -   In **_Linker > General_** add the following to the **_Additional Library Directories_**:

        -   `$(ProjectDir)external\vulkan\Lib`
        -   `$(ProjectDir)external\glfw\lib-vc2022`

    -   In **_Linker > Input_** add the following to the **_Additional Dependencies_**:

        -   `vulkan-1.lib`
        -   `glfw3.lib`

8.  Building a simple test program:

    -   Create a new file `main.cpp` in the project folder.
    -   Add the following code:

        ```cpp
        #define GLFW_INCLUDE_VULKAN
        #include <GLFW/glfw3.h>

        #define GLM_FORCE_RADIANS
        #define GLM_FORCE_DEPTH_ZERO_TO_ONE
        #include <glm/vec4.hpp>
        #include <glm/mat4x4.hpp>

        #include <iostream>

        void testVulcan() {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            std::cout << extensionCount << " extensions supported\n";
            glm::mat4 matrix;
            glm::vec4 vec;
            auto test = matrix * vec;
            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
            }
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        int main() {
            try {
                testVulcan();
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
        ```

    -   In the Solution Configuration Manager, set the Active solution configuration to `Debug` and the Active solution platform to `x64`.
    -   Click Local Windows Debugger to build and run the program, where you should see a window with the title "Vulkan window".

    -   If you see a warning in the build output: **LNK4098: defaultlib MSVCRT conflicts with use of other libs**; then add this to the **_Linker > Command Line > Additional Options_** : `/NODEFAULTLIB:MSVCRT` but only for the Debug configuration and not for the Release configuration (or all configurations).

9.  Optional step, I changed the structure of the build output to separate the build files from the source files.

    -   In **Configuration Properties > General** change the **Output Directory** to:
        `$(SolutionDir)build\$(Configuration)\$(Platform)\`
    -   In **Configuration Properties > General** change the **Intermediate Directory** to:
        `$(SolutionDir)intermediate\$(Configuration)\$(Platform)\`

    This will create a build folder in the solution directory where all build files are stored, and an intermediate folder where all temporary files are stored.

## Additional support for GLSL Shader Programs

We can use some tools to help write GLSL and compile them to SPIR-V automatically.

1.  Install GLSL language support with this extension: <https://github.com/danielscherzer/GLSL/releases> and restart Visual Studio.

2.  Create a `shaders` folder in the project directory and add a simple fragment shader `simple.frag`:

    ```glsl
    #version 460
    #extension GL_KHR_vulkan_glsl : enable

    layout(location = 0) out vec4 outColor;

    void main() {
        outColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
    ```

    -   In the Solution Explorer, right click the Resource Files and select `Add > Existing Item...` and add the `frag.spv` file.

3.  Create a file called `shaders/shader_compile.bat` and add it to the resource files. Open this file and enter the batch code:

    ```bat
    @echo off

    REM Look for any .vert .geom or .frag file and compile them to SPIR-V
    for /R %%f in (*.vert *.geom *.frag) do (
        echo %%f
        C:/VulkanSDK/1.3.290.0/Bin/glslc.exe %%f -o %%f.spv
    )

    pause
    ```

    Make sure to change the source of the `/Bin/glslc.exe` to the path of your Vulkan SDK installation.

    If you run this batch file, it will compile all `.vert`, `.geom`, and `.frag` files to `.spv` files. Try this by running the script in a console and verify that the `simple.frag.spv` file is created.

    The flag `#extension GL_KHR_vulkan_glsl : enable` will configure the GLSL language support we installed in step 1 to lint correctly with Vulkan features, but will produce warnings in the glslc compiler which can be ignored. Pick your poison here.

4.  I added this to **_Build Events > Post-Build Event > Command Line_** in the project properties:

    ```bat
    cd $(ProjectDir)shaders\
    call shader_compile.bat
    ```

    Note that it will only run on a rebuild and not on a build if nothing has changed in your source files, but it is handy for automatic compiling of the shader programs.

## Example Engine Projects

These source folders are VS2022 solutions with the following projects that I have been working on:

1. Vulkan3DEngineHelloWorld is a bare-bones GLFW window with Vulkan test.

2. Vulkan3DEngineTriangle is a simple triangle rendered with Vulkan using a vertex and fragment shader from Brendan Galea's tutorial (up to part 5).

3. ... to be continued.

4. Vulkan3DEngine will be the final demonstration project with of a simple 3D engine using Vulkan. **Note I have not yet finished the series, so this is a work in progress.** As it stands this will be the current progress where I am at.
