#include "network.hpp"
#include "bird.hpp"
#include "Tubes.hpp"
//#define POPULATION_SIZE = 10

using std::array;
using std::minstd_rand;
using std::uniform_int_distribution;
using std::move;
using std::to_string;

float speed = -1.4, scale;
int index_tube, dead_birds, gameover_birds, current_bird;

auto initScenary(Texture &tex)
{
	minstd_rand rand_gen(time(0));

	tex.loadFromFile("C:\\Users\\Aluno\\Desktop\\Dino-IA\\flappy-bird.png");
	Sprite background(tex, IntRect(0, 0, 144, 256));

	Vector2u window_s = Vector2u(378, 819);
	{
		auto [a, b, w_b, h_b] = background.getTextureRect();
		auto [w_w, h_w] = window_s;
		scale = (float(w_w / h_w) < float(w_b / h_b) ? float(w_w / w_b) : float(h_w / h_b));
		a--;
		b++;
	}

	background.scale(scale, scale);

	array<Sprite, 2> terrain{
		Sprite(tex, IntRect(146, 0, 154, 56)),
		Sprite(tex, IntRect(146, 0, 154, 56))};

	for (int i = 0; i < 2; i++)
	{
		terrain.at(i).scale(scale, scale);
		terrain.at(i).setPosition(terrain.at(i).getGlobalBounds().width * i, window_s.y - terrain.at(i).getGlobalBounds().height);
	}

	Tube::setOpeningSize(scale * Tube::getOpeningSize());

	uniform_int_distribution<int> rand_dist(Tube::getOpeningSize() * 1.2, window_s.y - terrain.at(0).getGlobalBounds().height - Tube::getOpeningSize() * 1.2);

	array<Tube, 3> tubes{
		Tube(tex, scale, Vector2f(window_s.x * 1.5, rand_dist(rand_gen))),
		Tube(tex, scale, Vector2f(window_s.x * 2, rand_dist(rand_gen))),
		Tube(tex, scale, Vector2f(window_s.x * 2.5, rand_dist(rand_gen)))};
	return make_tuple(rand_gen, move(background), move(terrain), move(rand_dist), move(tubes));
}

array<float, 2> getNextTube (array<Tube, 3> tubes, Bird player) {
		return array<float, 2> {tubes.at(index_tube % 3).getPosition().x - player.getPosition().x, tubes.at(index_tube % 3).getPosition().y - player.getPosition().y};
};