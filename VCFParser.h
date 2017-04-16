/*
 * VCFParser.h
 *
 *  Created on: 15 Apr 2017
 *      Author: balazs
 */

#ifndef VCFPARSER_H_
#define VCFPARSER_H_

#include <fstream>
#include "DefaultHandler.h"

namespace parsevcf {

class VCFParser {
	std::ifstream& _input;
	const DefaultHandler& _handler;
public:
	VCFParser(std::ifstream& input, const DefaultHandler& handler);
	virtual ~VCFParser();

	void parse();
};

} /* namespace parsevcf */

#endif /* VCFPARSER_H_ */
