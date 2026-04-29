#include "ScalarConverter.hpp"

#include <cerrno>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace {

bool isSpecialLiteral(const std::string& literal, double& value, bool& isFloat)
{
	if (literal == "nan" || literal == "nanf") {
		value = std::numeric_limits<double>::quiet_NaN();
		isFloat = (literal[literal.size() - 1] == 'f');
		return true;
	}
	if (literal == "+inf" || literal == "+inff") {
		value = std::numeric_limits<double>::infinity();
		isFloat = (literal[literal.size() - 1] == 'f');
		return true;
	}
	if (literal == "-inf" || literal == "-inff") {
		value = -std::numeric_limits<double>::infinity();
		isFloat = (literal[literal.size() - 1] == 'f');
		return true;
	}
	return false;
}

bool parseIntegerLiteral(const std::string& literal, long& value)
{
	char* end = 0;
	errno = 0;
	value = std::strtol(literal.c_str(), &end, 10);
	return errno != ERANGE && end != 0 && *end == '\0';
}

bool parseFloatingLiteral(const std::string& literal, double& value)
{
	char* end = 0;
	errno = 0;
	value = std::strtod(literal.c_str(), &end);
	return errno != ERANGE && end != 0 && *end == '\0';
}

std::string formatChar(double value)
{
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
		return "impossible";

	char c = static_cast<char>(static_cast<int>(value));
	if (!std::isprint(static_cast<unsigned char>(c)))
		return "Non displayable";

	std::string result("'");
	if (c == '\\' || c == '\'')
		result += '\\';
	result += c;
	result += '\'';
	return result;
}

std::string formatInt(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value < static_cast<double>(std::numeric_limits<int>::min())
		|| value > static_cast<double>(std::numeric_limits<int>::max()))
		return "impossible";

	std::ostringstream stream;
	stream << static_cast<int>(value);
	return stream.str();
}

std::string formatFloating(double value, bool isFloat)
{
	if (std::isnan(value))
		return isFloat ? "nanf" : "nan";
	if (std::isinf(value))
		return value > 0 ? (isFloat ? "+inff" : "+inf") : (isFloat ? "-inff" : "-inf");

	std::ostringstream stream;
	stream << value;
	std::string result = stream.str();
	if (result.find('.') == std::string::npos && result.find('e') == std::string::npos && result.find('E') == std::string::npos)
		result += ".0";
	if (isFloat)
		result += 'f';
	return result;
}

bool parseLiteral(const std::string& literal, double& value, bool& isFloat)
{
	if (literal.size() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0]))) {
		value = static_cast<unsigned char>(literal[0]);
		isFloat = false;
		return true;
	}
	if (isSpecialLiteral(literal, value, isFloat))
		return true;
	if (!literal.empty() && literal[literal.size() - 1] == 'f') {
		std::string prefix = literal.substr(0, literal.size() - 1);
		return parseFloatingLiteral(prefix, value) && (isFloat = true);
	}
	isFloat = false;
	long integerValue = 0;
	if (parseIntegerLiteral(literal, integerValue)) {
		value = static_cast<double>(integerValue);
		return true;
	}
	return parseFloatingLiteral(literal, value);
}

} // namespace

void ScalarConverter::convert(const std::string& literal)
{
	double value = 0.0;
	bool isFloat = false;

	if (!parseLiteral(literal, value, isFloat)) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	std::cout << "char: " << formatChar(value) << std::endl;
	std::cout << "int: " << formatInt(value) << std::endl;
	std::cout << "float: " << formatFloating(static_cast<float>(value), true) << std::endl;
	std::cout << "double: " << formatFloating(value, false) << std::endl;
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}