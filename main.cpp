#include "MetaInformation.h"
#include "VCFParser.h"
#include "DefaultHandler.h"

using namespace parsevcf;

int main(int argc, char **argv) {
	parsevcf::InfoField info = {.id = "ID", .type = kIntegerInfoType, .number = kGenotypeNumber,
			.description = "Description", .source = 0, .version = 0
	};

	std::ifstream input;
	//input.open("../../../Downloads/CEU.low_coverage.2010_09.genotypes.vcf", std::ifstream::in);
	input.open("test1.vcf", std::ifstream::in);
	DefaultHandler handler;

	VCFParser parser = VCFParser(input, handler);

	parser.parse();

	return 0;
}

