/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

namespace parsevcf {

/* types */
typedef int number_t;

typedef float quality_t;

typedef short type_t;

namespace exception {

inline void raise(const std::string& message) {
	throw std::runtime_error(message);
}

} /* namespace exception */

namespace tokens {

const std::string chrom = "CHROM";
const std::string pos = "POS";
const std::string id = "ID";
const std::string ref = "REF";
const std::string alt = "ALT";
const std::string qual = "QUAL";
const std::string filter = "FILTER";
const std::string info = "INFO";
const std::string format = "FORMAT";

const std::string pass = "PASS";
const std::string unknown = ".";

const std::string fileformat = "fileformat";
const std::string description = "Description";
const std::string contig = "contig";
const std::string sample = "META";
const std::string meta = "SAMPLE";
const std::string pedigree = "PEDIGREE";

const std::string type = "Type";
const std::string integer = "Integer";
const std::string string = "String";
const std::string float_ = "Float";
const std::string flag = "Flag";
const std::string character = "Character";

const std::string number = "Number";
const std::string a = "A";
const std::string r = "R";
const std::string g = "G";
const std::string dot = ".";

const std::string length = "length";
const std::string url = "URL";
const std::string md5 = "md5";

const std::string values = "Values";

const std::string assay = "Assay";
const std::string disease = "Disease";
const std::string ethnicity = "Ethnicity";

} /* namespace tokens */

namespace constants {

namespace number {

const number_t alternate = -1;
const number_t reference = -2;
const number_t genotype = -3;
const number_t unknown = -4;

} /* namespace number */

namespace type {

const type_t integer = 0;
const type_t float_ = 1;
const type_t flag = 2;
const type_t character = 3;
const type_t string = 4;

} /* namspace type */

namespace quality {

const quality_t unknown = std::numeric_limits<float>::max();

} /* namspace quality */


} /* namespace constants */

} /* namespace parsevcf */

#endif /* CONSTANTS_H_ */
