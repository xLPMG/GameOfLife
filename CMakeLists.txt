cmake_minimum_required(VERSION "3.25.2")
project("LifeSimulator")
add_executable("${PROJECT_NAME}" "Main.cpp")
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "Main.cpp" DESTINATION src)
