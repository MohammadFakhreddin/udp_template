#include "BedrockLog.hpp"
#include "ScopeProfiler.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define PACKET_COUNT 10
#define BUFFER_SIZE 1024


int main()
{
    MFA_LOG_INFO("Client is ready!");

    int sock;
    struct sockaddr_in server_addr;
    char message[256] = "Packet Data";
    char buffer[BUFFER_SIZE];

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        MFA_LOG_ERROR("Socket creation error");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send 10 packets to the server
    for (int i = 0; i < PACKET_COUNT; ++i) 
    {
        {
            SCOPE_Profiler("Time to send packet");
                        
            // Send packet to server
            sendto(sock, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            MFA_LOG_INFO("Sent packet %d", (i + 1));
        }
        usleep(500000);  // Optional: Sleep for 0.5 seconds between packets
    }

    MFA_LOG_INFO("All packets sent. Closing socket.\n");

    // Close the socket
    close(sock);

    return 0;
}

