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
#include <vector.h>

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
	
	//set the timeout at 1 second for a reply
	sockfd.settimeout(1)
	
	//keeping count of the sequence count
	count = 1;
	
	//create a list to store trip times
	vector<int> times;

	//creating a while loop repeat continuoussly
	while(count<=10){
		//gets the current time
		start = time.clock();
		//assigning the message to a variable
		string message = "" + to_string(count);

		//sending message to the server
		sockfd.sendto(message.encode("utf-8"),(IP,PORT,0));

		//Excetption Handeling
		try{
			//recieving messages from the server
			message = "" + to_string(sockfd.recvfrom(1024)[0]);
			string addr = "" + to_string(sockfd.recvfrom(1024)[1]);
			//calculate and print elapsed time
			end = (time.clock() - start);
			times.push_back(end);
			cout << "Ping Number " << count << "Round Trip Time " << end << " Seconds" << endl;
			//if there is no reply within one second then it will time out
		}
		catch(socket.timout){
			cout << "Connection Timed Out on Ping Number " << count << endl;
		}
		count++;
	}
	//check if the count is 10 or not
	if(count > 10){
		cout << "Sent " << count << " Packets" << endl;
		cout << "Recieved " << times.length() << " Packets" << endl;
	}

	//calculating the packet loss rate
	string lossRate = to_string(10-times.length()*10)
	cout << "Packet Loss Rate: " << lossRate << endl;

	//calculate average response time
	double sum = 0;
	for(int i = 0; i<time.length(); i++)
		sum+=time[i];
	cout << "Average Response Time: " << to_string(double(sum/time.length())) << " seconds" << endl;
	return 0; 
} 