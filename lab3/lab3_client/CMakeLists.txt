cmake_minimum_required(VERSION 3.19)
project(lab3_client LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(lab3_client
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    book.h book.cpp
    apiclient.h apiclient.cpp
)

target_link_libraries(lab3_client
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Widgets
        Qt6::Network
)

install(TARGETS lab3_client
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET lab3_client
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
