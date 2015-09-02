cmake_minimum_required(VERSION 2.8) #проверка версии cmake

set(PROJECT video_processing) #присваиваем переменной PROJECT название проекта

project(${PROJECT} CXX)

if ( NOT DEFINED LIBAV_INCLUDE )
    message(FATAL_ERROR "path to header files for libav not found")
endif()

if ( NOT DEFINED LIBAV_LIB )
    message(FATAL_ERROR "path to *.so files for libav not defined")
endif()

#макрос, выполняющий сборку с необходимыми параметрами в зависимости от значения входной переменной
macro(add_app_executable BUILD_TYPE)
    if (${BUILD_TYPE} STREQUAL "release")#если значение входной переменной равно release, то
        aux_source_directory("./sources" SOURCES)#задаем папки в которых хранятся исходники
        include_directories(${LIBAV_INCLUDE})
        link_directories(${LIBAV_LIB})
        add_executable(${PROJECT} ${SOURCES}) #создаем исполняемый файл
        set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS "-O2 -std=c++11 -pedantic -Wall -Wextra -DNDEBUG")#задаем ключи компилятора и макросы для цели ${PROJECT}
        target_link_libraries(${PROJECT} avcodec)
        add_custom_command(TARGET ${PROJECT} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ../${BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT}> ../${BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${PROJECT}>)
    endif ()

    if (${BUILD_TYPE} STREQUAL "debug")#если значение входной переменной равно Debug, то
        aux_source_directory("./sources" SOURCES)#задаем папки в которых хранятся исходники
        include_directories(${LIBAV_INCLUDE})
        link_directories(${LIBAV_LIB})
        add_executable(${PROJECT}_debug ${SOURCES}) #создаем динамическую библиотеку
        set_target_properties(${PROJECT}_debug PROPERTIES COMPILE_FLAGS "-O0 -g3 -std=c++11 -pedantic -Wall -Wextra -D__LED_CONTROL_DEBUG__")#задаем ключи компилятора и макросы для цели ${PROJECT}
        add_custom_command(TARGET ${PROJECT}_debug POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ../${BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT}_debug> ../${BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${PROJECT}_debug>)
    endif ()
endmacro()

add_app_executable("release")
