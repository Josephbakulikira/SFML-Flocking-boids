#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <list>
#include "Boid.h"
#include "Flock.h"


#define WIDTH 1920
#define HEIGHT 1080
#define SIZE 100
#define RADIUS 10

using namespace std;

int RandomIntegers(int minimum, int maximum);

int main() {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Flocking(Boid) Quadtree", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	
	vector<Flock> flocks;

	for (int i = 0; i < 3; i++)
	{

		Flock flock;
		flock.hue = i*50;
		for (int i = 0; i < SIZE; i++)
		{
			int x = RandomIntegers(RADIUS, WIDTH);
			int y = RandomIntegers(RADIUS, HEIGHT);
			sf::Vector2f randompos = sf::Vector2f(x, y);
			sf::Vector2f centerPos = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
			flock.Append(Boid(randompos, RADIUS));
		}
		flocks.push_back(flock);
	}

	while (window.isOpen()) {
		window.clear();
		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		for (int i = 0; i < 3; i++)
		{
			flocks[i].Simulate(window, WIDTH, HEIGHT);
		}
		
		
		window.display();
	}

	return 0;
}

int RandomIntegers(int minimum, int maximum) {
	int range = maximum - minimum + 1;
	return rand() % range + minimum;
}

