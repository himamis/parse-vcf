/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef SNVENTRY_H_
#define SNVENTRY_H_

#include <cstdlib>
#include <string>
#include <vector>
#include "Sample.h"

namespace parsevcf {

struct SNVEntry {

	std::vector<std::string> values;

	std::string chrom() const {
		return values[0];
	}

	unsigned int pos() const {
		return atoi(values[1].c_str());
	}

	std::vector<std::string> id() const {
		return tokenize(values[2], ';');
	}

	std::string ref() const {
		return values[3];
	}

	std::vector<std::string> alt() const {
		return tokenize(values[4], ',');
	}

	quality_t qual() const {
		if (values[5] == tokens::unknown) {
			return constants::quality::unknown;
		}
		return atof(values[5].c_str());
	}

	std::vector<std::string> filter() const {
		return tokenize(values[6], ';');
	}

	std::vector<std::pair<std::string, std::string> > info() const {
		std::vector<std::pair<std::string, std::string> > ret;
		std::vector<std::string> pairs = tokenize(values[7], ';');
		for(std::vector<std::string>::iterator it = pairs.begin(); it != pairs.end(); ++it) {
			std::vector<std::string> keyvalue = tokenize(*it, '=');
			if (keyvalue.size() == 1) {
				ret.push_back(std::pair<std::string, std::string>(keyvalue[0], ""));
			} else if (keyvalue.size() == 2) {
				ret.push_back(std::pair<std::string, std::string>(keyvalue[0], keyvalue[1]));
			} else {
				// error
			}
		}
		return ret;
	}

	std::vector<std::string> format() const {
		return tokenize(values[8], ';');
	}

	std::vector<Sample> samples() const {
		std::vector<Sample> sample;
		for(unsigned i = 9; i < values.size(); i++) {
			Sample s;
			s.value = values[i];
			sample.push_back(s);
		}

		return sample;
	}
};

} /* namespace parsevcf */

#endif /* SNVENTRY_H_ */
