#include "Boid.h"

Boid::Boid(){
	position = sf::Vector2f(0.0f, 0.0f);
	acceleration = sf::Vector2f(0.0f, 0.0f);
}

Boid::Boid(sf::Vector2f position){
	this->position = position;
	this->radius = 10.0f;
	this->acceleration = sf::Vector2f(0, 0);
}
Boid::Boid(sf::Vector2f position, float radius) {
	this->position = position;
	this->radius = radius;
	this->acceleration = sf::Vector2f(0, 0);
}

void Boid::ApplyForce(sf::Vector2f force) {
	acceleration = acceleration + force;
}
sf::Vector2f Boid::GetPosition() {
	return position;
}
void Boid::SetPosition(sf::Vector2f new_position) {
	position = new_position;
}

void Boid::Flocking(vector<Boid>* boids) {
	sf::Vector2f r_separation = Separate(boids);
	sf::Vector2f r_alignment = Align(boids);
	sf::Vector2f r_cohesion = Cohesion(boids);

	r_separation *= separation;
	r_alignment *= alignment;
	r_cohesion *= cohesion;

	ApplyForce(r_separation);
	ApplyForce(r_alignment);
	ApplyForce(r_cohesion);
}

void Boid::Update() {
	velocity = velocity + acceleration;
	velocity = Limit(velocity, maxSpeed);
	position = position + velocity;
	acceleration = sf::Vector2f(0, 0);
	angle = Heading(velocity, true) + 90;
}

sf::Vector2f Boid::Separate(vector<Boid>* boids) {
	sf::Vector2f steering = sf::Vector2f(0, 0);
	int total = 0;
	float desired_separation = separationValue;

	for (int i = 0; i < (*boids).size(); i++)
	{
		float d = GetDistance(position, (*boids)[i].GetPosition());
		if (d > 0 && d < desired_separation) {
			sf::Vector2f difference = position - (*boids)[i].GetPosition();
			difference = Normalize(difference);
			difference = difference / d;
			steering = steering + difference;
			total++;
		}
	}
	
	float len = Magnitude(steering);
	if (len > 0) {
		steering = Normalize(steering);
		steering = steering * maxSpeed;
		steering = steering - velocity;
		steering = Limit(steering, maxForce);
	}
	return steering;

}
sf::Vector2f Boid::Align(vector<Boid>* boids) {
	int total = 0;
	sf::Vector2f steering = sf::Vector2f(0.0f, 0.0f);
	float neighbourDistance = alignmentValue;

	for (int i = 0; i < (*boids).size(); i++)
	{
		float d = GetDistance(position, (*boids)[i].GetPosition());
		if (d > 0 && d < neighbourDistance) {
			steering += (*boids)[i].velocity;
			total++;
		}
	}
	if (total > 0) {
		steering /= (float)total;
		steering = Normalize(steering);
		steering *= maxSpeed;
		steering -= velocity;
		steering = Limit(steering, maxForce);
		return steering;
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}

}
sf::Vector2f Boid::Cohesion(vector<Boid>* boids) {
	float neighbourDistance = cohesionValue;
	int total = 0;
	sf::Vector2f steering = sf::Vector2f(0.0f, 0.0f);

	for (int i = 0; i < (*boids).size(); i++)
	{
		float d = GetDistance(position, (*boids)[i].GetPosition());
		if (d > 0 && d < neighbourDistance) {
			steering += (*boids)[i].position;
			total++;
		}
	}

	if (total > 0) {
		steering /= (float)total;
		return Seek(steering);
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}

}

sf::Vector2f Boid::Seek(sf::Vector2f target) {
	sf::Vector2f t = target - position;
	t = Normalize(t);
	t *= maxSpeed;
	sf::Vector2f steer = t - velocity;
	steer = Limit(steer, maxForce);
	return steer;
}
void Boid::Boundary(int width , int height) {
	if (position.x < -radius)
		position.x = width + radius;
	if (position.y < -radius)
		position.y = height + radius;

	if (position.x > width + radius)
		position.x = -radius;
	if (position.y > height + radius)
		position.y = -radius;
}

void Boid::SetColor(sf::Color color) {
	this->color = color;
}

sf::Color Boid::GetColor() {
	return color;
}


float Boid::SQMagnitude(sf::Vector2f vec) {
	return vec.x * vec.x + vec.y * vec.y;
}
float Boid::Magnitude(sf::Vector2f vec) {
	return sqrt(SQMagnitude(vec));
}
float Boid::GetDistanceSQ(sf::Vector2f vec1, sf::Vector2f vec2) {
	return (vec2.x - vec1.x) * (vec2.x - vec1.x) - (vec2.y - vec1.y) * (vec2.y - vec1.y);
}

float Boid::GetDistance(sf::Vector2f vec1, sf::Vector2f vec2) {
	return sqrt(GetDistanceSQ(vec1, vec2));
}

sf::Vector2f Boid::Normalize(sf::Vector2f vec) {
	float mag = Magnitude(vec);
	if (mag != 0) {
		return sf::Vector2f(vec.x / mag, vec.y / mag);
	}
	return vec;
}

sf::Color Boid::HSVColor(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

sf::Vector2f Boid::Limit(sf::Vector2f vec, float max_len) {
	float magSq = SQMagnitude(vec);
	sf::Vector2f tempor = vec;
	if (magSq > (max_len * max_len)) {
		tempor = Normalize(vec);
		tempor = tempor * max_len;
	}
	return tempor;
}
double Boid::Heading(sf::Vector2f vec, bool toDegrees) {
	double theta = atan2(vec.y, vec.x);
	// in radians
	if (toDegrees) {
		theta = theta * (180 / PI);
	}
	return theta;
}

void Boid::Run(vector<Boid>* boids, int width, int height) {
	Flocking(boids);
	Update();
	Boundary(width, height);
}

void Boid::Render(sf::RenderWindow& window, float hue) {
	//angle = Heading(position, true) + 90;
	color = HSVColor(hue, 100, 100);
	sf::CircleShape shape = sf::CircleShape(radius, 3);
	shape.setRotation(angle);
	shape.setPosition(position);
	shape.setFillColor(color);
	window.draw(shape);
}

float Boid::GetSeparationValue() {
	return this->separationValue;
}
float Boid::GetAlignmentValue() {
	return this->alignmentValue;
}
float Boid::GetCohesionValue() {
	return this->cohesionValue;
}

void Boid::SetSeparationValue(float value) {
	this->separationValue = value;
}
void Boid::SetAlignmentValue(float value) {
	this->alignmentValue = value;
}
void Boid::SetCohesionValue(float value) {
	this->cohesionValue = value;
}

float Boid::GetSeparation() {
	return this->separation;
}
float Boid::GetAlignment() {
	return this->alignment;
}
float Boid::GetCohesion() {
	return this->cohesion;
}

void Boid::SetSeparation(float value) {
	this->separation = value;
}
void Boid::SetAlignment(float value) {
	this->alignment = value;
}
void Boid::SetCohesion(float value) {
	this->cohesion = value;
}

