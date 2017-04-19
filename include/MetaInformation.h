/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef METAINFORMATION_H_
#define METAINFORMATION_H_

#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include "constants.h"

namespace parsevcf {

struct MetaEntry {

	union {
		const std::string* single;
		const std::map<std::string, std::string>* map;
	} value;
};

struct KeyValueEntry: public MetaEntry {

	std::string name;

	std::string line() const {
		return *value.single;
	}
};

struct ListEntry: public virtual MetaEntry {

	std::string id() const {
		return value_at(constants::kId);
	}

	std::string value_at(const std::string& key) const {
		return value.map->at(key);
	}
};

struct HasNumber: public virtual ListEntry {

	constants::number::number_t number() const {
		std::string number = value_at(constants::kNumber);
		if (number == constants::kA) {
			return constants::number::kAlternateNumber;
		} else if (number == constants::kG) {
			return constants::number::kGenotypeNumber;
		} else if (number == constants::kR) {
			return constants::number::kReferenceNumber;
		}
		return atoi(number.c_str());
	}
};

struct HasDescription: public virtual ListEntry {

	std::string description() const {
		return value_at(constants::kDescription);
	}
};

struct HasType: public virtual ListEntry {

	constants::type::type_t type() const {
		std::string info = value_at(constants::kType);
		if (info == constants::kInteger) {
			return constants::type::kInteger;
		} else if (info == constants::kFloat) {
			return constants::type::kFloat;
		} else if (info == constants::kString) {
			return constants::type::kString;
		} else if (info == constants::kFlag) {
			return constants::type::kFlag;
		} else if (info == constants::kCharacter) {
			return constants::type::kCharacter;
		}
		//throw error();
		return constants::type::kInteger;
	}
};

// Info field
///////////////

struct InfoField: public HasNumber, public HasDescription, public HasType {

	constants::type::type_t info_type() const {
		return type();
	}
};

// Format field
////////////////
struct FormatField: public HasNumber, public HasDescription, public HasType {

	constants::type::type_t format_type() const {
		constants::type::type_t format_t = type();
		if (format_t == constants::type::kFlag) {
			// error();
		}
		return format_t;
	}
};

// Filter field
////////////////

typedef HasDescription FilterField;

// Alt field
////////////////

typedef HasDescription AltField;

// Contig field
////////////////

struct ContigField: public ListEntry {

	unsigned long length() const {
		return atol(value_at(constants::kLength).c_str());
	}

	std::string md5() const {
		return value_at(constants::kMd5);
	}

	std::string url() const {
		return value_at(constants::kUrl);
	}
};

// Meta and Sample fields
/////////////////////////

struct MetaField: public HasNumber, public HasType {

	std::vector<std::string> values() const {
		std::string val = value_at(constants::kValues);
		std::vector<std::string> vec;
		// TODO

		return vec;
	}
};

struct SampleField: public HasDescription {

	std::string assay() const {
		return value_at(constants::kAssay);
	}

	std::string ethnicity() const {
		return value_at(constants::kEthnicity);
	}

	std::string disease() const {
		return value_at(constants::kDisease);
	}
};

// Pedigree field
//////////////////

struct PedigreeField: public ListEntry {
	// TODO
};

} /* namespace parsevcf */

#endif /* METAINFORMATION_H_ */
