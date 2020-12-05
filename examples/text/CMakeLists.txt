find_package(X11)

include_directories(../../ ./)

project (Editor)
add_executable(${PROJECT_NAME} editor.c)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(${PROJECT_NAME} "-framework Carbon" "-framework Cocoa" objc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} -lm)
endif()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .)

set_target_properties(${PROJECT_NAME} PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_FRAMEWORK_IDENTIFIER ${PROJECT_NAME}
  RESOURCE "${RESOURCE_FILES}"
)
