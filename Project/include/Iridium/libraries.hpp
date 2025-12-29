#ifndef IRIDIUM_LIBRARIES_HPP_
#define IRIDIUM_LIBRARIES_HPP_

// Compilation directives
// #define USING_IMGUI

// C++ core and STL features
#include <iostream>
#include <memory>
#include <exception>
#include <type_traits>
#include <cmath>
#include <functional>
#include <random>
#include <filesystem>
#include <map>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// ImGui-SFML
#ifdef USING_IMGUI
#include <imgui-SFML.h>
#include <imgui-SFML_export.h>
#endif

// GSL
#include <gsl/gsl>

// JSON

#endif // IRIDIUM_LIBRARIES_HPP_