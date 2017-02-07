require 'humanize'

#note: removed reagan and carter because they both clash with previous presidents
presidents = {"roosevelt" => 18, "truman" => 20, "eisenhower" => 5, 
	"kennedy" => 11, "johnson" => 10, "nixon" => 14, "ford" => 6, 
	"carter" => 3, "bush" => 2, "obama" => 15}

#fill in the 'missing' indices into the presidents' hash
for i in 0..32
	if !presidents.has_value?(i)
		presidents.merge!(i.humanize => i)
	end
end

prez = presidents.invert
prez.keys.sort.each {|k| puts prez[k]}