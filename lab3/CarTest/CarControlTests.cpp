#include "stdafx.h"
#include "../Car/CCarControl.h"
#include "../Car/CCar.h"

struct CarControlDependencies
{
	CCar car;
	std::stringstream input;
	std::stringstream output;
};

struct CarContolFixture : CarControlDependencies
{
	CCarControl carControl;

	CarContolFixture()
		:carControl(car, input, output)
	{
	}

	void VerifyCommandHandling(const std::string & command, const std::string & expectedOutput)
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
	BOOST_AUTO_TEST_CASE(can_handle_Info_command)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
		BOOST_CHECK(car.GetDirection() == Direction::None);
		BOOST_CHECK(car.GetGear() == Gear::Neutral);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		VerifyCommandHandling("Info", "Engine is turned off\nGear is 0\nDirection is 0\nSpeed is 0\n");

		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.SetGear(Gear::First));
		BOOST_CHECK(car.SetSpeed(10));
		VerifyCommandHandling("Info", "Engine is turned on\nGear is 1\nDirection is 1\nSpeed is 10\n");
	}
	BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
		VerifyCommandHandling("EngineOn", "Engine was turned on\n");

		BOOST_CHECK(car.IsEngineTurnOn());
		VerifyCommandHandling("EngineOn", "Engine is already turned on\n");
	}
	BOOST_AUTO_TEST_CASE(can_handle_EngineOff_command)
	{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.IsEngineTurnOn());
		BOOST_CHECK(car.SetGear(Gear::First));
		BOOST_CHECK(car.SetSpeed(10));
		VerifyCommandHandling("EngineOff", "Engine was not turned off\n");

		BOOST_CHECK(car.SetGear(Gear::Neutral));
		BOOST_CHECK(car.SetSpeed(0));
		BOOST_CHECK(car.IsEngineTurnOn());
		VerifyCommandHandling("EngineOff", "Engine was turned off\n");

		BOOST_CHECK(!car.IsEngineTurnOn());
		VerifyCommandHandling("EngineOff", "Engine is already turned off\n");
	}
BOOST_AUTO_TEST_SUITE_END()