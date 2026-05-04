#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <cctype>
#include <limits>

static double parseValue(const std::string& s, bool& isFloat)
{
	if (s.size() == 1 && !std::isdigit(s[0]))
		return static_cast<double>(static_cast<unsigned char>(s[0]));

	if (s == "nan" || s == "nanf")
		return (isFloat = (s[s.size()-1] == 'f'), std::numeric_limits<double>::quiet_NaN());
	if (s == "+inf" || s == "+inff")
		return (isFloat = (s[s.size()-1] == 'f'), std::numeric_limits<double>::infinity());
	if (s == "-inf" || s == "-inff")
		return (isFloat = (s[s.size()-1] == 'f'), -std::numeric_limits<double>::infinity());
	bool hasF = !s.empty() && s[s.size()-1] == 'f';
	std::string prefix = hasF ? s.substr(0, s.size() - 1) : s;
	char* end;
	errno = 0;
	double val = std::strtod(prefix.c_str(), &end);
	if (errno == ERANGE || end == prefix.c_str() || *end != '\0')
		return std::numeric_limits<double>::quiet_NaN();
	isFloat = hasF;
	return val;
}

static std::string formatChar(double value)
{
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
		return "impossible";
	int intVal = static_cast<int>(value);
	if (intVal < 0 || intVal > 127)
		return "impossible";
	unsigned char c = static_cast<unsigned char>(intVal);
	if (!std::isprint(c))
		return "Non displayable";
	if (c == '\'' || c == '\\')
		return std::string("'\\") + static_cast<char>(c) + "'";
	return std::string("'") + static_cast<char>(c) + "'";
}

static std::string formatInt(double value)
{
	if (std::isnan(value) || std::isinf(value))
		return "impossible";
	if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		return "impossible";
	std::ostringstream ss;
	ss << static_cast<int>(value);
	return ss.str();
}

static std::string formatSpecialFloating(double value, bool isFloat)
{
	return std::string(std::isnan(value) ? "nan" : (value > 0 ? "+inf" : "-inf")) + (isFloat ? "f" : "");
}

static std::string formatFloating(double value, bool isFloat)
{
	if (std::isnan(value) || std::isinf(value))
		return formatSpecialFloating(value, isFloat);
	
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(1) << value;
	std::string result = ss.str();
	if (isFloat) result += 'f';
	return result;
}

void ScalarConverter::convert(const std::string& s)
{
	bool isFloat = false;
	double val = parseValue(s, isFloat);
	if (std::isnan(val)) {
		std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n";
		return;
	}
	std::cout << "char: " << formatChar(val) << std::endl;
	std::cout << "int: " << formatInt(val) << std::endl;
	std::cout << "float: " << formatFloating(val, true) << std::endl;
	std::cout << "double: " << formatFloating(val, false) << std::endl;
}
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}