/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "DefaultHandler.h"

namespace parsevcf {

DefaultHandler::~DefaultHandler() { }

void DefaultHandler::startDocument() { }

void DefaultHandler::endDocument() { }

void DefaultHandler::fileformat(const std::string& format) { }

void DefaultHandler::extraField(const ListEntry& field) { }

void DefaultHandler::extraField(const KeyValueEntry& field) { }

void DefaultHandler::infoField(const InfoField& field) { }

void DefaultHandler::filterField(const FilterField& field) { }

void DefaultHandler::formatField(const FormatField& field) { }

void DefaultHandler::altField(const AltField& field) { }

void DefaultHandler::metaField(const MetaField& field) { }

void DefaultHandler::sampleField(const SampleField& field) { }

void DefaultHandler::contigField(const ContigField& field) { }

void DefaultHandler::pedigreeField(const PedigreeField& field) { }

void DefaultHandler::sampleNames(const std::vector<std::string>& names) { }

void DefaultHandler::entry(const SNVEntry& entry) { }

} /* namespace parsevcf */
