
set(EXECUTABLE_NAME "PhyMHC")

project(${EXECUTABLE_NAME} VERSION 0.1 LANGUAGES CXX)

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

# file(GLOB CPP_CONTROLLERS src/controllers/*.cpp)
# file(GLOB HPP_CONTROLLERS src/controllers/*.h)

# file(GLOB CPP_LIBS lib/*.cpp)
# file(GLOB HPP_LIBS lib/*.h)

# add_definitions(-DQCUSTOMPLOT_USE_OPENGL )
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

qt_add_executable(${EXECUTABLE_NAME}
    ${HEADERS} ${SOURCES} 
    # ${CPP_CONTROLLERS} ${HPP_CONTROLLERS}
    # ${CPP_LIBS} ${HPP_LIBS}
    ${QML_RESOURCES}
)

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE Qt6::Quick
            Qt6::QuickControls2
            Qt6::Charts
            Qt6::PrintSupport
            # Qt6::OpenGL
            # opengl32
)