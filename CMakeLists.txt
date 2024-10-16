cmake_minimum_required(VERSION 3.27.0)
project(gcc_starter VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(CTest)
enable_testing()
#[[s


]]#

#Codigo para añadir las librerias boost
#/set(BOOST_ROOT "C:/Program Files/Boost/boost_1_80_0/")
#find_package(Boost REQUIRED COMPONENTS)

#Codigo para añadir todos los archivos de src
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

#Compiler enable feature and flags 
#https://lefticus.gitbooks.io/cpp-best-practices/content/02-Use_the_Tools_Available.html
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wshadow -Wunused  -Wdouble-promotion 
                    -Wnull-dereference -Wconversion -Wduplicated-cond -Wduplicated-branches 
                    -Wnon-virtual-dtor -Wuninitialized  -Wlogical-op -Wformat=2 -Wmisleading-indentation
                    -Wformat-overflow -pedantic)

#Codigo para añadir carpetas include en modo PUBLIC
target_include_directories(${PROJECT_NAME} PUBLIC include)

#Codigo para añadir y linkear librerias boost
#target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS}) 
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
