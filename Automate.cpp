#include "Automate.h"

int Automate::find_node(string node_name)
{
	int i = 0;
	for (auto node : this->nodes)
	{
		if (node->get_name() == node_name)
			return i;
		i++;
	}
	return -1;
}

Automate::Automate(string configuration_file, string alphabet)
{
	this->nodes = vector<node*>();
	string line;
	fstream file;
	vector<string> args, condition;
	file.open(configuration_file, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line[0] == '#' || line[0] == '\n' || line[0] == ' ' || line[0] == '\r' || line.empty())
				continue;
			else
			{
				args = split(line, ' ');
				if (this->find_node(args[0]) != -1)
				{
					node* tmp = this->nodes[this->find_node(args[0])];
					condition = split(args[1], '>');
					if (condition[0] == "@")
					{
						tmp->setFinal();
						continue;
					}
					if (this->find_node(condition[1]) == -1)
						this->nodes.emplace_back(new node(alphabet, condition[1]));
					tmp->linkTo(nodes[this->find_node(condition[1])], condition[0]);
				}
				else
				{
					node* tmp = new node(alphabet, args[0]);
					condition = split(args[1], '>');
					if (condition[0] == "@")
					{
						this->nodes.emplace_back(tmp);
						tmp->setFinal();
						continue;
					}
					if (this->find_node(condition[1]) == -1)
						this->nodes.emplace_back(new node(alphabet,condition[1]));
					
					tmp->linkTo(nodes[this->find_node(condition[1])], condition[0]);
					this->nodes.emplace_back(tmp);
				}
			}
		}
		else {
			cout << " Can't open " << configuration_file << " ! " << endl;
		}
		file.close();
	}
}

status Automate::send(string starting_node_name, string word)
{
	const int node_position = this->find_node(starting_node_name);
	if (node_position != -1)
	{
		node* cur_node = this->nodes[node_position];
		int cursor = 0;
		string tmp;
		while (word[cursor] != 0)
		{
			tmp = word[cursor];
			cur_node = cur_node->input(tmp);
			cursor++;
		}
		if (cur_node->get_state())
			return found;
		return noresult;
	}
	cout << starting_node_name << " does not exists in your configuration !" << endl;
	return error;
}
