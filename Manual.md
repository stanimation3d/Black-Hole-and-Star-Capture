# How was this app compiled?
First, I downloaded the source code for this project, then I downloaded the Raylib library from "https://github.com/raysan5/raylib/releases" and installed it on any AOT compiler computer. I added "Add LLVM to the system PATH for all users" and then compiled it using the following command. Raylib library has been downloaded separately for Windows, Linux and MacOS, but you do not need to download separate versions of the compiler for each operating system to develop applications for each operating system. This is because the compiler is there to run on the computer system, regardless of which operating system version you use, and it certainly does not affect the executable code it can produce. By the way, if you put Raylib .h files in the same folder as your project, please use "raylib.h" and "raymath.h" instead of <raylib.h> and <raymath.h>, because "" refers to .h files that are in the same folder, and <> refers to the location where they were installed when installed on the system, this is valid for other libraries too! For example, we downloaded the Clang compiler

* If you are on Windows operating system
```
clang main.c game_logic.c game_draw.c -o black_hole_capture -Wall -lraylib -lm -lmingw32 -lopengl32 -lgdi32 -lwinmm
```
* If you are on Linux operating system
```
clang main.c game_logic.c game_draw.c -o black_hole_capture -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lasound
```
* If you are on MacOS operating system
```
clang main.c game_logic.c game_draw.c -o black_hole_capture -Wall -lraylib -lm \
    -framework Cocoa -framework OpenGL -framework IOKit -framework CoreAudio -framework CoreMIDI
```
That's all I have to say, but if the compiler you downloaded is not Clang, it will not start with the "clang" command. If you are using GNU Compiler, you need to type "gcc", in Tiny C Compiler it is "tcc". If you downloaded other compilers, you may see other commands! Other than that, the others are the same. 

However, the examples above are suitable for "Host Platform" compilation. In modern compilers, if we don't specify the operating system and CPU architecture when compiling, it will automatically compile for the computer's operating system and CPU architecture. This is called "Host Platform" compilation. If you want to develop an application for a different operating system on the operating system you're using, you need to add "--target=cpu_architecture-operating_system-gnu" between clang and main.c. Instead of "operating system," write the actual operating system name in all lowercase, but use a "_" instead of a space. Instead of "cpu_architecture," write the actual CPU architecture name in all lowercase, but use a "_" instead of a space. Raylib doesn't just support three operating systems! WebAssembly is a web platform, not an operating system, of course, but there are versions of Raylib built for other platforms. How you access them is up to you!
