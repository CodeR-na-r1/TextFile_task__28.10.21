#pragma once
#include "TextFile.h"

TextFile::TextFile()
{
	filename = "";
	mode = std::ios_base::in;
}

TextFile::TextFile(const char* path)
{
	filename = path;
	mode = std::ios_base::in;
}

TextFile::TextFile(const char* path, std::ios_base::openmode r_mode)
{
	filename = path;
	mode = r_mode;
}

//метод копирования дописать файл2 в конец файла1
TextFile& TextFile::write_file2_to_file1(TextFile& file_2)
{
	ofstream out(this->filename, ios_base::app);

	ifstream second(file_2.filename, std::ios_base::in);
	string bufer;
	while (getline(second, bufer))
	{
		out << bufer << endl;
	}
	second.close();

	out.close();

	return *this;
}

//метод, позволяющий по данным нескольких файлов сформировать файл с общими строками
TextFile TextFile::add_file2(const char* filename_new_file, TextFile& file_2)
{
	TextFile res(filename_new_file, std::ios_base::out);
	res.write_file2_to_file1(*this);
	res.write_file2_to_file1(file_2);

	return res;
}

//метод, позволяющий по данным нескольких файлов сформировать файл с уникальными строками
TextFile TextFile::add_file2_unique(const char* filename_new_file, TextFile& file_2)
{
	TextFile res(filename_new_file, std::ios_base::out);

	string bufer;
	list<string> temp_list;

	ifstream in(this->filename, std::ios_base::in);
	while (getline(in, bufer))
	{
		temp_list.push_back(bufer);
	}
	in.close();

	in.open(file_2.filename, std::ios_base::in);
	while (getline(in, bufer))
	{
		temp_list.push_back(bufer);
	}
	in.close();

	temp_list.unique();

	ofstream out(res.filename, res.mode);
	for (list<string>::iterator it = temp_list.begin(); it != temp_list.end(); it++)
	{
		out << *it << endl;
	}
	out.close();

	return res;
}

//добавление данных к файлу, причем добавляются, только не повторяющиеся строки
TextFile& TextFile::operator +=(TextFile& tf)
{
	ifstream second(tf.filename, std::ios_base::in);

	list<string> temp_list;

	string bufer;
	while (getline(second, bufer))
	{
		temp_list.push_back(bufer);
	}
	second.close();

	temp_list.unique();

	ofstream first(this->filename, ios_base::app);
	for (list<string>::iterator it = temp_list.begin(); it != temp_list.end(); it++)
	{
		first << *it << endl;
	}
	first.close();

	return *this;
}

//в результате формируется файл, в котором объединены данные двух файлов, причем в результате объединения нет повторяющихся строки
TextFile TextFile::operator +(TextFile& tf)
{
	list<string> temp_list;

	ifstream first(this->filename, std::ios_base::in);
	string bufer;
	while (getline(first, bufer))
	{
		temp_list.push_back(bufer);
	}
	first.close();

	ifstream second(tf.filename, std::ios_base::in);
	while (getline(second, bufer))
	{
		temp_list.push_back(bufer);
	}
	second.close();

	temp_list.unique();
	
	TextFile res("raport.dat", std::ios_base::app);
	ofstream out(res.filename, res.mode);
	for (list<string>::iterator it = temp_list.begin(); it != temp_list.end(); it++)
	{
		out << *it << endl;
	}

	return res;
}

//удаляем строки, присутствующие во втором файле
TextFile& TextFile::operator -=(TextFile& tf)
{
	list<string> temp_list;

	ifstream first(this->filename, std::ios_base::in);
	string bufer;
	while (getline(first, bufer))
	{
		temp_list.push_back(bufer);
	}
	first.close();

	ifstream second(tf.filename, std::ios_base::in);
	while (getline(second, bufer))
	{
		delete_from_list(temp_list, bufer);
	}
	second.close();

	ofstream out(this->filename, std::ios_base::out);
	for (list<string>::iterator it = temp_list.begin(); it != temp_list.end(); it++)
	{
		out << *it << endl;
	}
	out.close();

	return *this;
}

//в результате формируется файл, в который не входят строки присутствующие как в первом, так и во втором файле
TextFile TextFile::operator -(TextFile& tf)
{
	list<string> temp_list;

	ifstream first(this->filename, std::ios_base::in);
	string bufer;
	while (getline(first, bufer))
	{
		temp_list.push_back(bufer);
	}
	first.close();

	ifstream second(tf.filename, std::ios_base::in);
	while (getline(second, bufer))
	{
		delete_from_list(temp_list, bufer);
	}
	second.close();

	TextFile res("raport.dat", ios_base::app);
	ofstream out(res.filename, res.mode);
	for (list<string>::iterator it = temp_list.begin(); it != temp_list.end(); it++)
	{
		out << *it << endl;
	}
	out.close();

	return res;
}

void TextFile::delete_from_list(list<string>& l, string& str)
{
	for (list<string>::iterator it = l.begin(); it != l.end(); it++)
	{
		if (*it == str)
		{
			l.erase(it);
			break;
		}
	}

	return;
}