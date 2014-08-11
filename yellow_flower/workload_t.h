#ifndef WORKLOAD_T_H
#define WORKLOAD_T_H

#include <concepts.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstddef>
#include <unordered_map>

template<Regular T>
using workload_t = std::vector<T>;

std::istream& get_workload(std::istream& in, std::vector<std::string>& x) {
	using namespace std;
	string line{};
	while(getline(in, line)) x.push_back(line);
	return in;
}

std::istream& get_workload(std::istream& in, std::vector<int>& x) {
	using namespace std;
	unordered_map<string, int> map_line_id{};
	size_t next_line_id = 0;
	string line{};
	while(getline(in, line)) {
		auto pair_it = map_line_id.find(line);
		bool exists = pair_it != map_line_id.end();
		int entry = (exists) ? pair_it->second : next_line_id;
		x.push_back(entry);
		if (!exists) {
			map_line_id.emplace(line, next_line_id);
			++next_line_id;
		}
	}
	return in;
}

#endif