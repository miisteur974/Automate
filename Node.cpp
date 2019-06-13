#include "Node.h"


vector<string> split(string line, char delim)
{
	vector<std::string> tokens;
	string token;
	istringstream tokenStream(line);
	while (getline(tokenStream, token, delim))
	{
		tokens.push_back(token);
	}
	return tokens;
}

string remove(string sample, char elem)
{
	string output;
	for (auto c : sample)
	{
		if (c != elem)
			output.push_back(c);
	}
	return output;
}

node::node(string alphabet,string name)
{
	this->node_name = name;
	this->next_nodes = map<string, node*>();
	this->alphabet_exception = alphabet;
	this->isFinal = false;
}

void node::setFinal()
{
	this->isFinal = true;
}

void node::linkTo(node* r_node, string condition)
{
	vector<string> sub_conditions = split(condition, ',');
	
	for (auto sb : sub_conditions) {
		this->next_nodes.insert(pair<string, node*>(sb, r_node));
		for (auto c : sb)
		{
			if (this->alphabet_exception.find(c) != string::npos)
				this->alphabet_exception = remove(this->alphabet_exception, c);
		}
	}
}

node* node::input(string input)
{

	if (this->alphabet_exception.find(input) != string::npos || input == " " || input.empty())
		if (this->next_nodes.size() > 0)
			return this->next_nodes.at("!");
		else
			return this;
	else
		return this->next_nodes.at(input);
}

string node::get_name()
{
	return this->node_name;
}

bool node::get_state()
{
	return this->isFinal;
}
