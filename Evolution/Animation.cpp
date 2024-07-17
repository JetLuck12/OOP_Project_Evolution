#include "Animation.h"

Animation::Animation(std::shared_ptr<sf::Texture> texture, sf::Vector2u image_count, float switch_time)
{
	image_count_ = image_count;
	switch_time_ = switch_time;
	total_time_ = 0.0f;
	current_image_.x = 0;

	uv_rect.width = texture->getSize().x / float(image_count.x);
	uv_rect.height = texture->getSize().y / float(image_count.y);

}

void Animation::update(float delta_time)
{
	current_image_.y = current_row_;
	total_time_ += delta_time;

	if(total_time_ >= switch_time_)
	{
		total_time_ -= switch_time_;
		current_image_.x++;

		if(current_image_.x > image_count_.x)
		{
			current_image_.x = 0;
		}

	}

	uv_rect.left = current_image_.x * uv_rect.width;
	uv_rect.top = current_image_.y * uv_rect.height;
}

void Animation::set_action(int row)
{
	current_row_ = row;
}
