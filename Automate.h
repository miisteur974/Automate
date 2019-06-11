#pragma once
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef enum status {
	error,
	noresult,
	found
	} status;

class Automate
{
private:
	vector<node*> nodes;

public:
	int find_node(string node_name);
	Automate(string configuration_file, string alphabet);
	status send(string starting_node_name, string word);
};
