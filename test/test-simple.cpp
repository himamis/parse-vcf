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
	std::string doc_name;

	bool startDocumentCalled;
	bool endDocumentCalled;

	void fileformat(const std::string& format) {
		ff = format;
	}

	void startDocument() {
		startDocumentCalled = true;
	}

	void endDocument() {
		endDocumentCalled = true;
	}
};

TEST_CASE( "Minimal test case" ) {
	stringstream stream("#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO");
	DefaultHandler handler;
	VCFParser parser(stream, handler);
	REQUIRE( parser.parse() );
}

TEST_CASE( "Parsing a simple VCF file" ) {
	ifstream input;
	input.open("test/examples/test-simple.vcf", ifstream::in);
	TestHandler handler;

	VCFParser parser = VCFParser(input, handler);
	REQUIRE( parser.parse() );

	CHECK( handler.ff == "VCFv4.0" );
	CHECK( handler.startDocumentCalled );
	CHECK( handler.endDocumentCalled );
}
