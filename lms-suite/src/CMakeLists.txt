cmake_minimum_required(VERSION 2.8)
set(CMAKE_CONFIGURATION_TYPES Release CACHE TYPE INTERNAL)
project("lms-suite")
if(${CMAKE_MAJOR_VERSION} GREATER 2)
	cmake_policy(SET CMP0043 NEW)
endif()
cmake_policy(SET CMP0015 OLD)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(FFTW3 REQUIRED)
include_directories(${FFTW3_INCLUDE_DIRS})
LINK_DIRECTORIES(${FFTW3_LIBRARIES})

if(WIN32)
	find_package(CyAPI REQUIRED)
	LINK_DIRECTORIES(${CYAPI_LIBRARIES})	
	include_directories(${CYAPI_INCLUDE_DIRS})
endif()

include_directories(
	${PROJECT_SOURCE_DIR}/gui_src/fft
	${PROJECT_SOURCE_DIR}/gui_src/fft/oglGraph
	${PROJECT_SOURCE_DIR}/gui_src/fft/oglGraph/glew
	${PROJECT_SOURCE_DIR}/gui_src
	${PROJECT_SOURCE_DIR}/gui_src/lms6
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/lms6
)

set(logic_files 
src/CommonUtilities.cpp
src/ConnectionCOM.cpp
src/ConnectionManager.cpp
src/ConnectionSPI.cpp
src/ConnectionUSB.cpp
src/MessageLog.cpp
src/Programmer.cpp
src/Protocols.cpp
src/Si5351C.cpp
src/Si5356A.cpp
src/SignalHandler.cpp
src/lmSemaphore.cpp
src/lmThread.cpp
src/lms6/CompoundOperations.cpp
src/lms6/ADF_module.cpp
src/lms6/Algorithms.cpp
src/lms6/LMS6002_MainControl.cpp
src/lms6/LMS_Parameter.cpp
src/lms6/PLL.cpp
src/lms6/RegistersMap.cpp
)

set(gui_files 
gui_src/pnlSi5351C.cpp
gui_src/pnlSi5356A.cpp
gui_src/pnlWFMLoader.cpp
gui_src/fft/oglGraph/GLFont.cpp
gui_src/fft/oglGraph/OpenGLGraph.cpp
gui_src/fft/oglGraph/glew/glew.c
gui_src/fft/pnlFFTviewer.cpp
gui_src/lms6/ComboBoxMap.cpp
gui_src/lms6/LMS6002_GUI_Main.cpp
gui_src/lms6/RadioGroupMap.cpp
gui_src/lms6/UARFCN.cpp
gui_src/dlgAbout.cpp
gui_src/dlgConnectionSettings.cpp
gui_src/fft/FFTcalculator.cpp
gui_src/fft/NovenaFPGA.cpp
gui_src/lms6/dlgFloatInput.cpp
gui_src/fft/PlotUpdateThread.cpp
gui_src/fft/SamplesCollector.cpp
gui_src/fft/UnitsButton.cpp
gui_src/fft/dlgExtraControls.cpp
gui_src/lms6/pnlTxPLL.cpp
gui_src/lms6/pnlTxRF.cpp
gui_src/lms_suiteApp.cpp
gui_src/lms_suiteMain.cpp
gui_src/pnlADF4002.cpp
gui_src/pnlMinimalControls.cpp
gui_src/pnlMyriadRF2.cpp
gui_src/pnlNovena.cpp
gui_src/pnlProgramming.cpp
gui_src/pnlSPI.cpp
gui_src/lms6/pnlRxFE.cpp
gui_src/lms6/dlgFreqVsCap.cpp
gui_src/lms6/dlgLogger.cpp
gui_src/lms6/dlgRegisterTest.cpp
gui_src/lms6/pnlADDC.cpp
gui_src/lms6/pnlRxVGA2.cpp
gui_src/lms6/pnlSystem.cpp
gui_src/lms6/pnlTop.cpp
gui_src/lms6/pnlTxLPF.cpp
gui_src/pnlHPM1000.cpp
gui_src/pnlInfo.cpp)

add_executable(lms-suite ${logic_files} ${gui_files})
ADD_DEFINITIONS(-DGLEW_STATIC)
#disable unicode
ADD_DEFINITIONS(-UUNICODE)
ADD_DEFINITIONS(-U_UNICODE)

find_package(wxWidgets REQUIRED richtext xml html xrc adv aui core base gl)
include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_DEBUG OFF)
set(wxWidgets_USE_UNICODE OFF)
set(wxWidgets_USE_UNIVERSAL OFF)
set(wxWidgets_USE_STATIC ON)
target_link_libraries(lms-suite ${wxWidgets_LIBRARIES})
target_link_libraries(lms-suite ${FFTW3_LIBRARIES})

if(WIN32)
	target_link_libraries(lms-suite kernel32 user32 gdi32 advapi32 uuid winspool comdlg32 shell32 ole32 oleaut32 comctl32 wsock32 odbc32)
	target_link_libraries(lms-suite ${CYAPI_LIBRARIES})
	configure_file(${FFTW3_LIBRARY_DLL} ${CMAKE_BINARY_DIR}/Release/libfftw3f-3.dll COPYONLY)
	if(MSVC)
		set_property(TARGET lms-suite APPEND PROPERTY LINK_FLAGS /SUBSYSTEM:WINDOWS)
		#disable annoying visual c++ warnings
		ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)		
	endif()
endif()
if(UNIX)
	target_link_libraries(lms-suite GL usb-1.0)	
endif()
