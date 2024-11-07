#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
int main()
{
    char buf[256];
    char msg[] = "What a beautiful day!\n";
    struct sockaddr_in self_addr;
    self_addr.sin_family = AF_INET;
    self_addr.sin_port = 0; 				// Автоматический выбор порта
    self_addr.sin_addr.s_addr = INADDR_ANY; // Принять соединения от любого адреса
    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(10); 			// Порт сервера	
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        cerr << "Error creating socket" << endl;
        return 1;
    }
    int e = bind(s, (struct sockaddr*)&self_addr, sizeof(self_addr));
    if (e == -1)
    {
        cerr << "Error binding socket" << endl;
        close(s);
        return 1;
    }
    e = connect(s, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if (e == -1)
    {
        cerr << "Error connecting socket" << endl;
        close(s);
        return 1;
    }
    e = send(s, msg, strlen(msg), 0);
    if (e == -1)
    {
        cerr << "Error sending socket" << endl;
        close(s);
        return 1;
    }
    cout << "We send: " << msg;
    int rc = recv(s, buf, sizeof(buf), 0);
    if (rc < 0)
    {
        cerr << "Error receiving data" << endl;
        close(s);
        return 1;
    }
    buf[rc] = '\0';
    cout << "We receive: " << buf;
    close(s);
    return 0;
}
