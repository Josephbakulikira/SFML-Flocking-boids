#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

#include "Boid.h"

using namespace std;

class Flock
{
public:
	int width = 800;
	int height = 800;
	float hue = 0;
	Flock();
	Flock(vector<Boid>* boids);
	Flock(vector<Boid>* boids, float hue);
	
	void Simulate(sf::RenderWindow& window, int width, int height);
	void Append(Boid boid);

	vector<Boid>* GetBoids();
private:
	vector<Boid>* boids;
	
	//(*boids).push_back(Boid(sf::Vector2f(width / 2, height / 2)));
};

