find_package(Qt6 REQUIRED COMPONENTS Widgets)
file(GLOB_RECURSE XTLAYOUT_SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE XTLAYOUT_HEADERS include/*.h)
#add_custom_target(headers SOURCES ${XTLAYOUT_HEADERS}) #for showing header files in qt creator
qt_wrap_ui(UI_FILES mainwindow.ui)
qt_add_executable(xtLayout MANUAL_FINALIZATION ${XTLAYOUT_SOURCES} ${UI_FILES})
include_directories(include)
target_link_libraries(xtLayout PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
find_package(xtdb CONFIG REQUIRED)
target_link_libraries(xtLayout PRIVATE xtdb)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(xtLayout)
endif()

