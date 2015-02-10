# ConsoleScannerPort
Application to poll the network ports on your computer.
Official website: http://java-virys.narod.ru
***
#####Command:#####
>>>Description  

#####-s(Scan):#####
>>>This parameter is used to scan a single IP or to display the status of a particular port. For multi-threaded scanning use the key -t, transmit only after the -s.To conduct the scan report, use the key -r, transmit only after the -s will create a text file in the working directory with the name of the current time.  

                EXAMPLES:  

				 qnetscan -s 127.0.0.1:1234(Check the port as directed by ip)
				 
				 qnetscan -s 192.168.1.1(Scan all ports at the direction of ip)
				 
				 qnetscan -s -t 192.168.1.1(Scan all ports at the direction of ip, using multithreading)
				 
				 qnetscan -s -t -r 192.168.1.1(Scan all ports at the direction of ip, using multi-threading and the introduction of the log) 

#####-a(Scan all ip):#####
>>>This parameter is used to scan all IP for open ports.For multi-threaded scanning use the key -t, transmit only after the -a.To conduct the scan report, use the key -r, transmit only after the -a will create a text file in the working directory with the name of the current time.  

                EXAMPLES:  
				 
				 qnetscan -a(Scan all ip)
				 
				 qnetscan -a -r(scan all ip with logging)
				 
				 qnetscan -a -r -t(scan all ip with logging and multithreading)  

#####-i(Get all ip):#####
>>>This parameter is used for all IP.  

				EXAMPLES:

				 qnetscan -i  
