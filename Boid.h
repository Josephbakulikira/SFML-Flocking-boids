#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

//template<typename T>
class Boid
{
public:
	
	Boid();
	Boid(sf::Vector2f position);
	Boid(sf::Vector2f position, float radius);

	void Run(vector<Boid>* boids, int width, int height);
	void ApplyForce(sf::Vector2f force);
	void Flocking(vector<Boid>* boids);
	void Update();
	void Boundary(int width, int height);
	void Render(sf::RenderWindow& window, float hue);

	void SetPosition(sf::Vector2f new_position);
	void SetColor(sf::Color color);

	sf::Color GetColor();

	sf::Vector2f Separate(vector<Boid>* boids);
	sf::Vector2f Align(vector<Boid>* boids);
	sf::Vector2f Cohesion(vector<Boid>* boids);
	sf::Vector2f Limit(sf::Vector2f vec, float max_len);
	sf::Vector2f Seek(sf::Vector2f target);
	sf::Vector2f Normalize(sf::Vector2f vec);
	sf::Vector2f GetPosition();

	float SQMagnitude(sf::Vector2f vec);
	float Magnitude(sf::Vector2f vec);
	float GetDistance(sf::Vector2f vec1, sf::Vector2f vec2);
	float GetDistanceSQ(sf::Vector2f vec1, sf::Vector2f vec2);
	double Heading(sf::Vector2f vec, bool inDegrees);

	float GetSeparationValue();
	float GetAlignmentValue();
	float GetCohesionValue();

	void SetSeparationValue(float value);
	void SetAlignmentValue(float value);
	void SetCohesionValue(float value);

	float GetSeparation();
	float GetAlignment();
	float GetCohesion();

	void SetSeparation(float value);
	void SetAlignment(float value);
	void SetCohesion(float value);
	
	sf::Color HSVColor(int hue, float sat, float val);
	
	
private:
	const double PI = 3.14159265358;
	const double TWO_PI = 6.28318530718;
	double angle = TWO_PI * rand() / (RAND_MAX + 1);
	float radius=2;
	sf::Color color = sf::Color(255, 255, 255);
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f velocity = sf::Vector2f((float)cos(angle),(float) sin(angle));

	float maxSpeed = 2.0f;
	float maxForce = 0.03f;

	float separationValue = 25.0f;
	float alignmentValue = 50.0f;
	float cohesionValue = 50.0f;

	float separation = 1.2f;
	float alignment = 1.0f;
	float cohesion = 1.0f;


};

