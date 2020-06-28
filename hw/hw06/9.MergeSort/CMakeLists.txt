set(this MergeSort)

add_executable(${this} ${this}.cpp ${this}.h main.cpp)
set_target_properties (${this} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(${this} tester_lib)