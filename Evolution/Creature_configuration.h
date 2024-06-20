#pragma once
#include "Moss.h"
#include "Plant.h"
#include "Herbivorous.h"
#include "Goat.h"
#include "Lynx.h"
#include "Predator.h"

size_t Plant::breeding_period = 20;
size_t Plant::ttl_if_eaten = 6;

size_t Moss::ttl_if_eaten = 3;
size_t Moss::breeding_period = 25;

size_t Herbivorous::ttl_breeding_level = 100;

size_t Goat::ttl_breeding_level = 300;

size_t Predator::ttl_bonus_for_eat = 10;
size_t Predator::ttl_breeding_level = 600;

size_t Lynx::ttl_bonus_for_eat = 13;