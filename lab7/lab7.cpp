// lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(450, 150));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(.5, .3));

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 1200));
	leftWall.setCenter(Vector2f(790, 590));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 1200));
	rightWall.setCenter(Vector2f(10, 590));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	PhysicsRectangle top;
	top.setSize(Vector2f(900, 20));
	top.setCenter(Vector2f(400, 10));
	top.setStatic(true);
	world.AddPhysicsBody(top);

	PhysicsRectangle target;
	target.setSize(Vector2f(100, 100));
	target.setCenter(Vector2f(400, 300));
	target.setStatic(true);
	world.AddPhysicsBody(target);
	bool hit = false;
	target.onCollision = [&hit](PhysicsBodyCollisionResult result) {
			hit = true;
		};

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
			cout << "thud " << thudCount << endl;
			thudCount++;
		};

	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	top.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	int bangCount(0);
	target.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;

		int hitCount = 3;
		if (bangCount >= hitCount) {
				cout << "Game Over!" << endl;
				exit(0);
			}
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(top);
		window.draw(target);
		window.display();
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
