except_targets = ["Init_bonobo2()"]

def print_data(array, type, defs, extern = false)
  if array[type]
    extern_def = "extern void" if extern
    print "##{defs} #{type}\n" if defs
    array[type].each do |val|
	   print "#{extern_def}   #{val};\n"
    end
    print "#endif\n" if defs
  end
end

inits = Hash.new

while gets
  if ~ /^(Init_.*\(.*\))(.*)/
	init = $1
	unless except_targets.include?(init)
	  flag = $2
	  if flag.size > 0
		if flag =~ /\/\*\s*(\w*)\s*\*\//
		  inits[$1] = Array.new unless inits[$1]
		  inits[$1] << init
		end
	  else
		inits[""] = Array.new unless inits[""]
		inits[""] << init
	  end
	end
  end
end

print_data(inits, "", nil, true)

print "void Init_bonobo_inits()\n"
print "{\n"
print_data(inits, "", nil)
print "}\n"
