/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef VCFPARSER_H_
#define VCFPARSER_H_

#include <fstream>
#include "DefaultHandler.h"

namespace parsevcf {

class VCFParser {
	std::ifstream& _input;
	DefaultHandler& _handler;
public:
	VCFParser(std::ifstream& input, DefaultHandler& handler);
	virtual ~VCFParser();

	bool parse();
};

} /* namespace parsevcf */

#endif /* VCFPARSER_H_ */
