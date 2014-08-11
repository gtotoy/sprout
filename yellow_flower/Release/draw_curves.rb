require "csv"
require "gnuplot"

filenames = ["fifo_cache_t", "lru_cache_t", "lfu_cache_t"]
ext = "pdf"
tuple_descriptor = ["Cache capacity", "Cache misses", "Warm cache misses", "Time (in seconds)"]
y_descriptor = 3

Gnuplot.open do |gp|
  Gnuplot::Plot.new( gp ) do |plot|
	title = tuple_descriptor[y_descriptor] + " vs " + tuple_descriptor[0]
	plot.terminal ext
    plot.output File.expand_path("../" + title + "." + ext, __FILE__)
	
    plot.title  title
    plot.xlabel tuple_descriptor[0]
    plot.ylabel tuple_descriptor[y_descriptor]
    
	filenames.each do |filename|
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