#pragma once
#include <string>

class Creature_DTO final
{
public:
	Creature_DTO(const std::string& type, int ttl, int x, int y, int z) : type_(type), ttl_(ttl), x_(x), y_(y), z_(z){}
	int get_x() const;
	int get_y() const;
	int get_z() const;
	int get_ttl() const;
	const std::string& get_type() const;
private:
	std::string type_;
	int ttl_;
	int x_, y_, z_;
};
