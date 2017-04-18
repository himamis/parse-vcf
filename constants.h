/*
 * constants.h
 *
 *  Created on: 17 Apr 2017
 *      Author: balazs
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

namespace parsevcf {
namespace constants {

const std::string kChrom = "CHROM";
const std::string kPos = "POS";
const std::string kId = "ID";
const std::string kRef = "REF";
const std::string kAlt = "ALT";
const std::string kQual = "QUAL";
const std::string kFilter = "FILTER";
const std::string kInfo = "INFO";
const std::string kFormat = "FORMAT";

const std::string kPass = "PASS";
const std::string kUnknown = ".";

const std::string kFileFormat = "fileFormat";
const std::string kDescription = "Description";
const std::string kContig = "contig";
const std::string kSample = "META";
const std::string kMeta = "SAMPLE";
const std::string kPedigree = "PEDIGREE";

const std::string kType = "Type";
const std::string kInteger = "Integer";
const std::string kString = "String";
const std::string kFloat = "Float";
const std::string kFlag = "Flag";
const std::string kCharacter = "Character";

const std::string kNumber = "Number";
const std::string kA = "A";
const std::string kR = "R";
const std::string kG = "G";
const std::string kDot = ".";

const std::string kLength = "length";
const std::string kUrl = "URL";
const std::string kMd5 = "md5";

const std::string kValues = "Values";

const std::string kAssay = "Assay";
const std::string kDisease = "Disease";
const std::string kEthnicity = "Ethnicity";


// TODO move to types
namespace number {
typedef int number_t;

// If the field has one value per alternate allele (A)
const number_t kAlternateNumber = -1;
// If the field has one value for each possible allele (including the reference) (R)
const number_t kReferenceNumber = -2;
// If the field has one value for each possible genotype (more relevant to the FORMAT tags) (G)
const number_t kGenotypeNumber = -3;
// If the number of possible values varies, is unknown, or is unbounded (.)
const number_t kUnknownNumber = -4;
}

namespace type {
typedef short type_t;

const type_t kInteger = 0;
const type_t kFloat = 1;
const type_t kFlag = 2;
const type_t kCharacter = 3;
const type_t kString = 4;
}


} /* namespace constants */
} /* namespace parsevcf */

#endif /* CONSTANTS_H_ */
