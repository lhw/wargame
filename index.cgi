#!/usr/bin/ruby1.8

require "mysql"
require "cgi"

print "Content-type: text/html; charset=utf-8\n\n"
print <<HEAD
<html>
	<head>
		<title>ring0 Wargame</title>
	</head>
	<body>
		<div style="display:box;background:lightgrey;text-align:leftmagin-left:30px;">
			<h3>Title</h3>
			<p>Some text I have to come up with</p>
		</div>

		<h4>Userlist</h4>
		<form action="index.cgi" method="POST">
			<input size="80" type="text" name="user" />
			<button type="submit">Search for User</button>
		</form>
		<table>
HEAD
begin
	db = Mysql.connect("localhost", "wargame", "N1gVyFXKL8Q0bG4Rl1ySaoP", "wargame")
	cgi = CGI.new
	if(cgi.params.length > 0)
		query = "select * from users where nick = '%s'" % cgi.params["user"]
	else
		query = "select * from users"
	end
	db.query(query) do |res|
		while line = res.fetch_row do
			print "\t\t\t<tr><td>%s</td></tr>\n" % line[0]
		end
	end
rescue Mysql::Error => e
	print "<div id=\"error\">%s</div>" % e.error
ensure 
	db.close if db
	print <<FOOT
		</table>
	</body>
</html>
FOOT
end
