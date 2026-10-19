#include "/home/razor/Documents/raylib1/raylib/src/raylib.h"
#include "/home/razor/Documents/emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h"

void updateFrame(void) {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);
	EndDrawing();
}


int main(void) {
	InitWindow(800, 450, "Home Bound");

	emscripten_set_main_loop(updateFrame, 60, 1);

	CloseWindow();

	return 0;
}
