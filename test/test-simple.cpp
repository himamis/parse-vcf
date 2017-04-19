/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "catch.hpp"

#include "MetaInformation.h"
#include "VCFParser.h"
#include "DefaultHandler.h"
#include <iostream>

using namespace parsevcf;
using namespace std;

class TestHandler: public DefaultHandler {
public:
	std::string ff;

	void fileformat(const std::string& format) {
		ff = format;
	}
};

TEST_CASE( "Minimal test case" ) {
	stringstream stream("#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO");
	DefaultHandler handler;
	VCFParser parser(stream, handler);
	REQUIRE( parser.parse() );
}

TEST_CASE( "A simple VCF test" ) {
	ifstream input;
	input.open("test/examples/test-simple.vcf", ifstream::in);
	TestHandler handler;

	VCFParser parser = VCFParser(input, handler);
	REQUIRE( parser.parse() );

	SECTION( "File format" ) {
		REQUIRE( handler.ff == "VCFv4.0" );
	}
}
