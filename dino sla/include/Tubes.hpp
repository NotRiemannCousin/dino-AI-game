#include <SFML/Graphics.hpp>
#include <array>

using namespace sf;
class Tube : public Drawable
{
	static int opening_size;
	std::array<Sprite, 2> spr;
	Vector2f pos;

  public:
	Tube(Texture &tex, int scale, Vector2f pos) : spr{Sprite(tex, IntRect(302, 0, 26, 183)), Sprite(tex, IntRect(330, 0, 26, 183))}
	{
		this->pos = pos;
		for (int i = 0; i < 2; i++)
		{
			spr[i].scale(scale, scale);
			spr[i].setPosition(pos.x - spr[i].getGlobalBounds().width/2, pos.y + (i ? opening_size / 2 : -spr[0].getGlobalBounds().height - opening_size / 2));
		}
	}
	void setTexture(Texture &t)
	{
		for (auto &s : spr)
			s.setTexture(t);
	}
	void update(float speed)
	{
		pos.x += speed;
		for (auto &s : spr)
			s.move(speed, 0);
	}
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		target.draw(spr[0], states);
		target.draw(spr[1], states);
	}
	Vector2f getPosition() { return pos; }
	float getScale() { return spr[0].getScale().y; }
	static int getOpeningSize() { return opening_size; }
	
	static void setOpeningSize(int new_value)
	{
		opening_size = new_value;
	}
	
	float getWidth() { return spr[0].getGlobalBounds().width; }
	std::array<Sprite, 2> getSprites()
	{
		return {{spr[0], spr[1]}};	}
};
int Tube::opening_size = 43;