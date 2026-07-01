#include "raylib.h";
#include <vector>;
#include <string>;

int main() {
	
	int windowWidth = 1200;
	int windowHeight = 800;

	InitWindow(windowWidth, windowHeight, "Pong");
	SetTargetFPS(60);

	
	float paddleWidth = 35.0f;
	float paddleHeight = 100.0f;

	float leftXPosition = 0.0f;
	float leftYPosition = (GetScreenHeight() / 2.0f) - (paddleHeight / 2);

	float rightXPosition = GetScreenWidth() - paddleWidth;
	float rightYPosition = (GetScreenHeight() / 2.0f) - (paddleHeight / 2);

	float ballX = GetScreenWidth() / 2;
	float ballY = GetScreenHeight() / 2;

	Vector2 ball = { ballX, ballY };
	std::pair<float, float> ballSpeed{ 8.0f, 5.0f };

	int score = 0;
	bool gameEnded = false;

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(BLACK);
		
		if (!gameEnded) {
			Vector2 mousePosition = GetMousePosition();

			if (mousePosition.x < GetScreenWidth() - mousePosition.x) {

				leftYPosition = mousePosition.y;

			}
			else {

				rightYPosition = mousePosition.y;

			}

			Rectangle leftPaddle = { leftXPosition, leftYPosition, paddleWidth, paddleHeight };
			Rectangle rightPaddle = { rightXPosition, rightYPosition, paddleWidth, paddleHeight };

			ball.x += ballSpeed.first;
			ball.y += ballSpeed.second;

			if (CheckCollisionCircleRec(ball, 30, leftPaddle) || CheckCollisionCircleRec(ball, 30, rightPaddle)) {

				ballSpeed.first *= -1;
				score++;

			}
			else if (ball.y + 30 >= GetScreenHeight() || ball.y - 30 <= 0) {

				ballSpeed.second *= -1;

			}
			else if (ball.x + 30 >= GetScreenWidth() || ball.x + -30 <= 0) {

				ballSpeed.first = 0;
				ballSpeed.second = 0;
				gameEnded = true;


			}
			DrawRectangleRec(leftPaddle, WHITE);
			DrawRectangleRec(rightPaddle, WHITE);
			DrawCircleV(ball, 30.0f, BLUE);
			DrawText(std::to_string(score).c_str(), GetScreenWidth() / 2, 5, 40, WHITE);
		}
		else {

			int textWidth = MeasureText("Game Over", 100);
			DrawText("Game Over", GetScreenWidth() / 2 - textWidth/2, GetScreenHeight() / 2 - 50, 100, WHITE);

			Rectangle restartButton = { GetScreenWidth() / 2 - 70, GetScreenHeight() / 2 + 75, 140, 50 };
			DrawRectangleRec(restartButton, BLUE);

			int textTwoWidth = MeasureText("Restart", 25);
			DrawText("Restart", GetScreenWidth() / 2-textTwoWidth/2, GetScreenHeight() / 2 + 85, 25, WHITE);

			Vector2 mousePosition = GetMousePosition();

			if (CheckCollisionPointRec(mousePosition, restartButton)) {

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					gameEnded = false;
					score = 0;

					ball.x = GetScreenWidth() / 2;
					ball.y = GetScreenHeight() / 2;

					ballSpeed = { 8.0f, 5.0f };
				}
			}


		}

		EndDrawing();
	}
	CloseWindow();
}