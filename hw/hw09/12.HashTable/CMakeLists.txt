set(this HashTable)

# add main
add_executable(HashTable main.cpp ${this}.cpp ${this}.h)
set_target_properties(main_BST PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "*.h")

# add test
add_subdirectory(test)
