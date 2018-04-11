#include "stdafx.h"
#include "../Car/CCar.h"
#include "../Car/CCarController.h"

struct CarControlDependencies
{
	CCar car;
	std::stringstream input;
	std::stringstream output;
};

struct CarContolFixture : CarControlDependencies
{
	CCarController carControl;

	CarContolFixture()
		: carControl(car, input, output)
	{
	}

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		input = std::stringstream();
		output = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(carControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car_Control, CarContolFixture)
	BOOST_AUTO_TEST_CASE(can_give_information_about_car_which_is_set_by_default)
	{
		VerifyCommandHandling("Info", "Engine is turned off\nGear is 0\nDirection is 0\nSpeed is 0\n");
	}
	BOOST_AUTO_TEST_CASE(can_turn_on_engine)
	{
		VerifyCommandHandling("EngineOn", "Engine was turned on\n");
	}
	BOOST_AUTO_TEST_SUITE(when_enigne_is_turn_off)
		BOOST_AUTO_TEST_CASE(cannot_turn_off_engine_twice)
		{
			VerifyCommandHandling("EngineOff", "Engine is already turned off\n");
		}
		BOOST_AUTO_TEST_CASE(cannot_change_gear)
		{
			VerifyCommandHandling("SetGear 1", "Error: Engine was not turned on\n");
		}
		BOOST_AUTO_TEST_CASE(cannot_change_speed)
		{
			VerifyCommandHandling("SetSpeed 10", "Error: Engine was not turned on\n");
		}
		BOOST_AUTO_TEST_CASE(can_turn_on_engine)
		{
			VerifyCommandHandling("EngineOn", "Engine was turned on\n");
		}

	BOOST_AUTO_TEST_SUITE_END()
	struct when_engine_turned_on_ : CarContolFixture
	{
		when_engine_turned_on_()
		{
			car.TurnOnEngine();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_enigne_is_turn_on, when_engine_turned_on_)
		BOOST_AUTO_TEST_CASE(cannot_turn_on_engine_twice)
		{
			VerifyCommandHandling("EngineOn", "Engine is already turned on\n");
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_neutral_to_first)
		{
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
		}
		BOOST_AUTO_TEST_CASE(can_change_gear_from_reverse_to_first_at_zero_speed)
		{
			VerifyCommandHandling("SetGear -1", "Gear was change\n");
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
		}
		BOOST_AUTO_TEST_CASE(cannot_change_gear_from_first_to_reverse_at_zero_speed)
		{
			VerifyCommandHandling("SetGear 1", "Gear was change\n");
			VerifyCommandHandling("SetGear -1", "Gear wasn't change\n");
		}
		BOOST_AUTO_TEST_CASE(cannot_change_speed_up_on_neutral_gear)
		{
			VerifyCommandHandling("SetSpeed 10", "Speed wasn't change\n");
		}
		BOOST_AUTO_TEST_CASE(neutral_gear_does_not_change_moving_direction_when_speed_decreases)
		{
			VerifyCommandHandling("SetGear -1", "Gear was change\n");
			VerifyCommandHandling("SetSpeed 10", "Speed was change\n");
			VerifyCommandHandling("Info", "Engine is turned on\nGear is -1\nDirection is -1\nSpeed is 10\n");
			VerifyCommandHandling("SetGear 0", "Gear was change\n");
			VerifyCommandHandling("SetSpeed 8", "Speed was change\n");
			VerifyCommandHandling("Info", "Engine is turned on\nGear is 0\nDirection is -1\nSpeed is 8\n");
		}
		BOOST_AUTO_TEST_CASE(can_turn_off_engine_when_car_is_standing_still)
		{
			VerifyCommandHandling("EngineOff", "Engine was turned off\n");
		}
		BOOST_AUTO_TEST_CASE(cannot_turn_off_engine_on_while_driving)
		{
			VerifyCommandHandling("SetGear -1", "Gear was change\n");
			VerifyCommandHandling("SetSpeed 10", "Speed was change\n");
			VerifyCommandHandling("Info", "Engine is turned on\nGear is -1\nDirection is -1\nSpeed is 10\n");
			VerifyCommandHandling("EngineOff", "Engine was not turned off\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
