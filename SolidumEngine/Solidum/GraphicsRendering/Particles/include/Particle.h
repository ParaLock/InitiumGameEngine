#pragma once
#include "../../../sysInclude.h"

struct ParticleShape {
	float top;
	float bottom;
	float left;
	float right;

	bool operator==(const ParticleShape &o) const {
		return top == o.top && bottom == o.bottom && left == o.left && right == o.right;
	}

	bool operator<(const ParticleShape &o)  const {
		return (top<o.top || bottom<o.bottom || left<o.left || right<o.right);
	}
};

class Particle
{
private:
	int _currentLifeTick;
	int _maxLife;

public:
	Particle();
	~Particle();

	Vector3f _position;
};


