/*
 * MetaInformation.hpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#ifndef METAINFORMATION_HPP_
#define METAINFORMATION_HPP_

#include <string>

namespace parsevcf {

// Number type
///////////////

typedef int number_t;

// If the field has one value per alternate allele (A)
const number_t kAlternateNumber = -1;
// If the field has one value for each possible allele (including the reference) (R)
const number_t kReferenceNumber = -2;
// If the field has one value for each possible genotype (more relevant to the FORMAT tags) (G)
const number_t kGenotypeNumber = -3;
// If the number of possible values varies, is unknown, or is unbounded (.)
const number_t kUnknownNumber = -4;

// Info field
///////////////

enum InfoType {
	kIntegerInfoType,
	kFloatInfoType,
	kFlagInfoType,
	kCharacterInfoType,
	kStringInfoType
};

struct InfoField {
	/*InfoField(const std::string& id, const InfoType type, const number_t number, const std::string& description):
	id(id), type(type), number(number), description(description) {
		source = 0;
		version = 0;
	}*/
	const std::string& id;
	const InfoType type;
	const number_t number;
	const std::string& description;
	const std::string* source;
	const std::string* version;
};

// Format field
////////////////

enum FormatType {
	kIntegerFormatType,
	kFloatFormatType,
	kCharacterFormatType,
	kStringFormatType
};

struct FormatField {
	const std::string& id;
	const number_t number;
	const FormatType type;
	const std::string& description;
};

// Filter field
////////////////

struct FilterField {
	const std::string& id;
	const std::string& description;
};

struct AltField {

	const std::string& id;
	const std::string& description;
};

// Contig field
////////////////

struct ContigField {
	const std::string& id;
	const unsigned long length;
	const std::string* md5_checksum;
	const std::string* url;
};

} // namespace parsevcf



#endif /* METAINFORMATION_HPP_ */
