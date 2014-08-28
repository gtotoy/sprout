#ifndef FIFO_CACHE_T_H
#define FIFO_CACHE_T_H

#include <concepts.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>

template<Regular T>
struct fifo_cache_t {
	using Container = std::vector<T>;
	using Map = std::unordered_map<T, T>;
	
	using iterator = typename Map::iterator;
	
	Container container;
	Map map;
	
	fifo_cache_t()=default;
	fifo_cache_t(std::size_t capacity) : container(capacity), map() {
		map.reserve(capacity);
		replacement_it_ = container.begin();
	}
	
	std::size_t capacity() const { return container.capacity(); }
	std::size_t size() const { return container.size(); }
	void reserve(std::size_t new_capacity) {
		container.reserve(new_capacity);
		map.reserve(new_capacity);
		replacement_it_ = container.begin();
	}
	void clear() {
		container.clear();
		map.clear();
	}
	
	inline
	// return cache_miss
	bool find(T const& x) {
		auto map_entry_it = map.find(x);
		bool cache_miss = map_entry_it == map.end();
		if (cache_miss) {
			bool full = container.size() == capacity();
			if (full) {
				map.erase(*replacement_it_);
				*replacement_it_ = x;
				{
					++replacement_it_; // assuming iterators are always valid (cache is not going to expand and invalidate iterators)
					if (replacement_it_ == container.end()) replacement_it_ = container.begin();
				}
			} else {
				container.push_back(x);
			}
			map.insert({x, x});
			return true;
		}
		return false;
	}
	
	private:
	typename Container::iterator replacement_it_;
};

#endif