// Compilar no MinGW: gcc chat_client_win.c -o chat_client -lws2_32
// Uso: .\chat_client 127.0.0.1 9000 <nick>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#define BUFF_SIZE 1024

SOCKET sock;

DWORD WINAPI recv_handler(LPVOID arg)
{
  char buffer[BUFF_SIZE];
  int n;
  while ((n = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0)
  {
    buffer[n] = '\0';
    printf("%s", buffer);
    fflush(stdout);
  }
  printf("Conexao perdida.\n");
  exit(0);
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    printf("Uso: %s <host> <porta> <nick>\n", argv[0]);
    return 1;
  }

  char *host = argv[1];
  int port = atoi(argv[2]);
  char *nick = argv[3];

  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    printf("Falha no WSAStartup\n");
    return 1;
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET)
  {
    printf("Erro no socket()\n");
    return 1;
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = inet_addr(host);

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Erro no connect()\n");
    return 1;
  }

  // envia nick
  send(sock, nick, strlen(nick), 0);
  send(sock, "\n", 1, 0);

  CreateThread(NULL, 0, recv_handler, NULL, 0, NULL);

  char message[BUFF_SIZE];
  while (fgets(message, sizeof(message), stdin) != NULL)
  {
    if (strcmp(message, "/quit\n") == 0)
    {
      send(sock, "/quit\n", 6, 0);
      break;
    }
    send(sock, message, strlen(message), 0);
  }

  closesocket(sock);
  WSACleanup();
  return 0;
}
