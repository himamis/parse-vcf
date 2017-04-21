/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "catch.hpp"

#include "MetaInformation.h"
#include "VCFParser.h"
#include "DefaultHandler.h"
#include "Common.h"
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
	vector<SampleField> sampleFields;
	vector<PedigreeField> pedigreeFields;

	vector<string> samples;
	vector<SNVEntry> entries;

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

	void sampleField(const SampleField& field) {
		sampleFields.push_back(field);
	}

	void pedigreeField(const PedigreeField& field) {
		pedigreeFields.push_back(field);
	}

	void sampleNames(const std::vector<std::string>& names) {
		samples = names;
	}

	void entry(const SNVEntry& entry) {
		entries.push_back(entry);
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

		string keys[] = { "fileDate", "source", "reference", "phasing" };
		string values[] = { "20090805", "myImputationProgramV3.1", "1000GenomesPilot-NCBI36", "partial" };

		for (unsigned i = 0; i < 4; i++) {
			KeyValueEntry entry = handler.keyvalueExtraFields[i];
			CHECK( entry.name == keys[i] );
			CHECK( entry.line == values[i] );
		}
	}

	SECTION( "Parsing info fields" ) {
		REQUIRE( handler.infoFields.size() == 3 );

		string ids[] = { "NS", "AF", "H2" };
		number_t numbers[] = { 1, constants::number::genotype, 0 };
		type_t types[] = { constants::type::integer, constants::type::float_, constants::type::flag };
		string descriptions[] = { "Number of Samples With Data", "Allele Frequency", "HapMap2 membership" };

		for (unsigned i = 0; i < 3; i++) {
			InfoField field = handler.infoFields[i];
			CHECK( field.id() == ids[i] );
			CHECK( field.number() == numbers[i] );
			CHECK( field.type() == types[i] );
			CHECK( field.description() == descriptions[i] );
		}
	}

	SECTION( "Parsing filter field") {
		REQUIRE( handler.filterFields.size() == 1 );
		FilterField filter = handler.filterFields[0];

		CHECK( filter.id() == "q10" );
		CHECK( filter.description() == "Quality below 10" );
	}

	SECTION( "Parsing format" ) {
		REQUIRE( handler.formatFields.size() == 1 );
		FormatField format = handler.formatFields[0];

		CHECK( format.id() == "HQ" );
		CHECK( format.number() == 2 );
		CHECK( format.type() == constants::type::integer );
		CHECK( format.description() == "Haplotype Quality" );
	}

	SECTION( "Parsing pedigree" ) {
		REQUIRE( handler.pedigreeFields.size() == 1 );
		PedigreeField field = handler.pedigreeFields[0];

		CHECK( field.id() == "TumourSample" );
		CHECK( field.original() == "GermlineID" );
		CHECK( field.father() == "" );
		CHECK( field.mother() == "" );
	}
}

TEST_CASE( "Parsing VCF file with wrong format" ) {
	TestHandler handler;

	SECTION( "Missing header" ) {
		stringstream stream("Invalid format");
		VCFParser parser(stream, handler);

		REQUIRE_THROWS_WITH( parser.parse(), Catch::Contains("expecting header") );
	}

	SECTION( "Wrong type" ) {
		stringstream stream("##INFO=<ID=NS,Number=1,Type=Object,Description=\"Nothing\">\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO");
		VCFParser parser(stream, handler);

		REQUIRE( parser.parse() );
		REQUIRE( handler.infoFields.size() == 1 );

		InfoField field = handler.infoFields[0];
		CHECK_THROWS_WITH( field.type(), Catch::Contains("type") );
	}
}

TEST_CASE( "Samples" ) {
	ifstream input;
	input.open("test/examples/test-simple.vcf", ifstream::in);
	TestHandler handler;
	VCFParser parser(input, handler);

	REQUIRE( parser.parse() );
	REQUIRE( handler.entries.size() == 5 );
	REQUIRE( handler.samples.size() == 3 );

	SECTION( "Sample names" ) {
		CHECK( handler.samples[0] == "NA00001" );
		CHECK( handler.samples[1] == "NA00002" );
		CHECK( handler.samples[2] == "NA00003" );
	}

	SECTION( "Entry values" ) {
		SNVEntry entry = handler.entries[0];
		CHECK( entry.chrom() == "20" );
		CHECK( entry.pos() == 14370 );
		CHECK( entry.id().size() == 1 );
		CHECK( entry.id()[0] == "rs6054257" );
		CHECK( entry.ref() == "G" );
		CHECK( entry.alt().size() == 1 );
		CHECK( entry.alt()[0] == "A" );
		CHECK( entry.qual() == Approx(29) );
	}

	SECTION( "Sample values" ) {
		SNVEntry entry = handler.entries[0];
		vector<Sample> samples = entry.samples();
		REQUIRE( samples.size() == 3);
		Sample sample = samples[0];
		vector<string> data = sample.data();
		REQUIRE( data.size() == 4 );
		CHECK( data[0] == "0|0" );
		CHECK( data[1] == "48" );
		CHECK( data[2] == "1" );
		CHECK( data[3] == "51,51" );
	}
}

