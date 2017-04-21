/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "catch.hpp"

#include "Common.h"

using namespace std;
using namespace parsevcf;

TEST_CASE( "tokenize simple" ) {
	vector<string> ret = parsevcf::tokenize("12:23:34", ':');
	REQUIRE( ret.size() == 3 );
	CHECK( ret[0] == "12" );
	CHECK( ret[1] == "23" );
	CHECK( ret[2] == "34" );
}

TEST_CASE( "tokenize empty" ) {
	vector<string> ret = parsevcf::tokenize("", ':');
	REQUIRE( ret.size() == 1 );
	CHECK( ret[0] == "" );
}

TEST_CASE( "tokenize missing end" ) {
	vector<string> ret = parsevcf::tokenize("12::", ':');
	REQUIRE( ret.size() == 3 );
	CHECK( ret[0] == "12" );
	CHECK( ret[1] == "" );
	CHECK( ret[2] == "" );
}

TEST_CASE( "tokenize missing beginning" ) {
	vector<string> ret = parsevcf::tokenize(":12", ':');
	REQUIRE( ret.size() == 2 );
	CHECK( ret[0] == "" );
	CHECK( ret[1] == "12" );
}
