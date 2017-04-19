/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "MetaInformation.h"
#include "VCFParser.h"
#include "DefaultHandler.h"
#include <iostream>

using namespace parsevcf;

class NoisyHandler: public DefaultHandler {

	int entry_num;

	void sampleNames(const std::vector<std::string>& names) {
		std::cout << names[0];
		std::cout << std::endl;
	}

	void infoField(const InfoField& field) {
		std::cout << field.id();
		std::cout << std::endl;
	}

	void entry(const SNVEntry& entry) {
		entry_num++;
		entry.samples()[0].value;
		if (entry_num % 10000 == 0) {
			std::cout << entry.samples()[0].value << " ";
			std::cout << "at: " << entry_num << std::endl;
		}
		//std::cout << std::endl;
	}

public:
	NoisyHandler() {
		entry_num = 0;
	}

};

int main(int argc, char **argv) {
	std::string csa = "csa";
	parsevcf::InfoField fi;
	fi.value.single = &csa;

	std::ifstream input;
	input.open("../../../Downloads/CEU.low_coverage.2010_09.genotypes.vcf", std::ifstream::in);
	//input.open("test1.vcf", std::ifstream::in);
	NoisyHandler handler;

	VCFParser parser = VCFParser(input, handler);

	parser.parse();

	return 0;
}

