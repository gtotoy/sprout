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
	using Pair = std::pair<T, std::size_t>;
	using Container = std::vector<Pair>;
	
	using iterator = typename Container::iterator;
	
	Container container;
	
	lfu_cache_t()=default;
	lfu_cache_t(std::size_t capacity) : container(capacity) {;}
	
	std::size_t capacity() const { return container.capacity(); }
	std::size_t size() const { return container.size(); }
	void reserve(std::size_t new_capacity) {
		container.reserve(new_capacity);
	}
	void clear() {
		container.clear();
	}
	
	inline
	std::tuple<iterator, bool> find(T const& x) {
		auto first = container.begin();
		auto last = container.end();
		auto container_entry_it = last;
		while(first != last) {
			if (first->first == x) {
				container_entry_it = first;
				break;
			}
			++first;
		}
		bool cache_miss = container_entry_it == container.end();
		if (cache_miss) {
			bool full = container.size() == capacity();
			if (full) {
				auto replacement_it = min_element(container.begin(), container.end(),
					[](Pair const& x, Pair const& y){ return x.second < y.second; });
				*replacement_it = {x, 1};
				return make_tuple(replacement_it, cache_miss);
			} else {
				container.push_back({x, 1});
				return make_tuple(container.end() - 1, cache_miss);
			}
		} else {
			++container_entry_it->second;
		}
		return make_tuple(container_entry_it, cache_miss);
	}
};

#endif