#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::shared_ptr<sf::Texture> texture, sf::Vector2u image_count, float switch_time);
	~Animation();

	void update(float delta_time);
	void set_action(int row);

	sf::IntRect uv_rect;

private:


	sf::Vector2u image_count_;
	sf::Vector2u current_image_;

	int current_row_ = 0;
	float total_time_;
	float switch_time_;

};

