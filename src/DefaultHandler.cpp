/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "DefaultHandler.h"
#include <vector>

namespace parsevcf {

DefaultHandler::~DefaultHandler() { }

void DefaultHandler::startDocument() { }

void DefaultHandler::endDocument() { }

void DefaultHandler::fileformat(const std::string& format) { }

void DefaultHandler::extraField(const ListEntry& field) { }

void DefaultHandler::extraField(const KeyValueEntry& field) { }

void DefaultHandler::infoField(const InfoField& info_field) { }

void DefaultHandler::filterField(const FilterField& filter_field) { }

void DefaultHandler::formatField(const FormatField& format_field) { }

void DefaultHandler::altField(const AltField& alt_field) { }

void DefaultHandler::metaField(const MetaField& meta_field) { }

void DefaultHandler::sampleField(const SampleField& sample_field) { }

void DefaultHandler::contigField(const ContigField& contig_field) { }

void DefaultHandler::pedigreeField(const PedigreeField& field) { }

void DefaultHandler::sampleNames(const std::vector<std::string>& names) { }

void DefaultHandler::entry(const SNVEntry& entry) { }

} /* namespace parsevcf */
