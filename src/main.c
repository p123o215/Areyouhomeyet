#include "/home/razor/Documents/raylib1/raylib/src/raylib.h"
#include "/home/razor/Documents/emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h"

#include <stdio.h>
#include <time.h>

void updateFrame(void) {
	time_t rawTime;

	time(&rawTime);

	struct tm *timeInfo = localtime(&rawTime);

	char buffer[20] = {0};

	snprintf(buffer, sizeof(buffer), "%d", timeInfo->tm_mday - 22);

	BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText(buffer, 190, 200, 20, LIGHTGRAY);
	EndDrawing();
}


int main(void) {
	InitWindow(800, 450, "Home Bound");

	emscripten_set_main_loop(updateFrame, 60, 1);

	CloseWindow();

	return 0;
}
