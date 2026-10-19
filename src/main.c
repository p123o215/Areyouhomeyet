#include "/home/razor/Documents/raylib1/raylib/src/raylib.h"
#include "/home/razor/Documents/emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h"

#include <stdio.h>
#include <time.h>

void updateFrame(void) {
	time_t rawTime;

	time(&rawTime);

	struct tm *timeInfo = localtime(&rawTime);

	char buffer[20] = {0};

	snprintf(buffer, sizeof(buffer), "%d", 22 - timeInfo->tm_mday);

	BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText(buffer, GetScreenWidth()/2, GetScreenHeight()/2, 80, LIGHTGRAY);
	EndDrawing();
}


int main(void) {
	int width = GetScreenWidth();
	int height = GetScreenHeight();

	InitWindow(width, height, "Home Bound");

	emscripten_set_main_loop(updateFrame, 60, 1);

	CloseWindow();

	return 0;
}
