/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#ifndef DEFAULTHANDLER_H_
#define DEFAULTHANDLER_H_

#include "MetaInformation.h"
#include "SNVEntry.h"

namespace parsevcf {

class DefaultHandler {
public:
	virtual ~DefaultHandler();

	virtual void startDocument(const std::string& document_name);
	virtual void endDocument(const std::string& document_name);

	virtual void fileformat(const std::string& format);
	virtual void extraField(const ListEntry& field);
	virtual void extraField(const KeyValueEntry& field);

	virtual void infoField(const InfoField& field);
	virtual void filterField(const FilterField& field);
	virtual void formatField(const FormatField& field);
	virtual void altField(const AltField& field);
	virtual void metaField(const MetaField& field);
	virtual void sampleField(const SampleField& field);
	virtual void contigField(const ContigField& field);
	virtual void pedigreeField(const PedigreeField& field);

	virtual void sampleNames(const std::vector<std::string>& names);

	virtual void entry(const SNVEntry& sample);
};

} /* namespace parsevcf */

#endif /* DEFAULTHANDLER_H_ */
