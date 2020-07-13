set(this SegmentTree)

# add main
add_executable(main_SegmentTree main.cpp)
set_target_properties(main_BST PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "*.h")
