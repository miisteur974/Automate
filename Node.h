#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

/**
 * \brief 
 * \param line line to split
 * \param delim delimiter
 * \return vector containing substrings
 */
vector<string> split(string line, char delim);
string remove(string sample, char elem);

class node
{
private:
	string node_name;
	map<string,node*> next_nodes;
	string alphabet_exception;
	bool isFinal;
public:
	node(string alphabet, string name);
	void setFinal();
	void linkTo(node* r_node, string condition);
	node* input(string input);
	string get_name();
	bool get_state();
};