set(this HarryPotterSquare)

add_executable(${this} main.cpp)
set_target_properties (${this} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
