require "csv"
require "gnuplot"

filenames = ["fifo_cache_t", "lru_cache_t", "lfu_cache_t", "random_cache_t"]
ext = "eps"
workload_size = 3721736
tuple_descriptor = ["Cache capacity", "Cache misses", "Normalized cache misses", "Warm cache misses", "Normalized warm cache misses", "Time (in seconds)"]

(1...tuple_descriptor.size).each do |index|
	y_descriptor = index
	Gnuplot.open do |gp|
	  Gnuplot::Plot.new( gp ) do |plot|
		title = tuple_descriptor[y_descriptor] + " vs " + tuple_descriptor[0]
		plot.terminal ext
		plot.output File.expand_path("../" + title + "." + ext, __FILE__)
		
		plot.title  title + " (workload size: " + workload_size.to_s + " entries)"
		plot.xlabel tuple_descriptor[0]
		plot.ylabel tuple_descriptor[y_descriptor]
		
		filenames.each do |filename|
			if File.exists? filename then
				data = CSV.read(filename, {:col_sep => " "})
				x = data.collect { |tuple| tuple[0] }
				y = data.collect { |tuple| tuple[y_descriptor] }
				
				plot.data << Gnuplot::DataSet.new( [x, y] ) do |ds|
				  ds.with = "lines"
				  ds.title = filename
				end
			end
		end
	  end
	end
end