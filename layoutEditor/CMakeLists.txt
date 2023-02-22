find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE LAYOUTEDITOR_SOURCES src/*.cpp include/*.h)
set(XTDB_INST_DIR ${PROJECT_SOURCE_DIR}/../xtdbInstDir/)
file(GLOB_RECURSE LAYOUTEDITOR_HEADERS include/*.h)
#add_custom_target(headers SOURCES ${LAYOUTEDITOR_HEADERS}) #for showing header files in qt creator
qt_add_executable(layoutEditor MANUAL_FINALIZATION ${LAYOUTEDITOR_SOURCES})
include_directories(include)
include_directories(${XTDB_INST_DIR}/include)
target_link_directories(layoutEditor PRIVATE ${XTDB_INST_DIR}/lib)
target_link_libraries(layoutEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(layoutEditor PRIVATE xtdb)

set_target_properties(layoutEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(layoutEditor)
endif()

