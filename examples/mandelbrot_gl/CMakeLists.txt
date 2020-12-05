set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND NOT ${OPENGL_FOUND})
  execute_process(COMMAND bash -c "find /usr/lib/ -name libGL.so.* | head -n 1" OUTPUT_VARIABLE OPENGL_LIBRARIES)
  string(STRIP ${OPENGL_LIBRARIES} OPENGL_LIBRARIES)
  message("-- Using OpenGL library found at " ${OPENGL_LIBRARIES})
endif()

find_package(X11)

include_directories(../../ ./)

project (MandelbrotGL)
add_executable(${PROJECT_NAME}
  mandelbrot.c
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(${PROJECT_NAME} "-framework Carbon" "-framework Cocoa" "-framework Quartz" "-framework OpenGL" objc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} ${OPENGL_LIBRARIES} -lm)
else()
  target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  install(FILES mandelbrot.vs.glsl DESTINATION .)
  install(FILES mandelbrot.fs.glsl DESTINATION .)
endif()

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/mandelbrot_gl/mandelbrot.fs.glsl ${CMAKE_CURRENT_BINARY_DIR}/mandelbrot.fs.glsl
)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/mandelbrot_gl/mandelbrot.vs.glsl ${CMAKE_CURRENT_BINARY_DIR}/mandelbrot.vs.glsl
)

set(RESOURCE_FILES
  mandelbrot.vs.glsl
  mandelbrot.fs.glsl
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_FRAMEWORK_IDENTIFIER ${PROJECT_NAME}
  RESOURCE "${RESOURCE_FILES}"
)
