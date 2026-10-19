#include "/home/razor/Documents/raylib1/raylib/src/raylib.h"
#include "/home/razor/Documents/emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h"

#include <stdio.h>
#include <time.h>

void updateFrame(void) {
	time_t rawTime;

	time(&rawTime);

	struct tm *timeInfo = localtime(&rawTime);

	char buffer[20] = {0};

	snprintf(buffer, sizeof(buffer), "%d Days Remain!", 22 - timeInfo->tm_mday);

	Vector2 dateSize = MeasureTextEx(GetFontDefault(), buffer, 80, 1.5);

	BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText(buffer, (GetScreenWidth()/2) - dateSize.x/2, (GetScreenHeight()/2) - dateSize.y/2, 80, LIGHTGRAY);
	EndDrawing();
}


int main(void) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(800, 450, "Home Bound");

	emscripten_set_main_loop(updateFrame, 75, 1);

	CloseWindow();

	return 0;
}
