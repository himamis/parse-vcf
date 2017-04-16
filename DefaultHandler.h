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
	virtual void extraField(const std::string& key, const std::string& value);

	virtual void infoField(const InfoField& info_field);
	virtual void filterField(const FilterField& filter_field);
	virtual void formatField(const FormatField& format_field);
	virtual void altField(const AltField& alt_field);
	virtual void metaField(const MetaField& meta_field);
	virtual void sampleField(const SampleField& sample_field);
	virtual void contigField(const ContigField& contig_field);

	virtual void sampleNames(const std::string& names);

	virtual void sample(const Sample& sample);
};

} /* namespace parsevcf */

#endif /* DEFAULTHANDLER_H_ */
