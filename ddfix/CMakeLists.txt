set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_custom_command(OUTPUT ColorKeyHLSLC COMMAND fxc.exe /Eps_main /Vng_colorKeyHLSLC /Tps_2_b /Fh${CMAKE_CURRENT_BINARY_DIR}\\ColorKeyHLSLC.h /nologo ddraw\\ColorKey.hlsl WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB SRC_DINPUT dinput/*.h dinput/*.cpp)
FILE(GLOB SRC_DDRAW ddraw/*.h ddraw/*.cpp)
FILE(GLOB SRC_DSHOW dshow/*.h dshow/*.cpp)
FILE(GLOB SRC_COMMON Common/*.h Common/*.cpp)

FILE(GLOB SOURCE_FILES *.h *.cpp *.def)
include_directories(${EXTRADXSDK_INCLUDE_DIR})
link_directories(${EXTRADXSDK_LIB_DIR})
add_library(ddfix SHARED ${SOURCE_FILES} ${SRC_DINPUT} ${SRC_DDRAW} ${SRC_DSHOW} ${SRC_COMMON} ColorKeyHLSLC)
target_link_libraries(ddfix minhook dinput8.lib Strmiids.lib d3d9.lib d3dx9.lib legacy_stdio_definitions.lib "-SAFESEH:NO")

source_group("dinput" FILES ${SRC_DINPUT})
source_group("ddraw" FILES ${SRC_DDRAW})
source_group("dshow" FILES ${SRC_DSHOW})
source_group("Common" FILES ${SRC_COMMON})


configure_file(vcxproj.user.in ddfix.vcxproj.user @ONLY)


