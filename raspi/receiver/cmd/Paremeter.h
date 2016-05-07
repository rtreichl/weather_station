#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <math.h>
#include <ostream>
#include <assert.h>

// ArgumenterParser of the OSG Library!

// enum to set the datatyp
enum ParameterType
{
	BOOL_PARAMETER,
	FLOAT_PARAMETER,
	DOUBLE_PARAMETER,
	INT_PARAMETER,
	UNSIGNED_INT_PARAMETER,
	STRING_PARAMETER
};

// union to store the pointer
// of the parameter
union ValueUnion
{
	bool*           boolPtr;
	float*          floatPtr;
	double*         doublePtr;
	int*            intPtr;
	unsigned int*   uintPtr;
	std::string*    stringPtr;
};

class Parameter
{
protected:
	ParameterType   mType;
	ValueUnion      mValue;

public:
	// constructor for each parametertyp
	// these will store the pointer of 
	// the wished variable!
	Parameter(bool& value);
	Parameter(float& value);
	Parameter(double& value);
	Parameter(int& value);
	Parameter(unsigned int& value);
	Parameter(std::string& value);
	Parameter(const Parameter& param);

	// empty desctructor
	~Parameter() {}

	// assigment for each parametertyp
	// these will set a value to the 
	// stored parameter!
	Parameter& operator = (bool value);
	Parameter& operator = (float value);
	Parameter& operator = (double value);
	Parameter& operator = (int value);
	Parameter& operator = (unsigned int value);
	Parameter& operator = (std::string value);

	// special func that will just do a normal
	// copy and no set!
	Parameter& operator = (const Parameter param);

	// easy cast functions
	bool asBool() const;
	float asFloat() const;
	double asDouble() const;
	int asInt() const;
	unsigned int asUInt() const;
	std::string asString() const;

	// util
	bool valid(const char* str) const;
	bool assign(const char* str);

	// getter
	ParameterType & type();
	ValueUnion & value();
	const ParameterType & type() const;
	const ValueUnion & value() const;

	// static stuff
	static bool isOption(const char* str);
	static bool isString(const char* str);
	static bool isBool(const char* str);
	static bool isNumber(const char* str);

	/** Convert a ascii number to a double, ignoring locale settings.*/
	static double asciiToDouble(const char* str);
	/** Convert a ascii number to a float, ignoring locale settings.*/
	static inline float asciiToFloat(const char* str) { return static_cast<float>(asciiToDouble(str)); }
	/** Detect first ascii POSITIVE number in string and convert to double.*/
	static double findAsciiToDouble(const char* str);
	/** Detect first ascii POSITIVE number in string and convert to double.*/
	static inline float findAsciiToFloat(const char* str) { return static_cast<float>(findAsciiToDouble(str)); }
	
};

#endif
