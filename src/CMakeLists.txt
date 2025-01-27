
set(EXECUTABLE_NAME "PhyMHC")

project(${EXECUTABLE_NAME} VERSION 0.1 )

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_resources(QML_RESOURCES resources.qrc)

if(NOT DEFINED HEADERS)
    file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
endif()

if(NOT DEFINED SOURCES)
    file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
endif()

if(NOT DEFINED CONTROLLERHDR)
    file(GLOB CONTROLLERHDR ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.h)
endif()

if(NOT DEFINED CONTROLLERSRC)
    file(GLOB CONTROLLERSRC ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cpp)
endif()

if(NOT DEFINED LIBHDR)
    file(GLOB LIBHDR ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h)
endif()

if(NOT DEFINED LIBSRC)
    file(GLOB LIBSRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)
endif()

if(NOT DEFINED CHARTHDR)
    file(GLOB CHARTHDR ${CMAKE_CURRENT_SOURCE_DIR}/chart/*.h)
endif()

if(NOT DEFINED CHARTSRC)
    file(GLOB CHARTSRC ${CMAKE_CURRENT_SOURCE_DIR}/chart/*.cpp)
endif()

# file(GLOB CPP_CONTROLLERS src/controllers/*.cpp)
# file(GLOB HPP_CONTROLLERS src/controllers/*.h)

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

source_group("Controllers Header Files" FILES ${CONTROLLERHDR})
source_group("Controllers Source Files" FILES ${CONTROLLERSRC})

source_group("Lib Header Files" FILES ${LIBHDR})
source_group("Lib Source Files" FILES ${LIBSRC})

source_group("Chart Header Files" FILES ${CHARTHDR})
source_group("Chart Source Files" FILES ${CHARTSRC})

add_definitions(-DQCUSTOMPLOT_USE_OPENGL )

add_library(U SHARED icp/Global.h
                        icp/ICPDAS_USBIO.h
                        icp/ThreadFun.h
                        icp/Timer.h
                        icp/USBIO_Comm.h
                        icp/USBIO_Device.h
                        icp/USBIO_Object_Layout.h
                        )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libicp)

qt_add_executable(${EXECUTABLE_NAME}
${LIBHDR} ${LIBSRC}
${HEADERS} ${SOURCES} 
${CONTROLLERHDR} ${CONTROLLERSRC}
${CHARTHDR} ${CHARTSRC}
${QML_RESOURCES}
)

install (TARGETS ${EXECUTABLE_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE Qt6::Core
            Qt6::Quick
            Qt6::QuickControls2
            Qt6::Charts
            Qt6::PrintSupport
            Qt6::SerialPort
            Qt6::OpenGL
            # opengl32
            USBIO_64
)
