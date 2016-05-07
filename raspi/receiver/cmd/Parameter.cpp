#include "Paremeter.h"

// constructor for each parametertyp
// these will store the pointer of 
// the wished variable!
Parameter::Parameter(bool& value) {
	this->mType = BOOL_PARAMETER;
	this->mValue.boolPtr = &value;
}

Parameter::Parameter(float& value) {
	this->mType = FLOAT_PARAMETER;
	this->mValue.floatPtr = &value;
}

Parameter::Parameter(double& value) {
	this->mType = DOUBLE_PARAMETER;
	this->mValue.doublePtr = &value;
}

Parameter::Parameter(int& value) {
	this->mType = INT_PARAMETER;
	this->mValue.intPtr = &value;
}

Parameter::Parameter(unsigned int& value) {
	this->mType = UNSIGNED_INT_PARAMETER;
	this->mValue.uintPtr = &value;
}

Parameter::Parameter(std::string& value) {
	this->mType = STRING_PARAMETER;
	this->mValue.stringPtr = &value;
}

Parameter::Parameter(const Parameter& param) {
	this->mType = param.type();
	this->mValue = param.value();
}

// assigment for each parametertyp
// these will set a value to the 
// stored parameter!
Parameter& Parameter::operator = (bool value) {
	assert(this->mType == BOOL_PARAMETER);
	*this->mValue.boolPtr = value;
	return *this;
}

Parameter& Parameter::operator = (float value) {
	assert(this->mType == FLOAT_PARAMETER);
	*this->mValue.floatPtr = value;
	return *this;
}

Parameter& Parameter::operator = (double value) {
	assert(this->mType == DOUBLE_PARAMETER);
	*this->mValue.doublePtr = value;
	return *this;
}

Parameter& Parameter::operator = (int value) {
	assert(this->mType == INT_PARAMETER);
	*this->mValue.intPtr = value;
	return *this;
}

Parameter& Parameter::operator = (unsigned int value) {
	assert(this->mType == UNSIGNED_INT_PARAMETER);
	*this->mValue.uintPtr = value;
	return *this;
}

Parameter& Parameter::operator = (std::string value) {
	assert(this->mType == STRING_PARAMETER);
	*this->mValue.stringPtr = value;
	return *this;
}

// special func that will just do a normal
// copy and no set!
Parameter& Parameter::operator = (const Parameter param) {
	this->mType = param.type();
	this->mValue = param.value();
	return *this;
}

// easy cast functions
bool Parameter::asBool() const {
	assert(this->mType == BOOL_PARAMETER);
	return *this->mValue.boolPtr;
}

float Parameter::asFloat() const {
	assert(this->mType == FLOAT_PARAMETER);
	return *this->mValue.floatPtr;
}

double Parameter::asDouble() const {
	assert(this->mType == DOUBLE_PARAMETER);
	return *this->mValue.doublePtr;
}

int Parameter::asInt() const {
	assert(this->mType == INT_PARAMETER);
	return *this->mValue.intPtr;
}

unsigned int Parameter::asUInt() const {
	assert(this->mType == UNSIGNED_INT_PARAMETER);
	return *this->mValue.uintPtr;
}

std::string Parameter::asString() const {
	assert(this->mType == STRING_PARAMETER);
	return *this->mValue.stringPtr;
}

// util
bool Parameter::valid(const char* str) const {
	switch (this->mType) {
		case BOOL_PARAMETER:         return isBool(str); break;
		case FLOAT_PARAMETER:        return isNumber(str); break;
		case DOUBLE_PARAMETER:       return isNumber(str); break;
		case INT_PARAMETER:          return isNumber(str); break;
		case UNSIGNED_INT_PARAMETER: return isNumber(str); break;
		case STRING_PARAMETER:       return isString(str); break;
	}
	return false;
}

bool Parameter::assign(const char* str) {
	if (valid(str))
	{
		switch (mType) {
			case BOOL_PARAMETER: {
				*this->mValue.boolPtr = (strcmp(str, "True") == 0 || strcmp(str, "true") == 0 || strcmp(str, "TRUE") == 0 || strcmp(str, "1") ==0);
				break;
			}
			case FLOAT_PARAMETER:        *this->mValue.floatPtr = asciiToFloat(str); break;
			case DOUBLE_PARAMETER:       *this->mValue.doublePtr = asciiToDouble(str); break;
			case INT_PARAMETER:          *this->mValue.intPtr = atoi(str); break;
			case UNSIGNED_INT_PARAMETER: *this->mValue.uintPtr = atoi(str); break;
			case STRING_PARAMETER:       *this->mValue.stringPtr = str; break;
		}
		return true;
	}
	else {
		return false;
	}
}

// getter
ParameterType & Parameter::type() {
	return this->mType;
}

ValueUnion & Parameter::value() {
	return this->mValue;
}

const ParameterType & Parameter::type() const {
	return this->mType;
}

const ValueUnion & Parameter::value() const {
	return this->mValue;
}

// static stuff

bool Parameter::isOption(const char* str) {
	return str && str[0] == '-';
}

bool Parameter::isString(const char* str) {
	if (!str) return false;
	return true;
	//return !isOption(str);
}

bool Parameter::isBool(const char* str) {
	if (!str) return false;

	return (strcmp(str, "True") == 0 || strcmp(str, "true") == 0 || strcmp(str, "TRUE") == 0 ||
		strcmp(str, "False") == 0 || strcmp(str, "false") == 0 || strcmp(str, "FALSE") == 0 ||
		strcmp(str, "0") == 0 || strcmp(str, "1") == 0);
}

bool Parameter::isNumber(const char* str) {
	if (!str) return false;

	bool hadPlusMinus = false;
	bool hadDecimalPlace = false;
	bool hadExponent = false;
	bool couldBeInt = true;
	bool couldBeFloat = true;
	int noZeroToNine = 0;

	const char* ptr = str;

	// check if could be a hex number.
	if (strncmp(ptr, "0x", 2) == 0) {
		// skip over leading 0x, and then go through rest of string
		// checking to make sure all values are 0...9 or a..f.
		ptr += 2;
		while (
			*ptr != 0 &&
			((*ptr >= '0' && *ptr <= '9') ||
				(*ptr >= 'a' && *ptr <= 'f') ||
				(*ptr >= 'A' && *ptr <= 'F'))
			) {
			++ptr;
		}

		// got to end of string without failure, therefore must be a hex integer.
		if (*ptr == 0) return true;
	}

	ptr = str;

	// check if a float or an int.
	while (*ptr != 0 && couldBeFloat) {
		if (*ptr == '+' || *ptr == '-') {
			if (hadPlusMinus) {
				couldBeInt = false;
				couldBeFloat = false;
			}
			else hadPlusMinus = true;
		}
		else if (*ptr >= '0' && *ptr <= '9') {
			noZeroToNine++;
		}
		else if (*ptr == '.') {
			if (hadDecimalPlace) {
				couldBeInt = false;
				couldBeFloat = false;
			}
			else {
				hadDecimalPlace = true;
				couldBeInt = false;
			}
		}
		else if (*ptr == 'e' || *ptr == 'E') {
			if (hadExponent || noZeroToNine == 0) {
				couldBeInt = false;
				couldBeFloat = false;
			}
			else {
				hadExponent = true;
				couldBeInt = false;
				hadDecimalPlace = false;
				hadPlusMinus = false;
				noZeroToNine = 0;
			}
		}
		else {
			couldBeInt = false;
			couldBeFloat = false;
		}
		++ptr;
	}

	if (couldBeInt && noZeroToNine>0) return true;
	if (couldBeFloat && noZeroToNine>0) return true;

	return false;

}

double Parameter::asciiToDouble(const char* str)
{
	const char* ptr = str;

	// check if could be a hex number.
	if (strncmp(ptr, "0x", 2) == 0) {
		double value = 0.0;
		// skip over leading 0x, and then go through rest of string
		// checking to make sure all values are 0...9 or a..f.
		ptr += 2;
		while (
			*ptr != 0 &&
			((*ptr >= '0' && *ptr <= '9') ||
				(*ptr >= 'a' && *ptr <= 'f') ||
				(*ptr >= 'A' && *ptr <= 'F'))
			) {
			if (*ptr >= '0' && *ptr <= '9') value = value*16.0 + double(*ptr - '0');
			else if (*ptr >= 'a' && *ptr <= 'f') value = value*16.0 + double(*ptr - 'a' + 10);
			else if (*ptr >= 'A' && *ptr <= 'F') value = value*16.0 + double(*ptr - 'A' + 10);
			++ptr;
		}

		// OSG_NOTICE<<"Read "<<str<<" result = "<<value<<std::endl;
		return value;
	}

	ptr = str;

	bool    hadDecimal[2];
	double  value[2];
	double  sign[2];
	double  decimalMultiplier[2];

	hadDecimal[0] = hadDecimal[1] = false;
	sign[0] = sign[1] = 1.0;
	value[0] = value[1] = 0.0;
	decimalMultiplier[0] = decimalMultiplier[1] = 0.1;
	int pos = 0;

	// compute mantissa and exponent parts
	while (*ptr != 0 && pos<2) {
		if (*ptr == '+') {
			sign[pos] = 1.0;
		}
		else if (*ptr == '-') {
			sign[pos] = -1.0;
		}
		else if (*ptr >= '0' && *ptr <= '9') {
			if (!hadDecimal[pos]) {
				value[pos] = value[pos] * 10.0 + double(*ptr - '0');
			}
			else {
				value[pos] = value[pos] + decimalMultiplier[pos] * double(*ptr - '0');
				decimalMultiplier[pos] *= 0.1;
			}
		}
		else if (*ptr == '.') {
			hadDecimal[pos] = true;
		}
		else if (*ptr == 'e' || *ptr == 'E') {
			if (pos == 1) break;

			pos = 1;
		}
		else {
			break;
		}
		++ptr;
	}

	if (pos == 0) {
		// OSG_NOTICE<<"Read "<<str<<" result = "<<value[0]*sign[0]<<std::endl;
		return value[0] * sign[0];
	}
	else {
		double mantissa = value[0] * sign[0];
		double exponent = value[1] * sign[1];
		//OSG_NOTICE<<"Read "<<str<<" mantissa = "<<mantissa<<" exponent="<<exponent<<" result = "<<mantissa*pow(10.0,exponent)<<std::endl;
		return mantissa*pow(10.0, exponent);
	}
}

double Parameter::findAsciiToDouble(const char* str)
{
	const char* ptr = str;
	double value = 0.0;

	while (*ptr != 0) {
		if (*ptr >= '0' && *ptr <= '9') {
			value = asciiToDouble(ptr);
			return value;
		}
		++ptr;
	}

	return 0.0;
}