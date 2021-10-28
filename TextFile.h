#pragma once
#include <fstream>
#include <string>
#include <list>

using namespace std;

class TextFile
{
	const char* filename;
	std::ios_base::openmode mode;

	void delete_from_list(list<string>& l, string& str);

public:
	TextFile();
	TextFile(const char* path);
	TextFile(const char* path, std::ios_base::openmode r_mode);

	TextFile& write_file2_to_file1(TextFile& file_2);
	TextFile add_file2(const char* filename_new_file, TextFile& file_2);
	TextFile add_file2_unique(const char* filename_new_file, TextFile& file_2);

	TextFile& operator +=(TextFile& tf);
	TextFile operator +(TextFile& tf);
	TextFile& operator -=(TextFile& tf);
	TextFile operator -(TextFile& tf);
};