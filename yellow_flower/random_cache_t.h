#ifndef RANDOM_CACHE_T_H
#define RANDOM_CACHE_T_H

#include <concepts.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <random>

template<Regular T>
struct random_cache_t {
	using Container = std::vector<T>;
	using Map = std::unordered_map<T, T>;
	
	using iterator = typename Map::iterator;
	
	Container container;
	Map map;
	
	random_cache_t()=default;
	random_cache_t(std::size_t capacity) : container(capacity), map(), rd_{}, random_generator_{rd_()} {
		map.reserve(capacity);
	}
	
	std::size_t capacity() const { return container.capacity(); }
	std::size_t size() const { return container.size(); }
	void reserve(std::size_t new_capacity) {
		container.reserve(new_capacity);
		map.reserve(new_capacity);
		random_generator_ = std::mt19937{rd_()};
	}
	void clear() {
		container.clear();
		map.clear();
	}
	
	inline
	std::tuple<iterator, bool> find(T const& x) {
		auto map_entry_it = map.find(x);
		bool cache_miss = map_entry_it == map.end();
		if (cache_miss) {
			bool full = container.size() == capacity();
			if (full) {
				std::uniform_int_distribution<> dis(0, std::distance(container.begin(), container.end()) - 1);
				auto replacement_it = container.begin();
				std::advance(replacement_it, dis(random_generator_));
				map.erase(*replacement_it);
				*replacement_it = x;
			} else {
				container.push_back(x);
			}
			map.insert({x, x});
			return make_tuple(map.find(x), cache_miss);
		}
		return make_tuple(map_entry_it, false);
	}
	
private:
	std::random_device rd_;
    std::mt19937 random_generator_;
};

#endif