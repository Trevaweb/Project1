NAME:
	Trevor Weber

Files:
	server.c - Server that is able to translate incoming messages from a client from 
		normal words into pirate words or vice vice versa based off of arguments given 
		when starting the server.

	client.c - Connects to the server and is able to take user input to be translated 
			and printed out. 

	whatsgoingon.txt - explains what the functions do in the code.

	README.txt - this file

Compilation:
	server.c
		>gcc server.c -o server

	client.c
		>gcc client.c -o client

Running:
	
	translation arguments:
		-p - translates normal words into pirate words
		-n - translates pirate words into normal words 
	server.c
		>./server <translation argument>
	
	client.c 
		>./client <hostname>

Challenge:
	The biggest problem I faced was completing "Step 2". I had the code right for the most
	part but I was useing the incorrect sockets when trying to send and receive.
	Eventually I figured this out and got it working.

Not Working:
	N/A
