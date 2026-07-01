#include "raylib.h";
#include <vector>;

int main() {
	
	int windowWidth = 1200;
	int windowHeight = 800;

	InitWindow(windowWidth, windowHeight, "Pong");
	SetTargetFPS(60);

	
	while (!WindowShouldClose()) {

		BeginDrawing();

		ClearBackground(BLACK);

		float paddleWidth = 35.0f;
		float paddleHeight = 100.0f;

		float leftXPosition = 0.0f;
		float leftYPosition = (GetScreenHeight() / 2.0f)-(paddleHeight/2);

		float rightXPosition = GetScreenWidth() - paddleWidth;
		float rightYPosition = (GetScreenHeight() / 2.0f) - (paddleHeight / 2);
		
		Vector2 mousePosition = GetMousePosition();
	
		if (mousePosition.x >= 0 && mousePosition.x <= 100) {
			leftYPosition = mousePosition.y;
		}
		else if (mousePosition.x >= rightXPosition-65 && mousePosition.x <= GetScreenWidth()) {
			rightYPosition = mousePosition.y;
		}
		
		Rectangle leftPaddle = { leftXPosition, leftYPosition, paddleWidth, paddleHeight };
		Rectangle rightPaddle = { rightXPosition, rightYPosition, paddleWidth, paddleHeight };

		DrawRectangleRec(leftPaddle, WHITE);
		DrawRectangleRec(rightPaddle, WHITE);



		EndDrawing();
	}
	CloseWindow();
}