find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE XTLAYOUT_SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE XTLAYOUT_HEADERS include/*.h)
#add_custom_target(headers SOURCES ${XTLAYOUT_HEADERS}) #for showing header files in qt creator
qt_add_executable(xtLayout MANUAL_FINALIZATION ${XTLAYOUT_SOURCES})
include_directories(include)
target_link_libraries(xtLayout PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
find_package(xtdb CONFIG REQUIRED)
target_link_libraries(xtLayout PRIVATE xtdb)
set_target_properties(xtLayout PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(xtLayout)
endif()

