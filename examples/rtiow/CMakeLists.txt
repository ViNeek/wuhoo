find_package(X11)
find_package(Threads)

include_directories(../../ ./)

project (RTIOW)


include(CheckCXXSourceCompiles)

add_executable(${PROJECT_NAME} rtiow.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  target_link_libraries(${PROJECT_NAME} "-framework Carbon" "-framework Cocoa" objc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lm)
endif()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .)

set_target_properties(${PROJECT_NAME} PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_FRAMEWORK_IDENTIFIER ${PROJECT_NAME}
  RESOURCE "${RESOURCE_FILES}"
)
