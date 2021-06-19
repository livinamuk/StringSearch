#include "Book.h"


Book::Book()
{
}

Book::Book(std::vector<Line> lines, int cellCount)
{
	m_lines = lines;
	m_cellCount = cellCount;
}

void Book::LoadFile(std::string filename, int cellCount, bool encrypted)
{
	// clear any previous data
	m_lines.clear();
	m_currentLine = 0;

	// Store for later
	m_cellCount = cellCount;

	// Load the file into a string
	std::ifstream t(filename);
	std::string contents((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	// Dencrypt if neccessary
	if (encrypted)
		contents = Encrypt(contents, m_encryptionKey);

	// Read the contents line by line
	std::istringstream iss(contents);
	for (std::string line; std::getline(iss, line); ) 
		{
		// Process each line
		std::vector<std::string> cells;
		//Line processedLine;
		for (int i = 0; i < m_cellCount; i++)
		{
			// search and split at comma 
			int findIndex;
			if (i < m_cellCount - 1)
				findIndex = line.find(',');
			// unless on last column
			else
				findIndex = -1;

			// save the text
			std::string text = line.substr(0, findIndex);
			cells.push_back(text);

			// remove the part you just extracted and search again
			line = line.substr(findIndex + 1, line.length());

			// quit searching if no more commas to be found (this will be if there are less columns than specified)
			if (findIndex == -1)
				break;
		}
		// Add the processed line to the book
		Book::m_lines.push_back(Line(cells));
	}

	// Print to test	
	for (Line line : Book::m_lines)
	{
		std::cout << line.GetAsString() << "\n";
	}
}

void Book::ExportToFile(std::string filename, bool encrypted)
{
	// Iterate over current book contents and build a giant string of it all
	std::string text;
	//for (Line& line : s_lines) {
	for (int i = 0; i < m_lines.size(); i++) 
	{
		text += m_lines[i].GetAsString();
		if (i < m_lines.size() - 1)
			text += "\n";
	}
	// Encrypt if neccessary
	if (encrypted)
		text = Encrypt(text, m_encryptionKey);

	//std::cout << text << "\n";
	//std::cout << Encrypt(text, s_encryptionKey) << "\n";

	// Save text to file
	std::ofstream outfile;
	outfile.open(filename, std::ofstream::out | std::ofstream::trunc);
	outfile << text;
	outfile.close();
}

std::string Book::Encrypt(std::string msg, std::string key)
{
	if (!key.size())
		return msg;
	for (std::string::size_type i = 0; i < msg.size(); ++i)
		msg[i] ^= key[i % key.size()];
	return msg;
}
int Book::GetLineCount()
{
	return m_lines.size();
}
void Book::NextLine()
{
	m_currentLine++;
	if (m_currentLine >= m_lines.size())
		m_currentLine = m_lines.size() - 1;
}
void Book::PreviousLine()
{
	m_currentLine--;
	if (m_currentLine <= 0)
		m_currentLine = 0;
}

void Book::GotoLine(int lineNumber)
{
	m_currentLine = lineNumber;
	if (m_currentLine <= 0)
		m_currentLine = 0;
	if (m_currentLine >= m_lines.size())
		m_currentLine = m_lines.size() - 1;
}

std::string Book::GetCurrentLine()
{
	return m_lines[m_currentLine].GetAsString();
}

std::string Book::GetCurrentLineCell(int cell)
{
	return m_lines[m_currentLine].GetCell(cell);
}

std::string Book::GetLine(int line)
{
	return m_lines[line].GetAsString();
}

std::string Book::GetLineCell(int line, int cell)
{
	return m_lines[line].GetCell(cell);
}

int Book::FindString(int begin, std::string text)
{
	if (begin < 0)
		begin = 0;

	std::string query = Util::ToLower(text);

	for (int i = begin; i < m_lines.size(); i++)
	{
		int pos = m_lines[i].GetAsLowercaseString().find(query);
		if (pos != std::string::npos)
			return i;
	}

	return -1;
}

int Book::FindStringInCell(int begin, std::string text, int cell)
{
	if (begin < 0)
		begin = 0;

	if (cell < 0 || cell >= m_cellCount)
		return -1;

	std::string query = Util::ToLower(text);

	for (int i = begin; i < m_lines.size(); i++)
	{
		std::string stringToSerach = Util::ToLower(m_lines[i].GetCell(cell));
		int pos = stringToSerach.find(query);
		if (pos != std::string::npos)
			return i;
	}

	return -1;
}

void Book::PrintContents()
{
	for (int i = 0; i < m_lines.size(); i++)
		std::cout << m_lines[i].GetAsString() << "\n";
}

Book Book::MultiSearchString(Book* book, std::string query)
{
	std::vector<Line> matchingLines;
	query = Util::ToLower(query);

	for (int i = 0; i < book->m_lines.size(); i++)
	{
		int pos = book->m_lines[i].GetAsLowercaseString().find(query);
		if (pos != std::string::npos)
			matchingLines.push_back(book->m_lines[i]);
	}

	return Book(matchingLines, book->m_cellCount);
}

Book Book::MultiSearchStringInCell(Book* book, std::string query, int cell)
{
	std::vector<Line> matchingLines;
	query = Util::ToLower(query);

	for (int i = 0; i < book->m_lines.size(); i++)
	{
		std::string stringToSerach = Util::ToLower(book->m_lines[i].GetCell(cell));
		int pos = stringToSerach.find(query);
		if (pos != std::string::npos)
			matchingLines.push_back(book->m_lines[i]);
	}
	return Book(matchingLines, book->m_cellCount);
}

std::string Book::Decrypt(std::string msg, std::string key)
{
	return Encrypt(msg, key);
}
