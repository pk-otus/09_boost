cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
   project(bccl VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
   project(bccl VERSION 0.0.1)
endif()

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bccl custom_concepts.h main.cpp)

if (MSVC)
	set_target_properties(bccl PROPERTIES
		COMPILE_OPTIONS -W3 
	)	
else()
	set_target_properties(bccl PROPERTIES
		COMPILE_OPTIONS -Wpedantic -Wall -Wextra 
	)	
endif()



set_target_properties(bccl PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIR}"
)

target_link_libraries(bccl ${Boost_LIBRARIES} )

install(TARGETS bccl RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT a@a.a)

include (CPack)