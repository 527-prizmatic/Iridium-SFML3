# Iridium
A C++ game engine wrapped around SFML 3.0.2, for use in small game projects. It provides a layer of abstraction for most of SFML's functions to simplify window management, assets, rendering and audio; provide alternative implementations for certain of its features; and adds numerous mathematical or graphical utilities.

All code files (.hpp, .cpp, .inl) contained in `include/Iridium` and `src/Iridium`, as well as `main.cpp`, are engine files. Project files should go in `include/Project` and `src/Project`.

**IMPORTANT: As of writing (September 2026), Iridium is an in-development project and is not yet ready for production usage. Suggestions, contributions and feedback are welcome.**

### Game States
Your entry point into the engine are game states; roughly equivalent to Unity's scenes. An example game state is provided in the `include/Project` folder, and additional ones should be created there. A bare-bones game state looks like this:

```c++
class MyState: public ir::StateBase<MyState> {
public:
	void onInitialize(); // Runs upon entering state
	void onReceiveEvent(const sf::Event& event); // Runs every frame, once for each polled sf::Event (see SFML documentation)
	void onUpdate(); // Runs every frame after onReceiveEvent
	void onRender(); // Runs every frame after onUpdate
	void onEnd(); // Runs upon exiting state
private:
	// Declare objects and subsystems here
};
```

Furthermore, game states contain the protected member `context_` which gives access to engine subsystems, such as game window (for rendering), input systems, and more.

### VMF Files
The engine's rendering utilities revolve around a minimalist vector-based API. Aside from dedicated classes for basic geometrical shapes, the engine uses the homemade VMF file format, which encodes for 2D vector models to be drawn on-screen through the `ir::render::ModelRenderer` class. A graphical editor is available on the `VmfEditorUtil` branch.

The VMF file format is structured as such:
- **Version** (1 byte, unsigned) - Denotes the current file format version. 1 as of now.
- Any number of the following blocks:
	- **Primitive type** (1 byte, unsigned) - What kind of OpenGL shape the block encodes. 0 for single point; 1 for line; 2 for triangle.
	- As many of the following blocks as required by the shape (respectively 1, 2, 3):
		- **X coordinate** (2 bytes, signed) of the point relative to the origin, in pixels.
		- **Y coordinate** (2 bytes, signed) of the point relative to the origin, in pixels. Pay attention to axis direction: in SFML, positive Y is *down*, while negative Y is *up*.
		- **RGBA color** (4 x 1 byte, unsigned). Differently-colored points on the same primitive will render as gradients.

## Tools & Techs :wrench:
- **Languages** - C++
- **IDEs** - Microsoft Visual Studio Code
- **Additional Libraries**
	- SFML v3.0.2
	- GSL 4.2.0
	- Niels Lohmann's JSON for Modern C++ v3.12.0