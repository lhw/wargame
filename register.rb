#!/usr/bin/ruby

puts "Only supply username" and exit if ARGV.length != 1 

c = ('a'..'z').to_a + ('A'..'Z').to_a + ('0'..'9').to_a
pw = ""
salt = ""

0.upto(8) {|i| pw << c[rand(c.size)] }
c += ['/', '.']
0.upto(12) {|i| salt << c[rand(c.size)] }

print "User login: %s\n" % ARGV[0]
print "User password: %s\n" % pw = pw.crypt(salt)

%x{/usr/sbin/useradd -b /tmp -m -G level1 -p #{pw} #{ARGV[0]}
