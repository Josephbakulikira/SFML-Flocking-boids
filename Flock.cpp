#include "Flock.h"
Flock::Flock() {
	this->boids = new vector<Boid>;
}

Flock::Flock(vector<Boid>* boids) {
	this->boids = boids;
}
Flock::Flock(vector<Boid>* boids, float hue) {
	this->boids = boids;
	this->hue = hue;
}
void Flock::Simulate(sf::RenderWindow& window, int width, int height) {
	
	for (int i = 0; i < (*boids).size(); i++)
	{
		(*boids)[i].Run(boids, width, height);
		(*boids)[i].Render(window, hue);

	}
	hue++;
}

void Flock::Append(Boid boid) {
	
	(*boids).push_back(boid);
}



vector<Boid>* Flock::GetBoids() {
	return this->boids;
}

