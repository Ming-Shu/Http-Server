# Http-Server
Implementing a minimal HTTP server in C

If want to run a normal Web server,suggest using Daemon as the fork().


An HTTP server is conceptually simple:

1.Create socket port ,and open port 80 for listening.

2.Browse send a request "GET /..." or "POST ..." massage to http server.

3.The http server response "HTTP/....." message(as a "HTTP/1.0 200 OK\r\nContent-Type:text/html\r\n\r\n") to browse.

4.The two most used HTTP methods are: GET and POST.

   GET - Requests data from a specified resource
   
   POST - Submits data to be processed to a specified resource
  
