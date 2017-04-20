/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "catch.hpp"

#include "MetaInformation.h"
#include "VCFParser.h"
#include "DefaultHandler.h"
#include <iostream>
#include <fstream>

using namespace parsevcf;
using namespace std;

class TestHandler: public DefaultHandler {
public:
	bool startDocumentCalled;
	bool endDocumentCalled;

	vector<string> fileformats;

	vector<ListEntry> listExtraFields;
	vector<KeyValueEntry> keyvalueExtraFields;
	vector<InfoField> infoFields;
	vector<FilterField> filterFields;
	vector<FormatField> formatFields;
	vector<AltField> altFields;
	vector<MetaField> metaFields;
	vector<SampleField> sampleFields;
	vector<ContigField> contigFields;
	vector<PedigreeField> pedigreeFields;

	void fileformat(const std::string& format) {
		fileformats.push_back(format);
	}

	void startDocument() {
		startDocumentCalled = true;
	}

	void endDocument() {
		endDocumentCalled = true;
	}

	void extraField(const ListEntry& field) {
		listExtraFields.push_back(field);
	}

	void extraField(const KeyValueEntry& field) {
		keyvalueExtraFields.push_back(field);
	}

	void infoField(const InfoField& field) {
		infoFields.push_back(field);
	}

	void filterField(const FilterField& field) {
		filterFields.push_back(field);
	}

	void formatField(const FormatField& field) {
		formatFields.push_back(field);
	}

	void altField(const AltField& field) {
		altFields.push_back(field);
	}

	void metaField(const MetaField& field) {
		metaFields.push_back(field);
	}

	void sampleField(const SampleField& field) {
		sampleFields.push_back(field);
	}

	void contigField(const ContigField& field) {
		contigFields.push_back(field);
	}

	void pedigreeField(const PedigreeField& field) {
		pedigreeFields.push_back(field);
	}

	void sampleNames(const std::vector<std::string>& names) {

	}

	void entry(const SNVEntry& entry) { }

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

	CHECK( handler.fileformats.size() == 1 );
	CHECK( handler.fileformats[0] == "VCFv4.0" );
	CHECK( handler.startDocumentCalled );
	CHECK( handler.endDocumentCalled );
}

TEST_CASE( "Parsing VCF file with meta data" ) {
	ifstream input;
	input.open("test/examples/test-meta.vcf", ifstream::in);
	TestHandler handler;

	VCFParser parser = VCFParser(input, handler);
	REQUIRE( parser.parse() );

	SECTION( "Parsing key value pairs" ) {
		REQUIRE( handler.keyvalueExtraFields.size() == 4 );

		string keys[] = {"fileDate", "source", "reference", "phasing"};
		string values[] = {"20090805", "myImputationProgramV3.1", "1000GenomesPilot-NCBI36", "partial"};

		for (unsigned i = 0; i < 4; i++) {
			KeyValueEntry entry = handler.keyvalueExtraFields[i];
			CHECK( entry.name == keys[i] );
			CHECK( entry.line == values[i] );
		}
	}

	SECTION( "Parsing info fields" ) {
		REQUIRE( handler.infoFields.size() == 3);
	}
}
