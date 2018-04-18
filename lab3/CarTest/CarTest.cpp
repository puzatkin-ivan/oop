#include "stdafx.h"

#include "../Car/CCar.h"

struct CarFixture
{
	CCar car;

	void VerifyTurnOnGear(Gear currentGear, Gear expectedGear, bool successOperation)
	{
		BOOST_CHECK(car.GetGear() == currentGear);
		BOOST_CHECK(car.SetGear(expectedGear) == successOperation);
	}

	void VerifySetSpeed(Gear currentGear, int speed, bool successOperation)
	{
		BOOST_CHECK(car.GetGear() == currentGear);
		BOOST_CHECK(car.SetSpeed(speed) == successOperation);
	}
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
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, false);
			VerifyTurnOnGear(Gear::Neutral, Gear::First, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_change_speed)
		{
			VerifySetSpeed(Gear::Neutral, 10, false);
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
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_neutral_to_reverse_at_zero_speed)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, true);
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_first_to_reverse_at_zero_speed)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifyTurnOnGear(Gear::First, Gear::Reverse, true);
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_reverse_to_first_at_zero_speed)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, true);
			VerifyTurnOnGear(Gear::Reverse, Gear::First, true);
		}
		BOOST_AUTO_TEST_CASE(cannot_change_speed_up_on_neutral_gear)
		{
			VerifySetSpeed(Gear::Neutral, 10, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_set_speed_beyond_speed_range_first_gear)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 30, true);
			VerifySetSpeed(Gear::First, 31, false);

			VerifyTurnOnGear(Gear::First, Gear::Neutral, true);
			VerifySetSpeed(Gear::Neutral, 31, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_set_speed_beyond_speed_range_second_gear)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 30, true);
			VerifyTurnOnGear(Gear::First, Gear::Second, true);
			VerifySetSpeed(Gear::Second, 19, false);
			VerifySetSpeed(Gear::Second, 51, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_set_speed_beyond_speed_range_third_gear)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 30, true);
			VerifyTurnOnGear(Gear::First, Gear::Second, true);
			VerifySetSpeed(Gear::Second, 40, true);
			VerifyTurnOnGear(Gear::Second, Gear::Third, true);
			VerifySetSpeed(Gear::Third, 29, false);
			VerifySetSpeed(Gear::Third, 61, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_set_speed_beyond_speed_range_fourth_gear)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 30, true);
			VerifyTurnOnGear(Gear::First, Gear::Second, true);
			VerifySetSpeed(Gear::Second, 40, true);
			VerifyTurnOnGear(Gear::Second, Gear::Third, true);
			VerifyTurnOnGear(Gear::Third, Gear::Fourth, true);
			VerifySetSpeed(Gear::Fourth, 39, false);
			VerifySetSpeed(Gear::Fourth, 91, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_set_speed_beyond_speed_range_fifth_gear)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 30, true);
			VerifyTurnOnGear(Gear::First, Gear::Second, true);
			VerifySetSpeed(Gear::Second, 40, true);
			VerifyTurnOnGear(Gear::Second, Gear::Third, true);
			VerifyTurnOnGear(Gear::Third, Gear::Fourth, true);
			VerifySetSpeed(Gear::Fourth, 60, true);
			VerifyTurnOnGear(Gear::Fourth, Gear::Fifth, true);
			VerifySetSpeed(Gear::Fifth, 49, false);
			VerifySetSpeed(Gear::Fifth, 151, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_on_reverse_gear_on_while_moving_forward)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 30, true);
			BOOST_CHECK(car.GetDirection() == Direction::Forward);
			VerifyTurnOnGear(Gear::First, Gear::Neutral, true);
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_on_reverse_gear_on_while_moving_reverse)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, true);
			VerifySetSpeed(Gear::Reverse, 10, true);
			BOOST_CHECK(car.GetDirection() == Direction::Reverse);
			VerifyTurnOnGear(Gear::Reverse, Gear::Neutral, true);
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_on_first_gear_on_while_moving_reverse)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::Reverse, true);
			VerifySetSpeed(Gear::Reverse, 10, true);
			VerifyTurnOnGear(Gear::Reverse, Gear::Neutral, true);
			BOOST_CHECK(car.GetDirection() == Direction::Reverse);
			VerifyTurnOnGear(Gear::Neutral, Gear::First, false);
			VerifySetSpeed(Gear::Neutral, 0, true);
			BOOST_CHECK(car.GetDirection() == Direction::None);
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
		}
		BOOST_AUTO_TEST_CASE(can_turn_off_engine_when_car_is_standing_still)
		{
			BOOST_CHECK(car.TurnOffEngine());
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_off_engine_on_while_driving)
		{
			VerifyTurnOnGear(Gear::Neutral, Gear::First, true);
			VerifySetSpeed(Gear::First, 10, true);
			BOOST_CHECK(!car.TurnOffEngine());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
