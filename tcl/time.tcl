# time.tcl - tiny CGI script.
if {![info exists env(QUERY_STRING)]} {
    set env(QUERY_STRING) ""
}
puts "Content-type: text/html\n"
puts "<html><head><title>Tiny CGI time server</title></head>
<body><h1>Time server</h1>
Time now is: [clock format [clock seconds]]
<br>
Query was: $env(QUERY_STRING)
<hr>
<a href=index.htm>Index</a>
</body></html>"
