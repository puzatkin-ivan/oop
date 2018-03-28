#pragma once
#include <map>
#include <utility>

using SpeedRange = std::pair<unsigned, unsigned>;

static const unsigned MIN_SPEED = 0;
static const unsigned MAX_SPEED = 150;

enum class Direction
{
	Reverse = -1,
	None = 0,
	Forward,
};

enum class Gear
{
	Reverse = -1,
	Neutral = 0,
	First,
	Second,
	Third,
	Fourth,
	Fifth,
};

static const std::map<Gear, SpeedRange> MapSpeed = {
	{ Gear::Reverse, { 0, 20 } },
	{ Gear::Neutral, { 0, 150 } },
	{ Gear::First, { 0, 30 } },
	{ Gear::Second, { 20, 50 } },
	{ Gear::Third, { 30, 60 } },
	{ Gear::Fourth, { 40, 90 } },
	{ Gear::Fifth, { 50, 150} },
};