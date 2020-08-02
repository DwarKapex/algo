set(this graph)
# add headers to show up in the IDE
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
add_library(${this} DiGraph.cpp ${HEADER_LIST})

set_target_properties(${this} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

# we need this directory and all users of our library too
target_include_directories(${this} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})