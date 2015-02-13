Lime microsystems suite (2014-11-11)

1. What is it?
--------------
This software bundle is designed for configuring LMS6002 transceiver boards.
Currently supported boards: EVB6, DigiGreen, DigiRed, Zipper.
This software can run on Windows and Linux operating systems.

2. Compiling
------------
Project can be compiled on Windows or Linux operating system using CodeBlocksIDE
or using Make files on Linux. This project uses wxWidgets-3.0, fftw3 libraries. 
On Linux system additional libusb-1.0 library is required. wxWidgets must be 
compiled with openGL support.

Libraries can be downloaded from the following links:
	http://www.wxwidgets.org
	http://www.fftw.org

To build software using CodeBlocks IDE, open the project lms-suite.cbp. Adjust
project compiler and linker search paths according to your system configuration.
Select "Release" target and build it. The built software executable will be 
placed in lms-suite/bin directory.

On Linux operating system, to build software using Make files, open command line
and navigate to project directory. Execute 'make release' command and wait for 
the compilation process to complete. The built software executable will be 
placed in lms-suite/bin directory.

For additional information how to compile this software read compilation_guide
documents

3. Additional notes
-------------------
When running this software on Linux, it should be executed with admin privileges,
or the USB device permissions has to be changed to allow non admin users to use it.
