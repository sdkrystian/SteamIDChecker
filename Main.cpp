#include "stdafx.h"
#include "windows.h"
#include <urlmon.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem>
#pragma comment(lib, "urlmon.lib")

std::string getPageContent(std::string url);

void main()
{
	std::ifstream infile(std::experimental::filesystem::current_path().string() + "\\words.txt");
	std::ofstream outfile(std::experimental::filesystem::current_path().string() + "\\output.txt");
	std::string line;
	while (getline(infile, line))
	{
		if (getPageContent(line).find(":: Error</title>") != std::string::npos)
		{
			std::cout << "ID: " << line << std::endl;
			outfile << "ID: " << line << std::endl;
		}
	}
	outfile.close();
}

std::string getPageContent(std::string id)
{
	std::wstring url = L"https://steamcommunity.com/id/" + std::wstring(id.begin(), id.end());
	std::wstring path = std::experimental::filesystem::current_path().wstring() + L"\\cur.html";
	URLDownloadToFile(NULL, url.c_str(), path.c_str(), 0, NULL);
	return std::string((std::istreambuf_iterator<char>(std::ifstream(path))), std::istreambuf_iterator<char>());
}

