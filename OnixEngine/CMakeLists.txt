set(SOURCES 
	"OnixEngine.cpp"
)
set(HEADERS
	"OnixEngine.h"
)

add_executable (OnixEngine ${SOURCES} ${HEADERS} ${GLAD_DIR}/src/glad.c)

target_include_directories(OnixEngine PUBLIC ${GLAD_DIR}/include)
target_link_libraries(OnixEngine PRIVATE glfw)