set(SOURCES 
	"Imp3D.cpp"
	"Entities.cpp"
	"Components.cpp"
	"Systems.cpp"
	"ConsoleLogger.cpp"
)

set(HEADERS
	"Imp3D.h"
	"Entities.h"
	"Components.h"
	"Systems.h"
	"ConsoleLogger.h"
)

file(
	COPY ${CMAKE_SOURCE_DIR}/Imp3D/shaders
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable (Imp3D ${SOURCES} ${HEADERS} ${GLAD_DIR}/src/glad.c ${STB_DIR}/stb_image.h)

target_include_directories(Imp3D PUBLIC ${GLAD_DIR}/include)
target_include_directories(Imp3D PUBLIC ${STB_DIR})

target_link_libraries(Imp3D PRIVATE glfw)
target_link_libraries(Imp3D PRIVATE glm)