#include "/home/razor/Documents/raylib1/raylib/src/raylib.h"
#include "/home/razor/Documents/emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h"

#include <stdio.h>
#include <time.h>

bool animation = false;
double y;

typedef struct {
	double x;
	double y;

	Color color;
} Confetti;

Confetti confArray[100];

void updateFrame(void) {
	char cookieBuffer[20];

	cookieBuffer[0] = '\0';

	// Get remaining time cookie
	EM_ASM({{
		let buffer = $0;
		let bufferSize = $1;

		let cookie = document.cookie.split(';');

		let cookieString = "";

		for (let i = 0; i < cookie.length; i++) {
			let currentCookie = cookie[i].trim();

			if (currentCookie.startsWith("remaining=")) {
				stringToUTF8(currentCookie.substring(10), buffer, bufferSize);
				break;
			}
		}
	}}, cookieBuffer, sizeof(cookieBuffer));

	time_t rawTime;

	time(&rawTime);

	struct tm *timeInfo = localtime(&rawTime);

	char buffer[20] = {0};

	snprintf(buffer, sizeof(buffer), "%d Days Remain!", 22 - timeInfo->tm_mday);

	bool newDay = false;

	if (cookieBuffer[0] != buffer[0]) {
		newDay = true;
		animation = true;

		y = 0;

		for (int i = 0; i < 100; i++) {
			confArray[i].x = GetRandomValue(1, GetScreenWidth());
			confArray[i].y = GetRandomValue(-250, GetScreenHeight());

			int value = GetRandomValue(1, 3);

			if (value == 1) {
				confArray[i].color = BLUE;
			} else if (value == 2) {
				confArray[i].color = RED;
			} else {
				confArray[i].color = PURPLE;
			}
		}
	}

	// Set remaining time cookie
	EM_ASM({{
		let name = UTF8ToString($0);

		let d = new Date();

		d.setTime(d.getTime() + (4 * 24 * 60 * 60 * 1000));

		let expires = "expires=" + d.toUTCString();

		document.cookie = "remaining=" + name[0] + ";" + expires + ";path=/";
	}}, buffer);

	Vector2 dateSize = MeasureTextEx(GetFontDefault(), buffer, 80, 1.5);

	BeginDrawing();
		ClearBackground(RAYWHITE);

		if (newDay || animation) {
			for (int confettiPiece = 0; confettiPiece < 100; confettiPiece++) {
				if (y <= GetScreenHeight()) {
					DrawRectangle(confArray[confettiPiece].x, confArray[confettiPiece].y, 10, 5, confArray[confettiPiece].color);
				} else {
					animation = false;
				}

				confArray[confettiPiece].y += 2.5;
			}

			y += 2.5;
		}

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
