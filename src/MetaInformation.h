/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef METAINFORMATION_H_
#define METAINFORMATION_H_

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "Common.h"

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
		return value_at(tokens::id);
	}

	std::string value_at(const std::string& key) const {
		return value.map->at(key);
	}
};

struct HasNumber: public virtual ListEntry {

	number_t number() const {
		std::string number = value_at(tokens::number);
		if (number == tokens::a) {
			return constants::number::alternate;
		} else if (number == tokens::g) {
			return constants::number::genotype;
		} else if (number == tokens::r) {
			return constants::number::reference;
		}
		return atoi(number.c_str());
	}
};

struct HasDescription: public virtual ListEntry {

	std::string description() const {
		return value_at(tokens::description);
	}
};

struct HasType: public virtual ListEntry {

	type_t type() const {
		std::string info = value_at(tokens::type);
		if (info == tokens::integer) {
			return constants::type::integer;
		} else if (info == tokens::float_) {
			return constants::type::float_;
		} else if (info == tokens::string) {
			return constants::type::string;
		} else if (info == tokens::flag) {
			return constants::type::flag;
		} else if (info == tokens::character) {
			return constants::type::character;
		}
		exception::raise("Unknown type");
		return 0;
	}
};

// Info field
///////////////

struct InfoField: public HasNumber, public HasDescription, public HasType {

	type_t info_type() const {
		return type();
	}
};

// Format field
////////////////
struct FormatField: public HasNumber, public HasDescription, public HasType {

	type_t format_type() const {
		type_t format_t = type();
		if (format_t == constants::type::flag) {
			exception::raise("Unknown format type");
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
		return atol(value_at(tokens::length).c_str());
	}

	std::string md5() const {
		return value_at(tokens::md5);
	}

	std::string url() const {
		return value_at(tokens::url);
	}
};

// Meta and Sample fields
/////////////////////////

struct MetaField: public HasNumber, public HasType {

	std::vector<std::string> values() const {
		std::string val = value_at(tokens::values);
		std::vector<std::string> vec;
		// TODO

		return vec;
	}
};

struct SampleField: public HasDescription {

	std::string assay() const {
		return value_at(tokens::assay);
	}

	std::string ethnicity() const {
		return value_at(tokens::ethnicity);
	}

	std::string disease() const {
		return value_at(tokens::disease);
	}
};

// Pedigree field
//////////////////

struct PedigreeField: public ListEntry {
	// TODO
};

} /* namespace parsevcf */

#endif /* METAINFORMATION_H_ */
