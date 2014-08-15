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
	using size_type = std::size_t;
	
	Container container;
	Map map;
	
	lru_cache_t()=default;
	lru_cache_t(size_type capacity) : container(capacity), map() {
		map.reserve(capacity);
		capacity_ = capacity;
	}
	
	size_type capacity() const { return capacity_; }
	size_type size() const { return container.size(); }
	void reserve(size_type new_capacity) {
		container.reserve(new_capacity);
		map.reserve(new_capacity);
		capacity_ = new_capacity;
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
				auto replacement_it = container.begin(); // older
				map.erase(*replacement_it);
				container.erase(replacement_it);
				container.push_back(x);
				//std::rotate(replacement_it, replacement_it + 1, container.end());
			} else {
				container.push_back(x);
			}
			map.insert({x, x});
			return make_tuple(map.find(x), cache_miss);
		}
		auto container_entry_it = std::find(container.begin(), container.end(), x);
		auto entry = *container_entry_it;
		container.erase(container_entry_it);
		container.push_back(std::move(entry));
		return make_tuple(map_entry_it, cache_miss);
	}
	
	size_type capacity_;
};


#endif