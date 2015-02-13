# FFT viewer and ctr_6002dr2 software

1. Archive directory structure:
	./src/GUI - directory with source code for FFT viewer
	./src/Logic - directory with source code for ctr_6002dr2
	./src/wxsmith - FFT viewer gui defintions for CodeBlocks WxSmith plugin
	./src/Logic/dependencies - additional libraries needed to compile ctr_6002dr2 and FFT viewer
	./bin - Windows binaries
	
2. Description
	This software is designed to control LMS6002 chip and Myriad RF board.
	The FFT viewer collects I,Q channel data samples and performs FFT calculations,
	then displays results in graphs.
	
	This software can be compiled and executed on Windows and Linux operating systems.
	On Windows operating systems FFT viewer uses Cypress USB library to communicate
	with devices, on Linux operating system it is replaced by LibUSB library.
	
3. Compiling
	This archive contains project file for CodeBlocks IDE and which is compiled 
	by using GCC compiler, it has build targets	configured for Windows and Linux
	versions. Open project and select build target ReleaseWin32 or ReleaseLinux 
	depending on your operating system.	For windows version you need to change
	compiler, linker and resource compiler search paths to wxWidgets library directory.
	These settings can be found in project properties->Build targets, select GUIReleaseWIN32
	and open Build options. In search directories tab add needed directories.
	
	On Windows this software requires to be linked with:
	fftw3f, pthreads, libCyAPI_fx3_GCC.a, wxWidgets libraries

	On Linux this software requires to be linked with:
	libusb-1.0, fftw3f, pthreads, wxWidgets
	
4. Additional info
	On linux this software requires admin rights, otherwise it will be unable 
	to use USB device, also connected chips are discovered only at launch of
	this software.
