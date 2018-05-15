#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"
#include "Sportsman.h"

bool HighestPlayer(const std::vector<Sportsman>& team, Sportsman& sporstsman)
{
	return FindMaxEx(team, sporstsman, [](const auto& lhs, const auto& rhs) {
		return lhs.height < rhs.height;
	});
}

bool MostWeightytPlayer(const std::vector<Sportsman>& team, Sportsman& sporstsman)
{
	return FindMaxEx(team, sporstsman, [](const auto& lhs, const auto& rhs) {
		return lhs.weight < rhs.weight;
	});
}

struct Team
{
	std::vector<Sportsman> team;
};

BOOST_FIXTURE_TEST_SUITE(Find_Max_Ex, Team)
	BOOST_AUTO_TEST_CASE(returns_false_if_vector_is_empty)
	{
		Sportsman highestSportsman;
		BOOST_CHECK(!FindMaxEx(team, highestSportsman, [](const auto& lhs, const auto& rhs) { return lhs.height < rhs.height; }));
	}
	struct FootballTeam_ : Team
	{
		FootballTeam_()
		{
			team.push_back(Sportsman("Igor Akinfeev", 186, 82));
			team.push_back(Sportsman("Sergei Ignashevich", 186, 82));
			team.push_back(Sportsman("Igor Smolnikov", 178, 70));
			team.push_back(Sportsman("Fyodor Kudryashov", 181, 77));
			team.push_back(Sportsman("Vladislav Ignatyev", 180, 72));
			team.push_back(Sportsman("Yuri Zhirkov", 180, 75));
			team.push_back(Sportsman("Alan Dzagoev", 179, 75));
			team.push_back(Sportsman("Aleksandr Yerokhin", 203, 83));
			team.push_back(Sportsman("Aleksandr Samedov", 178, 75));
			team.push_back(Sportsman("Artem Dzyuba", 196, 89));
			team.push_back(Sportsman("Fyodor Smolov", 187, 80));
		}
	};

	BOOST_FIXTURE_TEST_SUITE(FootballTeam, FootballTeam_)
		BOOST_AUTO_TEST_CASE(the_higest_football_player_of_the_Russian_national_team)
		{
			Sportsman player;
			BOOST_CHECK(HighestPlayer(team, player));
			BOOST_CHECK(player.name == "Aleksandr Yerokhin");
		}
		BOOST_AUTO_TEST_CASE(the_most_weightly_football_player_of_the_Russian_national_team)
		{
			Sportsman player;
			BOOST_CHECK(MostWeightytPlayer(team, player));
			BOOST_CHECK(player.name == "Artem Dzyuba");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
