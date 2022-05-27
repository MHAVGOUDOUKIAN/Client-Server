#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

int main () {
    sockaddr_in host_addr; // Adresse du serveur
    hostent* host; // Informations sur le serveur
    int sock = socket(AF_INET, SOCK_STREAM, 0); // Le socket

    // Demande à l'utilisateur, à qui il souhaite se connecter
    std::string str;
    std::cout << "Bonjour, vous aller vous connecter" << std::endl;
    std::cout << "Hostname: ";
    std::cin >> str ;

    // Recherche des informations sur le poste serveur spécifié
    host = gethostbyname(str.c_str());
    if(host == NULL) {
        std::cout << "[ERROR] no such host" << std::endl;
        return -1;
    }

    // Définition des caractéristiques du serveur
    int port;
    std::cout << "Port: ";
    std::cin >> port;
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    bcopy((char*) host->h_addr, (char*)&host_addr.sin_addr.s_addr, host->h_length);

    // Tentative de connection au serveur
    if(connect(sock, (struct sockaddr *) &host_addr, sizeof(host_addr)) < 0) {
        std::cout << "[ERROR] connection impossible" << std::endl;
    }

    std::string msg;
    std::cout << "Vous êtes connecté, vous pouvez maintenant envoyer un message " << std::endl << " >> ";
    std::cin.ignore();
    std::getline(std::cin, msg, '\n');
    std::cout << msg;
    write(sock, msg.c_str(), 256);

    return 0;
}