#include "Line.h"

Line::Line(std::vector<std::string> cells)
{
	m_cells = cells;
	CalculateString();
}

std::string Line::GetCell(int cell)
{
	if (cell < 0 || cell >= m_cells.size())
		return "";
	else
		return m_cells[cell];
}

std::string Line::GetAsString()
{
	return m_string;
}

std::string Line::GetAsLowercaseString()
{
	return m_lowerCaseString;
}


void Line::CalculateString()
{
	m_string = "";
	for (int i = 0; i < m_cells.size(); i++)
	{
		m_string += m_cells[i];
		if (i < m_cells.size() - 1)
			m_string += ",";
	}

	// create lower case version
	m_lowerCaseString = Util::ToLower(m_string);
}