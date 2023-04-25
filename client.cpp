#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define PORT     8080
#define MAXLINE 1024

   
// Driver code
int main() {
    int sockfd, serverportnumber;
    char buffer[MAXLINE];
    char hello[MAXLINE];
    struct sockaddr_in     servaddr;
    std::string serverhostname;
    bool first_time;
   
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));

    std::cout << "Enter the server host name: ";
    std::cin >> serverhostname;
    std::cout << std::endl;

    std::cout << "Enter the server port number: ";
    std::cin >> serverportnumber;
    std::cout << std::endl;
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serverportnumber);
    servaddr.sin_addr.s_addr = INADDR_ANY; //function(127.0.0.1)
       
    int n;
    socklen_t len;

    std::cin.getline(hello, MAXLINE);
    
    while(true){
        std::cout << "Enter a car license plate number: ";
        std::cin.getline(hello, MAXLINE);
        //std::cout << std::endl;

        if(strcmp(hello, "killsvc") == 0){
            sendto(sockfd, (const char *)hello, strlen(hello),
                MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                    sizeof(servaddr));
            std::cout << "Client terminates. Bye!" << std::endl;
            close(sockfd);
            break;
        }
        else{
            //std::cout << strlen(hello) << std::endl;
            sendto(sockfd, (const char *)hello, strlen(hello),
                MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                    sizeof(servaddr));
                
            n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                        MSG_WAITALL, (struct sockaddr *) &servaddr,
                        &len);
            buffer[n] = '\0';
            std::cout<<buffer<<std::endl;
        }

    }
   
    return 0;
}