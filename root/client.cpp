//
//  client.cpp
//  client
//
//  Created by Emanuel Root on 26/12/17.
//  Copyright © 2017 Emanuel Root. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define HOST "127.0.0.1"
#define PORT "6000"
#define BUFFER 1024

int error(const char *msg) {
    perror(msg);
    return EXIT_FAILURE;
}

int main() {
    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[BUFFER];
    
    portno = atoi(PORT);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0){
        error("#r00t err - opening socket");
    }
    
    server = gethostbyname(HOST);
    if (server == NULL) {
        fprintf(stderr,"#r00t err - no such host");
        return EXIT_FAILURE;
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("#r00t err - connecting");
    }
    
    printf("#r00t msg: ");
    bzero(buffer,BUFFER);
    fgets(buffer,BUFFER,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0){
        error("#r00t err - writing to socket");
    }
    
    bzero(buffer,BUFFER);
    n = read(sockfd,buffer,BUFFER);
    if (n < 0){
        error("#r00t err - reading from socket");
    }
    
    printf("%s\n",buffer);
    close(sockfd);
    
    return EXIT_SUCCESS;
}
