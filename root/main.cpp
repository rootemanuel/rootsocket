//
//  main
//  root
//
//  Created by Emanuel Root on 26/12/17.
//  Copyright © 2017 Emanuel Root. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT "6000"
#define BUFFER 1024
#define CONMAX 5

int error(const char *msg) {
    perror(msg);
    return EXIT_FAILURE;
}

int main() {
    
    socklen_t clilen;
    char buffer[BUFFER];
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd, newsockfd, portno, auxerror;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("#r00t err - socket");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("#r00t err - binding");
    }
    
    while (true) {
        
        listen(sockfd,CONMAX);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0){
            error("#r00t err - accept");
        }
        
        bzero(buffer,BUFFER);
        auxerror = read(newsockfd,buffer,BUFFER);
        
        if (auxerror < 0) {
            error("#r00t err - reading socket");
        }
        
        printf("#r00t msg - %s",buffer);
        auxerror = write(newsockfd,"#r00t - receiv msg",18);
        
        if (auxerror < 0){
            error("#r00t err - writing to socket");
        }
    }
    
    return EXIT_SUCCESS;
}
