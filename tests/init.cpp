#include <sort.cpp>
#include <catch.hpp>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

SCENARIO("32mb", "[32mb]")
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	sort_it("32mb", "out_32", 17);
	end = std::chrono::system_clock::now();
	cout <<"32MB- " <<(end - start).count() <<" nanoseconds"<< endl;
  REQUIRE(1);
}
SCENARIO("15mb", "[15mb]")
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	sort_it("15mb", "out_15", 4);
	end = std::chrono::system_clock::now();
	cout <<"15MB- " <<(end - start).count() <<" nanoseconds"<< endl;
  REQUIRE(1);
}

SCENARIO("8mb", "[8mb]")
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	sort_it("8mb", "out_8", 1);
	end = std::chrono::system_clock::now();
	cout <<"8MB- " <<(end - start).count() <<" nanoseconds"<< endl;
  REQUIRE(1);
}
