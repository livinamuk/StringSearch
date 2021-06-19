#pragma once
#include "Header.h"
#include "Line.h"


class Book
{
public: // methods
	Book();
	Book(std::vector<Line> lines, int cellCount); 
	void LoadFile(std::string filename, int cellCount, bool encrypted);
	void ExportToFile(std::string filename, bool encrypted);
	std::string Decrypt(std::string msg, std::string key);
	std::string Encrypt(std::string msg, std::string key);

	int GetLineCount();
	void NextLine();
	void PreviousLine();
	void GotoLine(int line);
	std::string GetCurrentLine();
	std::string GetCurrentLineCell(int cell);
	std::string GetLine(int line);
	std::string GetLineCell(int line, int cell);
	int FindString(int begin, std::string text);
	int FindStringInCell(int begin, std::string text, int cell);
	void PrintContents();

private: // fields
	std::vector<Line> m_lines;
	int m_cellCount = 0;
	int m_currentLine = 0;
	std::string m_encryptionKey = "cba";

public: // static functions
	static Book MultiSearchString(Book* book, std::string query);
	static Book MultiSearchStringInCell(Book* book, std::string query, int cell);
};

