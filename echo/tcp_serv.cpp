#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
	int PORT = 10;
	int buf_size = 256;
    struct sockaddr_in address;
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    int addrlen = sizeof(address);
    char buf[buf_size];
   
    int s = socket(AF_INET, SOCK_STREAM, 0);
    
    
    
    bind(s, (struct sockaddr *)&address, sizeof(address));
	listen(s, 3);

    
    while (true)
    {
       	int new_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        recv(new_socket, buf, buf_size, 0);
        send(new_socket, buf, buf_size, 0);
        std::cout << buf;
        close(new_socket);
    }
    return 0;
}
