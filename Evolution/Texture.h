#pragma once

class Texture final
{
public:
	Texture() = default;
	Texture(size_t tex):texture_ptr(tex){}
	~Texture() = default;
	void set_texture(size_t new_tex) { texture_ptr = new_tex; }
	size_t get_texture() const { return texture_ptr; }
private:
	size_t texture_ptr;
};