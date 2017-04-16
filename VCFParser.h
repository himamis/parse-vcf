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

typedef short parser_state_t;

const parser_state_t kMeta = 0;
const parser_state_t kHeader = 1;
const parser_state_t kEntries = 2;

class VCFParser {
	std::ifstream& _input;
	const DefaultHandler& _handler;
	int _state;
public:
	VCFParser(std::ifstream& input, const DefaultHandler& handler);
	virtual ~VCFParser();

	void parse();
};

} /* namespace parsevcf */

#endif /* VCFPARSER_H_ */
