/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "catch.hpp"

#include "MetaInformation.h"
#include "VCFParser.h"
#include "DefaultHandler.h"
#include <iostream>

using namespace parsevcf;
using namespace std;

TEST_CASE("load simple file and parse") {
	ifstream input;
	input.open("examples/test-simple.vcf", ifstream::in);
	DefaultHandler handler;

	VCFParser parser = VCFParser(input, handler);

	REQUIRE(parser.parse());
}
