![MAGPIE](resources/splash.png)

MAGPIE is a learning and teaching tool introducing the basics of genetic programming, through the use of graphical and interactive examples.

The goal of the project was to produce a platform-independent software tool for the purpose of learning and teaching genetic programming concepts, including hands-on practical experiments to help users engage with the software. 

The application features eight different lessons covering the basics of genetic programming, including; genetic programming operators, selection methods, fitness, generations, and tree representation. The lawnmower problem is used to aid the teaching of these concepts, as it is a simple to understand problem and can easily be graphically represented.

Various graphical representations are used in the application to aid teaching, by helping users to engage with the software.
Lessons six to eight allows users to conduct full genetic programming runs. Users have the ability to alter run parameters, such as; crossover and mutation rates, population size, maximum tree size, and the selection method.


# Running

Precompilied binaries have been included for Windows, Ubuntu and Mac OSX, all of which can be found under releases.

For Ubuntu, the Qt libraries will need to be present on the system.
Use the following command to install them:

    sudo apt-get install libqt4-core librqt4-gui libqt4-opengl

Execute permission is required, which can be enabled with the following command on the binary file:

    sudo chmod MAGPIE u+x


# Documentation

Full HTML documentation has been provided for the source code, which can be found [here](doc/html/index.html).


# Building

The application can be compiled on Windows, Ubuntu or Mac OSX using the following steps:

1. Download and install Qt libraries 4.8.4 and Qt Creator 2.7.0 from http://qt-project.org/downloads. Other versions may work but have not been tested

2. Launch Qt Creator and open the MAPGPIE.pro project file

3. When prompted to configure the project, choose build directories for the build and debug versions, then press configure project.

4. Build the application (ctrl + B)

5. The binary will now be in the selected build folder

For Mac, run the following command from the terminal to add the Qt framework to the binary:

    macdeployqt MAGPIE.app -dmg

For Ubuntu the Qt libraries will need to be installed on the target platform:

    sudo apt-get install libqt4-core librqt4-gui libqt4-opengl

For Windows QtCore4.dll, QtGui4.dll and QtOpenGL4.dll will need to be placed in the same folder as the binary
 