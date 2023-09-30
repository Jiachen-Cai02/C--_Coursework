# A Virtual Solar System

This is the starting repository for assignment 2 of PHAS0100: Research Computing with C++. You may add or remove C++ files in any directory. You should organise the files as you see fit but do read the Folder Structure section below to understand the intended use of the existing folders.

## Installing dependencies

We are using the package manager Conan to install the dependencies Catch2 and Eigen. In order to use CMake's `Release` target for performance and `Debug` for debugging, the libraries must be installed twice with:

```
conan install . --output-folder=build --build=missing -s build_type=Debug
conan install . --output-folder=build --build=missing -s build_type=Release
```

If you delete the `build` directory to clean your build, you may have to install the dependencies again.

## Building

To build from the project root directory you should run:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

If you wish to debug your code, you should replace `Release` with `Debug`. For performance measurements, ensure you have built with the `Release` target.

## Testing

Once the project has been built, it can be tested by running:

```
cd build
ctest
```

## Folder structure

The project is split into four main parts aligning with the folder structure described in [the relevant section in Modern CMake](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html):

- `app/` contains all code implementing the command-line application.
- `lib/` contains all non-app code. Only code in this directory can be accessed by the unit tests.
- `include/` contains all `.hpp` files.
- `test/` contains all unit tests.

You are expected to edit the `CMakeLists.txt` file in each folder to add or remove sources as necessary. For example, if you create a new file `test/particle_test.cpp`, you must add `particle_test.cpp` to the line `add_executable(tests test.cpp)` in `test/CMakeLists.txt`. Please ensure you are comfortable editing these files well before the submission deadline. If you feel you are struggling with the CMake files, please see the Getting Help section of the assignment instructions.

## Usage Instructions

To run the solarSystemSimulator by following pattern:
```
build/solarSystemSimulator
```
Firstly, the help information could be checked by following lines:
```
build/solarSystemSimulator -h
```
or
```
build/solarSystemSimulator --help
```
If you want to simulate the solar sytem, there are 3 input parameters to run the program:
```
timesteps | time length/number of steps | pattern
```
Where the timesteps is a small time interval for implementing the simulation. There are two patterns in the solar simulator, you can input the total length of the time with the argument ***time*** (number of years) and the total steps of the simulator would be the time length divided by time steps. What's more, you can also input the number of the steps directly to run the simulator with the argument ***step***. 

Example for ***time*** pattern:
```
build/solarSystemSimulator 0.0001 1 time
```
Example for ***step*** pattern:
```
build/solarSystemSimulator 0.0001 100 step
```

If you want to simulate the random sytem, there are 4 input parameters to run the program:
```
timesteps | time length/number of steps | pattern | number of particles
```

Where the last argument is the number of the particles in the whole system

Example for ***time*** pattern with 100 particles:
```
build/solarSystemSimulator 0.0001 1 time 100
```

Example for ***step*** pattern with 100 particles:
```
build/solarSystemSimulator 0.0001 100 step 100
```

## Simulate results
### 1.3e Result of 1 full year
The simulation result of the solar system could be shown in the table with a timestep of 0.0001 as below (the z axis data is ignored with all zero values):
|Name|position(before simulation)|position(after simulation)|
|:------:|:------:|:------:|
|Sun|(0, 0)|(-0.000421348 -0.000607874)|
|Mercury|(0.05323, 0.396442)|(0.287804 0.287966)|
|Venus|(-0.0102407, 0.699925)|(0.674669 -0.195638)|
|Earth|(-0.487701, -0.873011)|(-0.493769 -0.871868)|
|Mars|(1.02355, -1.09651)|(-1.28606 0.773657)|
|Jupiter|(-3.44428, -3.89576)|(-1.00302  -5.1023)|
|Saturn|(-9.45137 -0.960015)|(-9.02984 -2.95072)|
|Uranus|(18.7679 -4.05025)|(9.0178 -2.63859)|
|Neptune|(29.6641 5.10421)|(29.4484 6.22889)|
  

According to the results, it is obvious that after 1 full year the position of earth remain the same with appropriate error. When the timestep equals to 0.0001, the result of the earth position accuracy is in the range of 0.01 according to the test.
### 2.1 Calculating numerical energy loss
The result of the solar system energy difference could be shown in the table with 8 different timesteps and 100 full years:
|timestep|total energy(before)|total energy(after)|
|:------:|:------:|:------:|
|1000|-0.000112427|10.545|
|100|-0.000112415|0.105553|
|10|-0.000112442|0.00106875|
|1|-0.000112415|8.52785e-05|
|0.1|-0.000112422|-6.29764e-05|
|0.01|-0.000112417|-0.000102496|
|0.001|-0.000112428|-0.000109823|
|0.0001|-0.000112448|-0.000111727|
  
According to the result, it is clear that the solar system would have a larger variance in total energy when the timestep is larger.

### 2.2 Benchmarking the simulation
The result of the total running time with different compiler options and timesteps:
|timestep|total time(s)(with -O0)|total time(s)(with -O2)|
|:------:|:------:|:------:|
|1000|0.00164404|0.00124613|
|100|0.00128304|0.00118604|
|10|0.00161071|0.00141187|
|1|0.0139736|0.00657125|
|0.1|0.0734255|0.0267113|
|0.01|0.386313|0.177923|
|0.001|3.46633|1.65031|
|0.0001|34.5909|16.64|

The result of the average running time with different compiler options and timesteps:
|timestep|avg time(s)(with -O0)|avg time(s)(with -O2)|
|:------:|:------:|:------:|
|1000|0.00261657|0.00198327|
|100|0.000204202|0.000188764|
|10|2.56352e-05|2.24707e-05|
|1|2.22396e-05|1.04585e-05|
|0.1|1.1686e-05|4.25124e-06|
|0.01|6.14836e-06 |2.83173e-06|
|0.001|5.51683e-06|2.62654e-06|
|0.0001|5.50532e-06|2.64834e-06|

According to the results above, a timestep of 0.00001 would be selected and the performance could be shown as below:
|timestep|total energy(before)|total energy(after)|
|:------:|:------:|:------:|
|1000|-0.000112423|-0.000112306|

|timestep|total time(with -O2)|avg time(with -O2)|
|:------:|:------:|:------:|
|0.00001|162.595|2.58778e-06|

According to the results above, the error of the total energy is slightly small with a reasonable running time (in 3 minutes)

### 2.3 Increasing the scale of the system
In this section, the scale of the system is increased and the data of each particle would be generated based on uniform distribution with random seed. The range of masses should be distributed between 1./6000000 and 1./1000, the distances from the origin should be distributed between 0.4 and 30 and the initial angle for each body should be distributed between 0 and 2$\pi$.  
The performance of the simulation based on timestep of 0.01 and 10 full years time could be shown as below:
|num_particles|total time(s)(with -O2)|avg time(s)(with -O2)|
|:------:|:------:|:------:|
|8|0.0712892|6.24529e-06|
|64|0.807154|0.000128462|
|256|12.0403|0.00191628|
|1024|232.806|0.0370523|
|2048|1214.94|0.193363|
  
According to the results, the running time scale approximately with the square of the number of the partilces.

### 2.4 Parallelising with OpenMP
In this section, the OpenMP would be used for the nested loop in the main function. A laptop with 6 cores would be used in this section. A timestep of 0.15 and 10 full years time would be used in this section.
  
The results of the strong scaling experiment of 2048 particles would be shown as below:
|OMP_NUM_THREADS|time(s)|speedup|
|:------:|:------:|:------:|
|1|60.8717|1|
|2|60.3975|1.008|
|3|42.3691|1.437|
|4|33.4677|1.819|
|5|27.6177|2.204|
|6|25.1389|2.421|
|12|27.5747|2.208|
  
According to the results, when the number of the threads get the maximum value, the speedup of the parallelising is about 2.421. In this section, only the two loops that iterate the all particles pointer are parallelised because the order of generating force and update the update the information of the particles, it may be a reason that the speedup is not ideal as other cases.

The results of the weak scaling experiment would be shown as below:
|OMP_NUM_THREADS|Num Particles|time(s)|speedup|
|:------:|:------:|:------:|:------:|
|1|2048|63.8731|1|
|2|4096|234.877|0.272|
|3|6144|357.557|0.179|
|4|8192|481.216|0.133|
|5|10240|622.269|0.103|
|6|12288|773.527|0.083|

  
When the number of threads increase with the number of particles increasing, the speed up decreaes because the performance should scale with the square of the number of particles.





## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
