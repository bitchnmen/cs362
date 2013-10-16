
#include "prime.h"

int main(int argc, char *argv[]){
    int sockfd, newsockfd, portno; // listen on sock_fd, new connection on new_fd, port number
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;  // my address information, connector's address information
    int n;
    int open = 1; //true


    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    //Socket setup
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    } 
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);             //port number (ex. 10.12.110.57 or thing-1.uwec.edu)
    serv_addr.sin_family = AF_INET;     // host byte order
    serv_addr.sin_port = htons(portno); // short, network byte order
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // use my IP address

    //Bind socket
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    //Listen for connection
    listen(sockfd,5);

    //Accept the connection
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0){
        error("ERROR on accept");
    }
    printf("Connection accepted!\n");

    // Variable to college the largest number in the range
    int maximum;

    // Collect the maximum
    cout << "\nEnter a Maximum:";
    cin >> maximum;
    cout << "\n";

    int *maxToSend = new int[1];
    maxToSend[0] = maximum;

    if(send(newsockfd, maxToSend, 10, 0) < 0){
        perror("ERROR sending to socket");
    }


    int maxSqrt = (int)sqrt((double)maximum);

    // Declare the array to hold important 
    // information and the numbers to sieve
    int *isComposite= new int[maximum+1]();

    // Insert the variable that keeps track of where we
    // are in the array, starting with 2 (the first prime)
    // which is held in isComposite[3]
    isComposite[0] = 3;

    // Run the sieve for each prime we come accross
    // until we reach the prime that is the square
    // root of the maximum (isComposite[2])
    while(isComposite[0] <= maxSqrt){

        // Unless it is the first time through
        // Receive from the client
        if(isComposite[0] > 3){
            if(recv(newsockfd, isComposite, (maximum+1)* sizeof(int), 0) < 0){
                perror("ERROR receiving from socket");
            }
        }

        // If we're not done:
        if(isComposite[0] <= maxSqrt){
            // Sieve the range
            sieve(isComposite, maximum, maxSqrt);
            isComposite[0]++;

            // Find the next prime
            while(isComposite[isComposite[0]] == 1){
                isComposite[0]++;
            }
            cout << "Doing next Sieve on: " << isComposite[0]-1 << endl;

        }

        // If we're still not done:
        if(send(newsockfd, isComposite, (maximum+1)* sizeof(int), 0) < 0){
            if(send(newsockfd, isComposite, maximum+1500, 0) < 0){
                perror("ERROR sending to socket");
            }
        }
    }
    return 0;
}