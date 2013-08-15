cmake_minimum_required ( VERSION 2.6 )
project (ispc_template)

include(FindISPC.cmake)

set(alignment 32)

set(CMAKE_CXX_COMPILER "icc")
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_RELEASE "-vec-report=3 -O3 -g -std=c++0x")

include_directories(include)

if(NOT DEFINED USE_DOUBLE)
  set(use_double -DUSE_DOUBLE=0)
else()
  set(use_double -DUSE_DOUBLE=${USE_DOUBLE})
endif()
add_definitions(-DALIGNMENT=${alignment} -DHAS_MATERIAL_EFFECTS=0 ${use_double})

ispc_compile(${CMAKE_SOURCE_DIR}/ispc/saxpy.ispc "--target=avx ${use_double} --opt=force-aligned-memory --force-alignment=${alignment}" SAXPY)

#ispc_compile_phi(${CMAKE_SOURCE_DIR}/ispc/saxpy.ispc "${use_double}" SAXPY)

add_executable(main src/main.cpp include/ispc/saxpy.ispc.h)
target_link_libraries(main ${SAXPY})
