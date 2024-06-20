#pragma once
#include <exception>

class memory_problems final : public std::exception
{
	const char* what() const override { return "Memory not allocate"; }
};



class Parser_exc : public std::exception
{
	const char* what() const override { return "Bad line!"; }
};



class Builder_exc : public std::exception
{
	const char* what() const override { return "Undefined creature!"; }
};

class Undef_land final : public Builder_exc
{
	const char* what() const override { return "Undefined landscape!"; }
};

class Wrong_size_exc final : public Builder_exc
{
	const char* what() const override { return "Wrong size of field"; }
};

class few_lands_exc final : public Builder_exc
{
	const char* what() const override { return "Not enough landscape"; }
};

class Bad_numbers final : public Builder_exc
{
	const char* what() const override { return "Numbers are negative!"; }
};



class Field_exc : public std::exception
{
	const char* what() const override { return "Undefined creature!"; }
};

class Wrong_coords  final : public Field_exc
{
	const char* what() const override { return "Wrong coordinate of creature"; }
};

class Double_resize final : public Field_exc
{
	const char* what() const override { return "You can not change size of field"; }
};

class Bad_creature final : public Field_exc
{
	const char* what() const override { return "Pointer not found"; }
};


class List_exc : public std::exception
{
	const char* what() const override { return "List problems"; }
};

class Unfound_creature : public List_exc
{
	const char* what() const override { return "Creature not found"; }
};