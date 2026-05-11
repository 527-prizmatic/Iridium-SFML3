# CONVENTIONS & NOMENCLATURE (EDITED 2026.05.11)

## BRACES & INDENTATION
 - All code files must be indented with tabs rather than spaces.
 - Follow the One True Brace Style.

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
