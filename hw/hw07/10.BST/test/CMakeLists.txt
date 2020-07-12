# add test

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(this bst_test)
add_executable(${this} test_SimpleBST.cpp)

set_target_properties(${this} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(${this}
	BST
	${Boost_LIBRARIES}
)

