set(hw 1)
while(hw LESS_EQUAL HW_DONE)
    if (hw LESS 10)
    	add_subdirectory("hw0${hw}")
    else()
	add_subdirectory("hw${hw}")
    endif()
    MATH(EXPR hw "${hw}+1")
endwhile()