# CONVENTIONS & NOMENCLATURE (EDITED 2026.05.11)

## FRAMEWORK
 - CMake version 3.15 or newer.
 - C++23 (as established in the root-level CMakeLists.txt file).
 - clang with compile flags -Wall, -Wextra, -Wpedantic, -Werror.
 - All warnings should be treated as errors.

## HIERARCHY
 - All .hpp files in a subfolder of "include/iridium".
 - All .inl files in a subfolder of "include/iridium/detail", mirroring the implemented file's path (for instance, implement "include/iridium/foo/bar.hpp" in "include/iridium/detail/foo/bar.inl").
 - All .cpp files in a subfolder of "src/iridium".
 - Prefer include guards over #pragma once.
   - Include guard names should follow the nomenclature IRIDIUM_SUBFOLDER_FILE_EXTENSION_. For instance, "include/iridium/foo/bar.hpp" should use IRIDIUM_FOO_BAR_HPP_.

## INDENTATION
 - All code files must be indented with tabs rather than spaces.
 - Follow the One True Brace Style.
 - Spaces should be added:
   - After but not before commas and semicolons.
   - Before and after operators, except . and ->.
   - After but not before &, && and * when declaring variables.
   - Never after & and * when de/referencing variables.
   - Never before or after round, square or angle braces.
   - Always before and after curly braces, unless at the start/end of a line respectively.
   - Always between a control statement and the following condition.

## ITEM NAMING
 - Do not encode type information in names (no `int iValue`).
 - File and folder names in snake_case.
   - .hpp for header files.
   - .cpp for source files.
   - .inl for inline files.
 - Class and struct names in PascalCase.
 - Variable names in camelCase.
 - Function names in camelCase.
 - Namespace names in snake_case.
   - All namespaces should be part of the top-level namespace **iridium**.
   - Use namespace **detail** for internal implementation.
 - Private class members use a trailing underscore.
 - Static constants begin with **k** (as in **kArraySize**), except in obvious mathematical or physical constants (**pi** or **euler** is fine).
 - Global variables begin with **g** (as in **gInstance**).
