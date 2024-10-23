#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MESSAGE_LEN 1024

/*
El funcionamiento debe ser el siguiente: una vez establecida la conexión
el cliente lee una línea del archivo de entrada y se la envía al servidor
el servidor se la devuelve al cliente pasada a mayúsculas
el cliente la escribe en el archivo de salida
de vuelta al paso a, hasta que se termine el archivo.
*/

int main(int argc, char **argv){
    // Check if the args recieved from the command line are correct
    if(argc < 4){
        perror("\nIncorrect number of arguments\n");
        exit(EXIT_FAILURE);
    }

    // Declare the variables
    char *serverIP = argv[2];
    int portNum = atoi(argv[3]), clientSock;
    struct sockaddr_in clientSocketAddress;
    socklen_t socketSize = sizeof(struct sockaddr_in);
    char recievedMessage[MESSAGE_LEN];

    // Create the socket
    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSock < 0){
        perror("\nUnable to create socket\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the sockaddr_in struct
    if(inet_pton(AF_INET, serverIP, &clientSocketAddress.sin_addr) != 1){
        perror("\nError in IP conversion\n");
        exit(EXIT_FAILURE);
    }
    clientSocketAddress.sin_port = htons(portNum);
    clientSocketAddress.sin_family = AF_INET;

    // Solicit connection
    if(connect(clientSock, (struct sockaddr *) &clientSocketAddress, socketSize) == -1){
        perror("\nUnable to connect\n");
        exit(EXIT_FAILURE);
    }

    //Open file
    FILE* clientFile = fopen(argv[1], "r");
    if(clientFile == NULL){
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }
    char buffer[MESSAGE_LEN];

    return 0;
}
