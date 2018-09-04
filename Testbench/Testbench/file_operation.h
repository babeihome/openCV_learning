#pragma once
#include <io.h>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

void getFiles(string path, vector<string>& files);
void getAllFileListFromDirectory(string path, vector<string> &files);