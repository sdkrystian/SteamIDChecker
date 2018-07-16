// Copyright 2018 Krystian Stasiowski

#include <experimental/filesystem>
#include <urlmon.h>
#include <windows.h>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "urlmon.lib")

std::string GetPageContent(std::string id)
{
  std::string path = std::experimental::filesystem::current_path().string() + "\\cur.html";
  URLDownloadToFile(NULL, ("https://steamcommunity.com/id/" + id).c_str(), path.c_str(), 0, NULL);
  std::ifstream stream(path);
  std::string output((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  remove(path.c_str());
  return output;
}

void main()
{
  std::ifstream infile(std::experimental::filesystem::current_path().string() + "\\words.txt");
  std::string line;
  while (getline(infile, line))
  {
    if (GetPageContent(line).find(":: Error</title>") != std::string::npos)
    {
      std::ofstream outfile(std::experimental::filesystem::current_path().string() + "\\output.txt", std::ios::app);
      std::cout << "ID: " << line << std::endl;
      outfile << "ID: " << line << std::endl;
      outfile.close();
    }
  }
}
