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
	using Container = std::list<T>;
	using iterator = typename Container::iterator;
	using Map = std::unordered_map<T, iterator>;
	
	Map map;
	Container container;
	
	lru_cache_t()=default;
	lru_cache_t(size_type capacity) : map(), container() {
		map.reserve(capacity);
		capacity_ = capacity;
	}
	
	size_type capacity() const { return capacity_; }
	size_type size() const { return map.size(); }
	void reserve(size_type new_capacity) {
		map.reserve(new_capacity);
		capacity_ = new_capacity;
	}
	void clear() { map.clear(); container.clear(); }
	
	
	template <typename F, typename S>
	struct second_compare {
		bool operator()(std::pair<F, S> const& x, std::pair<F, S> const& y) {
			return x.second < y.second;
		}
	};
	
	inline
	// return cache_miss
	bool find(T const& x) {
		auto map_entry_it = map.find(x);
		bool cache_miss = map_entry_it == map.end();
		if (cache_miss) {
			bool full = map.size() == capacity();
			if (full) {
				auto replacement_it = --container.end();
				map.erase(*replacement_it);
				*replacement_it = x;
				container.splice(container.begin(), container, replacement_it); // replacement_it is not invalidated
			} else {
				container.push_front(x);
			}
			map.insert({x, container.begin()});
			return true;
		}
		container.splice(container.begin(), container, map_entry_it->second); // map_entry_it->second is not invalidated
		return false;
	}
	
	size_type capacity_;
};


#endif