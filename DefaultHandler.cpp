/*
 * DefaultHandler.cpp
 *
 *  Created on: 14 Apr 2017
 *      Author: balazs
 */

#include "DefaultHandler.h"

namespace parsevcf {

DefaultHandler::~DefaultHandler() { }

void DefaultHandler::startDocument(const std::string& document_name) { }

void DefaultHandler::endDocument(const std::string& document_name) { }

void DefaultHandler::fileformat(const std::string& format) { }

void DefaultHandler::extraField(const std::string& key, const std::string& value) { }

void DefaultHandler::infoField(const InfoField& info_field) { }

void DefaultHandler::filterField(const FilterField& filter_field) { }

void DefaultHandler::formatField(const FormatField& format_field) { }

void DefaultHandler::altField(const AltField& alt_field) { }

void DefaultHandler::metaField(const MetaField& meta_field) { }

void DefaultHandler::sampleField(const SampleField& sample_field) { }

void DefaultHandler::contigField(const ContigField& contig_field) { }

void DefaultHandler::sampleNames(const std::string& names) { }

void DefaultHandler::sample(const Sample& sample) { }

} /* namespace parsevcf */
