#pragma once

class Animations_list {

public:
	Animations_list() = default;
	void set_action(std::string type, int row, int size)
	{
		animations_list_.at(type).first = row;
		animations_list_.at(type).second= size;
	}
	std::pair<int, int> get_action(std::string type)
	{
		return animations_list_.at(type);
	}
private:
	std::map<std::string, std::pair<int, int>> animations_list_
	{
		{"Stand",{0,0}},
		{"Move_up",{0,0}},
		{"Move_up_right",{0,0}},
		{"Move_right",{0,0}},
		{"Move_down_right",{0,0}},
		{"Move_down",{0,0}},
		{"Move_down_left",{0,0}},
		{"Move_left",{0,0}},
		{"Move_up_left",{0,0}},
		{"Eat",{0,0}},
		{"Sleep",{0,0}}
	};
};