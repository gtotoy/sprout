#ifndef LRU_CACHE_T_H
#define LRU_CACHE_T_H

#include <concepts.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>

template<Regular T>
struct lru_cache_t {
	using Container = std::vector<T>;
	using Map = std::unordered_map<T, T>;
	
	using iterator = typename Map::iterator;
	
	Container container;
	Map map;
	
	lru_cache_t()=default;
	lru_cache_t(std::size_t capacity) : container(capacity), map() {
		map.reserve(capacity);
	}
	
	std::size_t capacity() const { return container.capacity(); }
	std::size_t size() const { return container.size(); }
	void reserve(std::size_t new_capacity) {
		container.reserve(new_capacity);
		map.reserve(new_capacity);
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
				auto replacement_it = container.begin();
				map.erase(*replacement_it);
				*replacement_it = x;
				std::rotate(replacement_it, replacement_it + 1, container.end());
			} else {
				container.push_back(x);
			}
			map.insert({x, x});
			return make_tuple(map.find(x), cache_miss);
		}
		return make_tuple(map_entry_it, cache_miss);
	}
};


#endif