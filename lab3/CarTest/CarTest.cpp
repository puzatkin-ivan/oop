#include "stdafx.h"

#include "../Car/CCar.h"

struct CarFixture
{
public:
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
	BOOST_AUTO_TEST_CASE(engine_is_turn_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
	}
	BOOST_AUTO_TEST_CASE(speed_is_zero_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}
	BOOST_AUTO_TEST_CASE(gear_is_neutral_by_default)
	{
		BOOST_CHECK(car.GetGear() == Gear::Neutral);
	}
	BOOST_AUTO_TEST_CASE(direction_is_none_by_default)
	{
		BOOST_CHECK(car.GetDirection() == Direction::None);
	}
	BOOST_AUTO_TEST_SUITE(when_enigne_is_turn_off)
		BOOST_AUTO_TEST_CASE(cannot_turn_off_engine_twice)
		{
			BOOST_CHECK(!car.TurnOffEngine());
		}
		BOOST_AUTO_TEST_CASE(cannot_change_gear)
		{
			BOOST_CHECK(!car.SetGear(Gear::Reverse));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
			BOOST_CHECK(!car.SetGear(Gear::First));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}
		BOOST_AUTO_TEST_CASE(cannot_change_speed)
		{
			BOOST_CHECK(!car.SetSpeed(10));
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(can_turn_on_engine)
		{
			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.IsEngineTurnOn());
		}
	BOOST_AUTO_TEST_SUITE_END()
	struct when_engine_turned_on_ : CarFixture
	{
		when_engine_turned_on_()
		{
			car.TurnOnEngine();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_enigne_is_turn_on, when_engine_turned_on_)
		BOOST_AUTO_TEST_CASE(cannot_turn_on_engine_twice)
		{
			BOOST_CHECK(!car.TurnOnEngine());
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_neutral_to_first)
		{
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
			BOOST_CHECK(car.SetGear(Gear::First));
			BOOST_CHECK(car.GetGear() == Gear::First);
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_neutral_to_reverse_at_zero_speed)
		{
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
			BOOST_CHECK(car.SetGear(Gear::Reverse));
			BOOST_CHECK(car.GetGear() == Gear::Reverse);
		}
		BOOST_AUTO_TEST_CASE(cannot_change_gear_from_first_to_reverse_at_zero_speed)
		{
			BOOST_CHECK(car.SetGear(Gear::First));
			BOOST_CHECK(car.GetGear() == Gear::First);
			BOOST_CHECK(!car.SetGear(Gear::Reverse));
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_reverse_to_first_at_zero_speed)
		{
			BOOST_CHECK(car.SetGear(Gear::Reverse));
			BOOST_CHECK(car.GetGear() == Gear::Reverse);
			BOOST_CHECK(car.SetGear(Gear::First));
		}
		BOOST_AUTO_TEST_CASE(cannot_change_speed_up_on_neutral_gear)
		{
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
			BOOST_CHECK(car.GetSpeed() == 0);
			BOOST_CHECK(!car.SetSpeed(10));
		}
		BOOST_AUTO_TEST_CASE(cannot_set_speed_beyond_speed_range_gear)
		{
			BOOST_CHECK(car.SetGear(Gear::First));
			BOOST_CHECK(car.SetSpeed(30));

			BOOST_CHECK(!car.SetSpeed(31));

			BOOST_CHECK(car.SetGear(Gear::Neutral));
			BOOST_CHECK(!car.SetSpeed(31));
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_on_reverse_gear_on_while_moving_forward)
		{
			BOOST_CHECK(car.SetGear(Gear::First));
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(car.GetDirection() == Direction::Forward);
			BOOST_CHECK(car.SetGear(Gear::Neutral));
			BOOST_CHECK(!car.SetGear(Gear::Reverse));
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_on_reverse_gear_on_while_moving_reverse)
		{
			BOOST_CHECK(car.SetGear(Gear::Reverse));
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(car.GetDirection() == Direction::Reverse);
			BOOST_CHECK(car.SetGear(Gear::Neutral));
			BOOST_CHECK(!car.SetGear(Gear::Reverse));
		}
		BOOST_AUTO_TEST_CASE(can_turn_off_engine_when_car_is_standing_still)
		{
			BOOST_CHECK(car.TurnOffEngine());
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_off_engine_on_while_driving)
		{
			BOOST_CHECK(car.SetGear(Gear::First));
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(!car.TurnOffEngine());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
