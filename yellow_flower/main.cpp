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


template<class C, class Cache>
inline
void print_workload_cache (C const& workload, Cache& cache) {
	std::cout << "cache capacity: " << cache.capacity() << std::endl
		 << "cache size: " << cache.size() << std::endl
		 << "workload size: " << workload.size() << std::endl
		 << std::endl;
}

void print_elapsed_time (std::chrono::time_point<std::chrono::system_clock> const& begin,
							std::chrono::time_point<std::chrono::system_clock> const& end) {
	std::chrono::duration<double> elapsed_seconds = end-begin;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
	std::cout << "finished computation at " << std::ctime(&end_time)
			  << "elapsed time: " << elapsed_seconds.count() << "s"
			  << " == "
			  << std::chrono::duration_cast<std::chrono::minutes>(elapsed_seconds).count() << "m " << (int)elapsed_seconds.count() % 60 << "s" << std::endl
			  << std::endl;
}

using cache_record_t = std::vector<std::tuple<std::size_t, std::size_t, double, std::size_t, double, double>>;

template<typename T>
constexpr char* type_name() { return "undefined_type_name"; }

template<>
constexpr char* type_name<fifo_cache_t<entry_t>>() { return "fifo_cache_t"; }

template<>
constexpr char* type_name<lru_cache_t<entry_t>>() { return "lru_cache_t"; }

template<>
constexpr char* type_name<lfu_cache_t<entry_t>>() { return "lfu_cache_t"; }


int main(int argc, char **argv) {
	using namespace std;
	workload_t<entry_t> workload{};
	{
		ifstream ifworkload{workload_path};
		if (!ifworkload) {
			cerr << "file NOT found" << endl;
			return -1;
		}
		cout << "file ok" << endl;
		workload.reserve(3000000);
		cout << "loading workload from file ..." << endl;
		get_workload(ifworkload, workload);
		cout << "loaded" << endl;
		/*{
			auto w = workload;
			sort(w.begin(), w.end());
			auto unique_last = unique(w.begin(), w.end());
			cout << "unique elements size in workload: " << distance(w.begin(), unique_last) << endl;
 		}*/
		cout << endl;
	}
	
	lru_cache_t<entry_t> cache{};
	cache_record_t cache_record{};
	for (size_t i = 1; i < 640000; i += 20000) {
	//for (size_t i = 1; i < 635000; i += 5000) {
	//for (size_t i = 600000; i < 700000; i *= 2) {
		size_t cache_capacity = i;
		cache.reserve(cache_capacity);
		
		print_workload_cache(workload, cache);
		
		std::chrono::time_point<std::chrono::system_clock> begin_time, end_time;
		begin_time = std::chrono::system_clock::now();
		size_t cache_misses = feed_cache(workload, cache);
		size_t warm_cache_misses = (cache_misses > cache.size()) ? cache_misses - cache.size() : 0;
		end_time = std::chrono::system_clock::now();
		
		std::chrono::duration<double> elapsed_seconds = end_time-begin_time;
		cache_record.emplace_back(cache.capacity(), cache_misses, (double)cache_misses/workload.size(), warm_cache_misses, (double)warm_cache_misses/workload.size(), elapsed_seconds.count());
		
		print_elapsed_time(begin_time, end_time);
		cout << "cache misses: " << cache_misses << " entries == " << (cache_misses * 100.0)/workload.size() << "% of workload's size" << endl;
		cout << "warm cache misses: " << warm_cache_misses << " entries == " << (warm_cache_misses * 100.0)/workload.size() << "% of workload's size" << endl;
		print_workload_cache(workload, cache);
		
		cache.clear();
		if (i == 1) --i;
		cout << "\n\n\n" << endl;
	}
	
	cout << "finished computation" << endl;
	
	{
		ofstream ofrecord{type_name<decltype(cache)>()};
		if (!ofrecord) {
			cerr << "coud NOT save file" << endl;
			return -1;
		}
		cout << "saving record to file ..." << endl;
		for (auto const& record : cache_record) {
			ofrecord << get<0>(record) << ' ' << get<1>(record) << ' ' << get<2>(record)
					 << ' ' << get<3>(record) << ' ' << get<4>(record) << ' ' << get<5>(record)
					 << '\n';
		}
		cout << "saved" << endl;
	}
	char c; cin >> c;
	return 0;
}