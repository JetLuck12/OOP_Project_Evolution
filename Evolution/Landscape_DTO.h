#pragma once
#include <string>

class Landscape_DTO final
{
public:
	Landscape_DTO(const std::string& type, int x, int y) : type_(type), x_(x), y_(y){}
	const std::string& get_type() const { return type_; }
	int get_x() const { return x_; }
	int get_y() const { return y_; }
private:
	std::string type_;
	int x_, y_;
};
