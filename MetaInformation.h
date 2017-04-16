#ifndef METAINFORMATION_H_
#define METAINFORMATION_H_

#include <string>
#include <vector>
#include <map>

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

// Alt field
////////////////

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

// Meta and Sample fields
/////////////////////////

typedef FormatType MetaType;

struct MetaField {
	const std::string& id;
	const MetaType type;
	const number_t number;
	const std::vector<const std::string&>& values;
};

struct SampleField {
	const std::string& id;
	const std::map<MetaField*, const std::string&> values;
};

// Pedigree field
//////////////////

struct PedigreeField {
	const std::string& id;
	// length 1 corresponds to original
	// length 2 corresponds to mother and father
	// length >2 corresponds to the i-th ancestor
	const std::vector<const std::string&>& names;
};

} /* namespace parsevcf */

#endif /* METAINFORMATION_H_ */
