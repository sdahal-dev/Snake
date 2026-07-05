#include "raylib.h"
#include <vector>
#include <string>
#include <random>

int main() {

	InitWindow(800, 800, "Snake");
	SetTargetFPS(60);

	float centerX = GetScreenWidth() / 2;
	float centerY = GetScreenHeight() / 2;
	float bodyWidth = 25, bodyHeight = 25;

	Rectangle startBody = { centerX - (35 / 2), centerY - (35 / 2), bodyWidth, bodyHeight };

	bool gameStarted = false;

	Rectangle startButton = { centerX-50, centerY-25, 100, 50 };

	float textWidth = MeasureText("Start", 25);

	std::string snakeDirection = "up";

	float speed = 5.0f;

	std::random_device random_seed;
	std::mt19937 gen(random_seed());
	std::uniform_int_distribution<int> dist(bodyWidth, GetScreenWidth() - bodyWidth);

	bool ballSpawn = false;
	Vector2 ball = { dist(gen), dist(gen) };
	
	std::vector<Rectangle> snakeBody{ startBody };

	int score = 0;

	while (!WindowShouldClose()){


		Vector2 mousePosition = GetMousePosition();
		

		BeginDrawing();

		ClearBackground(BLACK);

		if (CheckCollisionPointRec(mousePosition, startButton)) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				gameStarted = true;
			}
		}
		
		if (gameStarted) {

			if (IsKeyPressed(KEY_W)) {
				snakeDirection = "up";
			}
			else if (IsKeyPressed(KEY_D)) {
				snakeDirection = "right";
			}
			else if (IsKeyPressed(KEY_S)) {
				snakeDirection = "down";
			}
			else if (IsKeyPressed(KEY_A)) {
				snakeDirection = "left";
			};

			float x = 0.0f, y = 0.0f;

			if (snakeDirection == "up") {
				y = -speed;
			}
			else if (snakeDirection == "down") {
				y = speed;
			}
			else if (snakeDirection == "right") {
				x = speed;
			}
			else {
				x = -speed;
			};

			if (!ballSpawn) {
				ball = { float(dist(gen)), float(dist(gen)) };
				ballSpawn = true;
			}
			else {
				if (CheckCollisionCircleRec(ball, 10, snakeBody[0])) {

					score++;

					ball = { float(dist(gen)), float(dist(gen)) };
					
					int length = snakeBody.size();
					Rectangle lastPart = snakeBody[length - 1];

					float currentX = lastPart.x;
					float currentY = lastPart.y;

					if (snakeDirection == "up") {
						currentY += bodyHeight;
					}
					else if (snakeDirection == "down") {
						currentY -= bodyHeight;
					}
					else if (snakeDirection == "right") {
						currentX -= bodyWidth;
					}
					else {
						currentX += bodyWidth;
					}

					Rectangle tempPart = { currentX, currentY, bodyWidth, bodyHeight };

					snakeBody.push_back(tempPart);

				}
			}

			DrawCircleV(ball, 10, RED);
			float scoreWidth = MeasureText("Score: ", 25);
			DrawText(TextFormat("Score: %d", score), 10, 10, 25, WHITE);

			std::vector<Rectangle> old = snakeBody;

			snakeBody[0].x += x;
			snakeBody[0].y += y;

			for (size_t i = snakeBody.size() - 1; i > 0; i--) {
				snakeBody[i] = old[i - 1];
			}

			if (snakeBody[0].x >= GetScreenWidth()) {
				snakeBody[0].x = 0;
			}
			else if (snakeBody[0].x < 0) {
				snakeBody[0].x = GetScreenWidth() - bodyWidth;
			}

			if (snakeBody[0].y >= GetScreenHeight()) {
				snakeBody[0].y = 0;
			}
			else if (snakeBody[0].y < 0) {
				snakeBody[0].y = GetScreenHeight() - bodyHeight;
			}
			

			for (Rectangle& bodyPart : snakeBody) {
				DrawRectangleRec(bodyPart, WHITE);
			}
		}
		else {
			DrawRectangleRec(startButton, BLUE);
			DrawText("Start", centerX-(textWidth/2), centerY-(25/2), 25, WHITE);
		}


		EndDrawing();
	}
	
	CloseWindow();
}