add_executable(${PROJECT_NAME} "main.cpp")
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::System SFML::Window)
target_link_libraries(${PROJECT_NAME} PRIVATE GSL)
# target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann::json)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(ImGui-SFML PRIVATE "../build/_deps/imgui-src/")

target_precompile_headers(${PROJECT_NAME} PRIVATE "include/Iridium/libraries.hpp")

# set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)
# set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD_MODE BATCH)

add_subdirectory("src/Iridium")
add_subdirectory("src/Project")