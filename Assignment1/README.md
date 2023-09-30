[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-f4981d0f882b2a3f0472912d15f9806d57e124e0fc890972558857b51b24a6f9.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=9991601)
PHAS0100ASSIGNMENT1
------------------

Purpose
-------

This project serves as a starting point for the PHAS0100 2022/23 Assignment 1 Game of Life Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Further information on the specific project is left as an exercise for the student.

Credits
-------

This project is maintained by [Dr. Jamie Quinn](http://jamiejquinn.com/). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](https://github-pages.ucl.ac.uk/research-computing-with-cpp/) course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james) and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).

Build Instructions
------------------

To run cmake:

```
cmake -B build
```

To compile:

```
cmake --build build
```

To test:

```
cd build
ctest
```

After the building sections, the game could be started by the command lines as follow:
```
./bin/golSimulator
```
To get the instructions of the game, there are two ways:

```
./bin/golSimulator -h
```
or
```
./bin/golSimulator --help
```
There are serval types of inputs to start the game, the first one is to define rows, columns and steps. The alive cells would be determined randomly by the program:
```
./bin/golSimulator rows, columns, steps
```
The second one is to define rows, columns, number of alive cells and steps. The locations of the alive cells would be determined randomly by the program:
```
./bin/golSimulator rows, columns, number of alive cells, steps
```
If you want to start game with txt file, the input should be the path and number of steps:
```
./bin/golSimulator path of txt file, steps
```
What's more, this program could also find the still pattern of the game with specific inputs. The inputs should be like following:
```
./bin/StillLifes rows, columns, number of alive cells, maximum iterations, number of different initial conditions
```

The screenshot with glider txt file could be displayed as follow:
![](./results_screenshots/running%20with%20glider.png)
The screenshot with 7 by 7 grids could be displayed as follow:
![](./results_screenshots/running%20with%20glider.png)
The screenshot of still pattern 4 by 4 grids could be displayed as follow:
![](./results_screenshots/still%20pattern%20of%204%20by%204%20grids.png)