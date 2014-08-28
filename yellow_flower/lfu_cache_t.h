#ifndef LFU_CACHE_T_H
#define LFU_CACHE_T_H

#include <concepts.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <algorithm>

template<Regular T>
struct lfu_cache_t {
	using size_type = std::size_t;
	using Map = std::unordered_map<T, size_type>;
	using iterator = typename Map::iterator;
	
	Map map;
	
	lfu_cache_t()=default;
	lfu_cache_t(size_type capacity) : capacity_(capacity) {;}
	
	size_type capacity() const { return capacity_; }
	size_type size() const { return map.size(); }
	void reserve(std::size_t new_capacity) {
		map.reserve(new_capacity);
		capacity_ = new_capacity;
	}
	void clear() {
		map.clear();
	}
	
	inline
	// return cache_miss
	bool find(T const& x) {
		auto map_entry_it = map.find(x);
		bool cache_miss = map_entry_it == map.end();
		if (cache_miss) {
			bool full = map.size() == capacity();
			if (full) {
				auto replacement_it = min_element(map.begin(), map.end(),
					[](std::pair<T, size_type> const& x, std::pair<T, size_type> const& y){ return x.second < y.second; });
				map.erase(replacement_it);
			}
			map.insert({x, 1});
			return true;
		}
		++(map_entry_it->second);
		return false;
	}
	
private:
	size_type capacity_;
};

#endif