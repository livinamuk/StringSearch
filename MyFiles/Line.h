#pragma once
#include "Header.h"

class Line
{
public:
	Line(std::vector<std::string> cells); 
	std::string GetCell(int cell);
	std::string GetAsString();
	std::string GetAsLowercaseString();

private:
	void CalculateString();
	std::vector<std::string> m_cells;
	std::string m_string = "";
	std::string m_lowerCaseString = "";
};