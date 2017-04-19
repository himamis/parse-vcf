/* This file is part of the parsevcf library (GPL v2 or later), see LICENSE */
#include "meta_parser.h"

#include <map>
#include "MetaInformation.h"
#include "constants.h"

using namespace std;

namespace parsevcf {

typedef map<string, string> meta_field_list_t;

bool equals(lexer& input) {
	return next_character(input, '=');
}

bool newline(lexer& input) {
	return next_line(input);
}

bool comma(lexer& input) {
	return next_character(input, ',');
}

bool quotemarks(lexer& input) {
	return next_character(input, '"');
}

bool langle(lexer& input) {
	return next_character(input, '<');
}

bool rangle(lexer& input) {
	return next_character(input, '>');
}

bool quoted_string(lexer& input, string& ret) {
	first_rule(quotemarks, input)

	if (!next_string_until_char(input, ret, '"')) {
		error_missing(input, "\"");
		return false;
	}
	rule(quotemarks, input)
	return true;
}

bool metaKey(lexer& input, string& ret) {
	return next_string_until_char(input, ret, '=');
}

bool metaPrefix(lexer& input) {
	return next_string(input, "##"); // ##
}

bool metaValueListKey(lexer& input, string& key) {
	if (!next_string_until_char(input, key, '=')) {
		return false;
	}
	return true;
}

bool metaValueListValue(lexer& input, string& value) {
	if (!quoted_string(input, value)) {
		if (!next_string_until_one_of(input, value, ",>")) {
			return false;
		}
	}
	return true;
}

bool metaValueListEntry(lexer& input, meta_field_list_t& values) {
	string key;
	if (!metaValueListKey(input, key)) {
		return false;
	}

	rule(equals, input)

	string value;
	if (!metaValueListValue(input, value)) {
		error_missing(input, "meta field list value");
		return false;
	}
	values[key] = value;
	return true;
}

bool metaValueList(lexer& input, meta_field_list_t& values) {
	first_rule(langle, input)

	if (!metaValueListEntry(input, values)) {
		error_missing(input, "meta filed list entry missing");
		return false;
	}

	while (comma(input)) {
		if (!metaValueListEntry(input, values)) {
			error_missing(input, "meta filed list entry missing");
			return false;
		}
	}

	rule(rangle, input)
	return true;
}

bool metaValueString(lexer& input, string& ret) {
	return next_string_until_newline(input, ret);
}

bool metaValue(lexer& input, meta_field_list_t& values) {
	if (!metaValueList(input, values)) {
		string ret;
		if (!metaValueString(input, ret)) {
			return false;
		}
		values[ret] = "";
	}
	return true;
}

void parseMetaEntry(DefaultHandler& handler, const string& key, const map<string, string>& values) {
	if (key == tokens::fileformat) {
		handler.fileformat(values.begin()->first);
	} else if (key == tokens::info) {
		InfoField field;
		field.value.map = &values;
		handler.infoField(field);
	} else if (key == tokens::format) {
		FormatField field;
		field.value.map = &values;
		handler.formatField(field);
	} else if (key == tokens::filter) {
		FilterField field;
		field.value.map = &values;
		handler.filterField(field);
	} else if (key == tokens::alt) {
		AltField field;
		field.value.map = &values;
		handler.altField(field);
	} else if (key == tokens::contig) {
		ContigField field;
		field.value.map = &values;
		handler.contigField(field);
	} else if (key == tokens::sample) {
		SampleField field;
		field.value.map = &values;
		handler.sampleField(field);
	} else if (key == tokens::meta) {
		MetaField field;
		field.value.map = &values;
		handler.metaField(field);
	} else if (key == tokens::pedigree) {
		PedigreeField field;
		field.value.map = &values;
		handler.pedigreeField(field);
	} else if (values.begin()->second != "") {
		ListEntry field;
		field.value.map = &values;
		handler.extraField(field);
	} else {
		KeyValueEntry field;
		field.name = key;
		field.value.single = &(values.begin()->first);
		handler.extraField(field);
	}
}

bool metaEntry(lexer& input, DefaultHandler& handler) {
	first_rule(metaPrefix, input)
	string key;
	if (!metaKey(input, key)) {
		error_missing(input, "meta key");
		return false;
	}
	rule(equals, input)

	meta_field_list_t values;
	if (!metaValue(input, values)) {
		error_missing(input, "meta field value");
		return false;
	}

	rule(newline, input)
	// create meta entry
	parseMetaEntry(handler, key, values);

	return true;
}

bool metaInformation(lexer& input, DefaultHandler& handler) {
	// list of meta entries
	first_rule(metaEntry, input, handler)

	do {
	} while (metaEntry(input, handler));
	return true;
}

} /* namespace parsevcf */

