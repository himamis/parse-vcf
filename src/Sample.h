/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <string>
#include <vector>
#include "Common.h"

namespace parsevcf {

struct Sample {

	std::string value;

	std::vector<std::string> data() const {
		return tokenize(value, ':');
	}
};

} /* namespace parsevcf */


#endif /* SAMPLE_H_ */
