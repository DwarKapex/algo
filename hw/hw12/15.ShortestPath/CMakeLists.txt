set(this ShortestPath)

# add main
add_executable(main_${this} main.cpp ${this}.cpp ${this}.h)
set_target_properties(main_${this} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(main_${this} graph)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "*.h")
