
#include "prime.h"

using namespace std;
int main(int argc, char *argv[]){

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int open = 1; //true
    char c = 'a';

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);  //parse port number

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;   // host byte order
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);  // short, network byte order


    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    int *maxToSend = new int[1];

    if(recv(sockfd, maxToSend, 10, 0) < 0){
        perror("ERROR receiving from socket");
    }

    int maximum = maxToSend[0];
    int maxSqrt = (int)sqrt((double)maximum);

    int *isComposite= new int[maximum+1]();

    while(isComposite[0] <= maxSqrt){

        if(read(sockfd, isComposite, (maximum+1)* sizeof(int)) < 0){
            perror("ERROR receiving from socket");
        }

        // Sieve the range
        sieve(isComposite, maximum, maxSqrt);
        isComposite[0]++;

        // Find the next prime
        while(isComposite[isComposite[0]] == 1){
            isComposite[0]++;
        }
        cout << "Doing next Sieve on: " << isComposite[0]-1 << endl;

        if(send(sockfd, isComposite, (maximum+1)* sizeof(int), 0) < 0){
            perror("ERROR sending to socket");
        }

    }

    close(sockfd);
	
	writeFile(isComposite, maximum);
	printWholeArray(isComposite, maximum);
	
    return(0);
}

