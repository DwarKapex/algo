set(this BST)

add_library(${this} ${this}.cpp ${this}.h Node.h Node.cpp AVL.h AVL.cpp)
set_target_properties (${this} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

# add main
add_executable(main_BST main.cpp)
set_target_properties(main_BST PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries(main_BST BST)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "*.h")

# add test
add_subdirectory(test)

