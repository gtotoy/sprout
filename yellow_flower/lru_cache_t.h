#ifndef LRU_CACHE_T_H
#define LRU_CACHE_T_H

#include <concepts.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <list>

template<Regular T>
struct lru_cache_t {
	using size_type = std::size_t;
	using time_mark_t = std::size_t;
	using Map = std::unordered_map<T, time_mark_t>;
	using iterator = typename Map::iterator;
	
	Map map;
	
	lru_cache_t()=default;
	lru_cache_t(size_type capacity) : map(), time_mark_() {
		map.reserve(capacity);
		capacity_ = capacity;
	}
	
	size_type capacity() const { return capacity_; }
	size_type size() const { return map.size(); }
	void reserve(size_type new_capacity) {
		map.reserve(new_capacity);
		capacity_ = new_capacity;
	}
	void clear() { map.clear(); reset_time_mark(); }
	void reset_time_mark() { time_mark_ = time_mark_t(); }
	
	
	template <typename F, typename S>
	struct second_compare {
		bool operator()(std::pair<F, S> const& x, std::pair<F, S> const& y) {
			return x.second < y.second;
		}
	};
	
	inline
	// return cache_miss
	bool find(T const& x) {
		time_mark_t time_mark = time_mark_++;
		auto map_entry_it = map.find(x);
		bool cache_miss = map_entry_it == map.end();
		if (cache_miss) {
			bool full = map.size() == capacity();
			if (full) {
				auto replacement_it = std::min_element(map.begin(), map.end(),
					[](std::pair<T, time_mark_t> const& x, std::pair<T, time_mark_t> const& y){ return x.second < y.second; });
				map.erase(replacement_it);
			}
			map.insert({x, time_mark});
			return true;
		}
		map_entry_it->second = time_mark;
		return false;
	}
	
	size_type capacity_;
	time_mark_t time_mark_;
};


#endif