#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstddef>
#include <chrono>
#include <workload_t.h>
#include <fifo_cache_t.h>
#include <lru_cache_t.h>
#include <lfu_cache_t.h>

const std::string workload_path = "workload.txt";
//using entry_t = std::string;
using entry_t = int;


template<class C, class Cache>
inline
std::size_t feed_cache(C const& workload, Cache& cache) {
	using namespace std;
	size_t cache_misses = 0;
	for (auto& entry : workload) {
		typename Cache::iterator entry_it;
		bool cache_miss;
		tie(entry_it, cache_miss) = cache.find(entry);
		if (cache_miss) ++cache_misses;
	}
	return cache_misses;
}


int main(int argc, char **argv) {
	using namespace std;
	workload_t<entry_t> workload{};
	{
		ifstream ifworkload{workload_path};
		if (!ifworkload) {
			cerr << "file NOT found." << endl;
			return -1;
		}
		cout << "file ok" << endl;
		workload.reserve(3000000);
		cout << "loading workload from file..." << endl;
		get_workload(ifworkload, workload);
		/*{
			auto w = workload;
			sort(w.begin(), w.end());
			auto unique_last = unique(w.begin(), w.end());
			cout << "unique elements size in workload: " << distance(w.begin(), unique_last) << endl;
 		}*/
		cout << endl;
	}
	
	lru_cache_t<entry_t> cache{};
	//for (size_t i = 1; i < 2000000; i *= 2) {
	for (size_t i = 600000; i < 700000; i *= 2) {
		size_t cache_capacity = i;
		cache.reserve(cache_capacity);
		
		cout << "cache capacity: " << cache_capacity << endl
			 << "cache size: " << cache.size() << endl
			 << "workload size: " << workload.size() << endl
			 << endl;
		
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();
		size_t cache_misses = feed_cache(workload, cache);;
		end = std::chrono::system_clock::now();
	 
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		
		std::cout << "finished computation at " << std::ctime(&end_time)
				  << "elapsed time: " << elapsed_seconds.count() << "s"
				  << " == "
				  << chrono::duration_cast<chrono::minutes>(elapsed_seconds).count() << "m " << (int)elapsed_seconds.count() % 60 << "s" << endl
				  << endl;
		cout << "cache misses: " << cache_misses << " entries == " << (cache_misses * 100.0)/workload.size() << "% of workload's size" << endl;
		size_t warm_cache_misses = (cache_misses > cache.size()) ? cache_misses - cache.size() : 0;
		cout << "warm cache misses: " << warm_cache_misses << " entries == " << (warm_cache_misses * 100.0)/workload.size() << "% of workload's size" << endl;
		cout << "cache capacity: " << cache_capacity << endl;
		cout << "cache size: " << cache.size() << endl;
		
		cache.clear();
		cout << "\n\n\n" << endl;
	}
	
	cout << "finished computation" << endl;
	char c; cin >> c;
	return 0;
}