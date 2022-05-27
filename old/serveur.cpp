#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctime>
#include <chrono>

void showtime() {
    time_t actuel = std::time(0);
    tm *time=std::localtime(&actuel);
    std::cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec;
}

int main()
{
    // Création du socket pour le serveur
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
	{
		std::cout << "Erreur creation socket : "<< std::endl;
		return -1;
	} 
	
    // Définition des caractéristiques du serveur
    sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
    int port;
    std::cout << "Port de connexion: ";
    std::cin >> port;
	server.sin_port = htons(port);
	
    // Liaison du socket avec le serveur
    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) == -1)
	{
		std::cout << "[ERROR] port already used " << std::endl;
		return -1;
	}
    // Prépare le socket à écouter les prochaines connections
    listen(sock,5);

    // Ici le programme va attendre jusqu'à ce que quelqu'un essaye de se connecter
    sockaddr client;
    socklen_t clientLenght = sizeof(client);
    
    int clientSock ;

    char buffer[256];
    int n;
    while(1) {
        std::cout << "Waiting for connection.." << std::endl;
        clientSock= accept(sock, (struct sockaddr *) &client, &clientLenght);
        if( clientSock< 0) {
            std::cout << "Error on accept" << std::endl;
            return -1; 
        }

        bzero(buffer,256);
        n = read(clientSock,buffer,255);
        time_t actuel = std::time(0);
        tm *time=std::localtime(&actuel);
        if (n < 0) std::cout <<"[ERROR] reading from socket" << std::endl;
        std::cout << "[";
        showtime();
        std::cout <<"] " << buffer << std::endl;
    }

    return 0;
}