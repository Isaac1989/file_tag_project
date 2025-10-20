#pragma once

#include <cctype>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <chrono>


std::string str_to_lower(const std::string &str);
bool containsSubStr(const std::string &s, const std::string &sub);
void runFileSystemTests();
void tesingFoldersAndFiles();
long long serialize_time_point(const std::chrono::system_clock::time_point& tp);
std::chrono::system_clock::time_point deserialize_time_point(long long milliseconds_count);