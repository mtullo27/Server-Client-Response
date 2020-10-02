// UDP Pinger

// Must have this server running before you can run the UDP Pinger Client code

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <vector>

using namespace std;

#define PORT	 12000
#define IP		 '127.0.0.1'

int main() { 
	int sockfd, count;
	clock_t start, end;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr; 
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	//set the timeout at 1 second for a reply
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if(setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	  perror("setsockopt failed\n");
	
	//keeping count of the sequence count
	count = 1;
	
	//create a list to store trip times
	vector<double> times;

	//creating a while loop repeat continuoussly
	while(count<=10){
		//gets the current time
	        start = time(0);

		//sending message to the server
		sendto(sockfd, (const char *) buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
		//recieving messages from the server
		int n;
	        n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
		//calculate and print elapsed time
		double total = (double)difftime(time(0), start);
		//timeout handling
		if(total >= 1.0){
		  cout << "Connection Time out on Ping Number " << count << endl;
		}
		//it works
		else{
		  times.push_back(end);
		  cout << "Ping Number " << count << "Round Trip Time " << end << " Seconds" << endl;
		}
		count++;
	}
	//check if the count is 10 or not
	if(count > 10){
		cout << "Sent " << count << " Packets" << endl;
		cout << "Recieved " << times.size() << " Packets" << endl;
	}

	//calculating the packet loss rate
	string lossRate = to_string(10-times.size()*10);
	cout << "Packet Loss Rate: " << lossRate << endl;

	//calculate average response time
	double sum = 0;
	for(int i = 0; i<times.size(); i++)
	  sum+=times[i];
	cout << "Average Response Time: " << to_string(double(sum/times.size())) << " seconds" << endl;
	return 0; 
} 
