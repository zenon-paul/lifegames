# 2D/3D lifegame
This tool enables you to play 2D/3D lifegame.

＊[What is lifegame?](https://ja.wikipedia.org/wiki/%E3%83%A9%E3%82%A4%E3%83%95%E3%82%B2%E3%83%BC%E3%83%A0)
## Demo

## Description
This is a tool that achieves highspeed processing by implementing it on a bit bord.
## Requirement
You need "Visual Studio 2019" to use this tool.
If you already hane it, please follow the steps below.

*step 1 
Pleaase download these four files.

*step 2 
Please make an enpty project.

*step 3
Please introduce openGL.
(You can get elements you need to use openGL by making use of NuGet. Please select "Manage NuGet Packages..." in "Project" tab.
Then you will find "nupengl.core" and "glm" easily by entering these  two name in search box.These two libraries are required for 
openGL.)

### If you will play 2D lifegame
*step 4
Please add 2DLifegame.cpp as source file and 2DLifegemeHeader.h as header file.

### If you will play 3D lifegame
*step 4
Please add 3DLifegame.cpp as source file and 3DLifegemeHeader.h as header file.

*step 5
Please run the program!

## Usage
### 2D lifegame
*Left-click
When you click once the square you click on gets "ON".
when you click "ON" square it gets "OFF".
*Right-click
The simulation gets started.
### 3D lifegame
You will see some message in standard output.Please enter number to dicide Lifegame-rule and initial state.
*Right-click
The simulation gets started.

## Note
In 2D Lifegame, squares in red area get "OFF" forcibly due to convenience if implementation.



