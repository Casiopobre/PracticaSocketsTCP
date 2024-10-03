#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MESSAGE_LEN 30
#define SERVER_IP "127.0.0.1"

int main(int argc, char **argv){
    // Check if the args recieved from the command line are correct
    if(argc != 2){
        perror("\nIncorrect number of arguments\n");
        exit(EXIT_FAILURE);
    }

    // Declare the variables
    int portNum = atoi(argv[1]), clientSock;
    struct sockaddr_in clientSocketAddress;
    socklen_t socketSize = sizeof(struct sockaddr_in);
    char recievedMessage[MESSAGE_LEN];

    // Create the socket
    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSock < 0){
        perror("\nUnable to create socket\n");
        exit(EXIT_FAILURE);
    }

    // Initialize tthe sockaddr_in struct
    inet_pton(AF_INET, SERVER_IP, &clientSocketAddress.sin_addr);
    clientSocketAddress.sin_port = portNum;

    // Solicit connection
    connect(clientSock, (struct sockaddr *) &clientSocketAddress, socketSize);

    // Recieve message
    ssize_t bytesReceived = recv(clientSock, recievedMessage, MESSAGE_LEN, 0);
    if(bytesReceived == -1){
        perror("\nUnable to send message\n");
        exit(EXIT_FAILURE);
    }
    if(bytesReceived == 0){
        perror("\nConnection socket closed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nBytes sent: %ld\n", bytesReceived);

    // Close socket
    close(clientSock);
    
    return 0;
}
