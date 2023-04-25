#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
using namespace std;
   
#define PORT     8080
#define MAXLINE 1024


//port number = 5353
   
// Driver code
int main() {
    int sockfd, serverportnumber;
    char buffer[MAXLINE];
    char test[MAXLINE];
    char hello[MAXLINE];
    char char_test[MAXLINE];
    ifstream file_name;
    string filename, line;
    vector<string> lines;
    bool exists;

    cout << "Enter file name: ";
    cin >> filename;
    cout << endl;
    file_name.open(filename);
    if(!file_name.is_open()){
        cout << "File is not open!" << endl;
        return -1;
    }
    while(getline(file_name, line)){
        line.erase(line.size()-1);
        lines.push_back(line);
    }

    /*for(int i = 0; i < lines.size(); i++){
        cout << lines[i] << " " << lines[i].size() << endl;
        //lines[i].erase(lines[i].size()-1);
    }*/

    cout << "Enter the server port number: ";
    cin >> serverportnumber;


    struct sockaddr_in servaddr, cliaddr;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(serverportnumber);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    socklen_t len;
    int n;
   
    len = sizeof(cliaddr);  //len is value/result

    //cout << "len of len: " << len << endl;

    while(true){
        exists = false;
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    &len);


        buffer[n] = '\0';
        //printf("Client : %s\n", buffer);


        if(strcmp(buffer, "killsvc") == 0){
            cout << "Recieved request to termainte the service" << endl;
            cout << "Bye!" << endl;
            break;
        }
        else{
            for(int i = 0; i < lines.size(); i ++){
                strcpy(char_test, lines[i].c_str());
                if(strcmp(buffer, char_test) == 0){
                    exists = true;
                    break;
                }
                else{
                    continue;
                }
            }
            if(exists){
                string holder = "";
                cout << buffer << ": Reported as stolen." << endl;
                holder += buffer;
                holder += ": Reported as stolen.";
                strcpy(hello, holder.c_str());
                sendto(sockfd, (char *)hello, strlen(hello), 
                    MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                        len);
            }
            else{
                string holder = "";
                cout << buffer << ": Not in the database." << endl;
                holder += buffer;
                holder += ": Not in the database.";
                strcpy(hello, holder.c_str());
                sendto(sockfd, (char *)hello, strlen(hello), 
                    MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                        len);
            }
        }
    }
       
    return 0;
}