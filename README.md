# ML-KEM

C++ implentation of the post-quantum key establishment scheme ML-KEM


## Authors

- [@Benoît Wattinne](https://www.github.com/Benoit62)
- [@Aurélien Degain](https://www.github.com/aurelienDgn)
- [@Hamza Berbache](https://www.github.com/Hamz11)
- [@Louis Landouzy](https://www.github.com/LouisLandouzy)
- [@Enzo Barea](https://www.github.com/Ximaere)


## Deployment

### C++ Development Environment Setup

This guide will help you set up a C++ development environment in Visual Studio Code (VSCode) and compile/run a C++ program.

#### Prerequisites

Before you begin, make sure you have the following installed on your system:

- C++ Compiler: Install a C++ compiler such as GCC or Clang. You can download GCC from the official website or install Clang using package managers like Homebrew (for macOS) or apt-get (for Linux).

- Visual Studio Code: [Download and install VSCode](https://code.visualstudio.com/)

#### Setting up C++ in VSCode

1. Open VSCode and install the C++ extension. You can find it in the VSCode Extensions marketplace or install it from the command palette (`Ctrl+Shift+X`) by searching for "C++".

2. Once the C++ extension is installed, open the command palette (`Ctrl+Shift+P`) and search for "C++: Edit Configurations". Select it to create a `c_cpp_properties.json` file.

3. In the `c_cpp_properties.json` file, configure the include paths and compiler path according to your system setup. For example:

    ```json
    {
        "configurations": [
            {
                "name": "Win32",
                "includePath": [
                    "${workspaceFolder}/**"
                ],
                "defines": [],
                "compilerPath": "C:/MinGW/bin/g++.exe",
                "cStandard": "c11",
                "cppStandard": "c++17",
                "intelliSenseMode": "gcc-x64"
            }
        ],
        "version": 4
    }
    ```

4. Restart VSCode to apply the changes.

#### Compiling and Running a C++ Program

1. Create a new C++ file with a `.cpp` extension, for example `main.cpp`.

2. In the new C++ file, write your C++ program code.

3. To compile and run the C++ program, open the integrated terminal in VSCode by selecting `View -> Terminal` or using the shortcut `Ctrl+` backtick.

4. In the terminal, navigate to the directory where your C++ file is located using the `cd` command.

5. Use the `g++` command followed by the name of your C++ file to compile the program. For example:

    ```shell
    g++ main.cpp -o main
    ```

    This will generate an executable file named `main` in the same directory.

6. Finally, use the `./` command followed by the name of the executable file to run the program. For example:

    ```shell
    ./main
    ```

    The output of your C++ program will be displayed in the terminal.

That's it! You now have a C++ development environment set up in VSCode and know how to compile and run a C++ program.

Happy coding!

## Documentation

*Coming soon...*
