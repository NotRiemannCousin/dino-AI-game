#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <random>

#define RAD_TO_DEGREES 57.2957795
#define SQRT_3 1.732050

using namespace sf;
using std::min, std::max;
class Bird : public Sprite
{
	float i = 0, t = 0, r = 6; // thrust = 3.6;

	float funcPos(float x)
	{
		return 3 * x * x - 2 * x * x * x;
	}
	float derivatedFuncPos(float x)
	{
		return 6 * x - 7 * x * x;
	}

public:
	Bird(){};
	Bird(Texture &tex, float scale, Vector2f pos) : Sprite(tex, IntRect(265, 64, 17, 12))
	{
		r = r * scale;
		this->scale(scale, scale);
		this->setPosition(pos);
		this->setOrigin(this->getTextureRect().width / 2, this->getTextureRect().height / 2);
	}
	void update()
	{
		/*i = max(0.0, i -0.2);
		t = clamp(t - 0.01f, -1.23394491f, 0.1067950f);

		this->setRotation(min(atan(-derivatedFuncPos(t)) * RAD_TO_DEGREES + 12-i, 90.0));
		this->move(0, -derivatedFuncPos((t -0.03)*5) - i);
		*/
		t = t - 0.07f;
		float t_base = min(max(t, -0.9f), 0.2f);

		i = i - 0.68f;
		float i_base = min(max(i, -25.0f), 10.0f);

		this->setRotation(-t_base * 100);
		this->move(0, t_base * 1.2 - i_base);
	}
	void deadUpdate(float speed)
	{
		this->move(speed, 0);
	}
	void flap()
	{
		t = 1.7, i = 12.5;
	}
	bool checkColision(FloatRect rect)
	{
		Vector2f circleDistance = Vector2f(abs(this->getPosition().x - rect.left - rect.width / 2), abs(this->getPosition().y - rect.top - rect.height / 2));

		if (circleDistance.x > (rect.width / 2 + r))
		{
			return false;
		}
		if (circleDistance.y > (rect.height / 2 + r))
		{
			return false;
		}

		if (circleDistance.x <= (rect.width / 2))
		{
			return true;
		}
		if (circleDistance.y <= (rect.height / 2))
		{
			return true;
		}

		float cornerDistance_sq = powf(circleDistance.x - rect.width / 2, 2) +
								  powf(circleDistance.y - rect.height / 2, 2);

		return cornerDistance_sq < powf(r, 2);
	}
	float getRadius()
	{
		return r;
	}
	void kill()
	{
		t = 0;
		i = 5;
	}
};