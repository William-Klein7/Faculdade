// Compilar no MinGW: gcc chat_server_win.c -o chat_server -lws2_32
// Uso: .\chat_server 9000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

typedef struct
{
  SOCKET sock;
  char nick[32];
} client_t;

client_t *clients[MAX_CLIENTS];
CRITICAL_SECTION clients_mutex;

void strip_newline(char *s)
{
  while (*s && (*s == '\n' || *s == '\r'))
    *s++ = '\0';
}

void send_to_all(const char *msg, SOCKET except_sock)
{
  EnterCriticalSection(&clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++)
  {
    if (clients[i])
    {
      if (clients[i]->sock != except_sock)
      {
        send(clients[i]->sock, msg, strlen(msg), 0);
      }
    }
  }
  LeaveCriticalSection(&clients_mutex);
}

void remove_client(SOCKET sock)
{
  EnterCriticalSection(&clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++)
  {
    if (clients[i])
    {
      if (clients[i]->sock == sock)
      {
        free(clients[i]);
        clients[i] = NULL;
        break;
      }
    }
  }
  LeaveCriticalSection(&clients_mutex);
}

DWORD WINAPI client_handler(LPVOID arg)
{
  SOCKET sock = *((SOCKET *)arg);
  free(arg);

  char buffer[BUFFER_SIZE];
  char nick[32];

  int n = recv(sock, nick, sizeof(nick) - 1, 0);
  if (n <= 0)
  {
    closesocket(sock);
    return 0;
  }
  nick[n] = '\0';
  strip_newline(nick);

  client_t *cli = (client_t *)malloc(sizeof(client_t));
  cli->sock = sock;
  strncpy(cli->nick, nick, sizeof(cli->nick) - 1);

  EnterCriticalSection(&clients_mutex);
  int i;
  for (i = 0; i < MAX_CLIENTS; i++)
  {
    if (!clients[i])
    {
      clients[i] = cli;
      break;
    }
  }
  LeaveCriticalSection(&clients_mutex);

  if (i == MAX_CLIENTS)
  {
    const char *msg = "Servidor cheio\n";
    send(sock, msg, strlen(msg), 0);
    closesocket(sock);
    free(cli);
    return 0;
  }

  char join_msg[BUFFER_SIZE];
  sprintf(join_msg, "*** %s entrou no chat\n", cli->nick);
  send_to_all(join_msg, -1);

  while (1)
  {
    memset(buffer, 0, sizeof(buffer));
    int r = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (r <= 0)
      break;
    buffer[r] = '\0';
    strip_newline(buffer);

    if (strcmp(buffer, "/quit") == 0)
      break;

    char out[BUFFER_SIZE + 64];
    sprintf(out, "%s: %s\n", cli->nick, buffer);
    send_to_all(out, sock);
  }

  char leave_msg[BUFFER_SIZE];
  sprintf(leave_msg, "*** %s saiu do chat\n", cli->nick);
  remove_client(sock);
  send_to_all(leave_msg, -1);
  closesocket(sock);
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Uso: %s <porta>\n", argv[0]);
    return 1;
  }

  int port = atoi(argv[1]);

  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    printf("Falha no WSAStartup\n");
    return 1;
  }

  SOCKET listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == INVALID_SOCKET)
  {
    printf("Erro no socket()\n");
    return 1;
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
  {
    printf("Erro no bind()\n");
    return 1;
  }

  if (listen(listenfd, 10) == SOCKET_ERROR)
  {
    printf("Erro no listen()\n");
    return 1;
  }

  InitializeCriticalSection(&clients_mutex);

  printf("Servidor rodando na porta %d\n", port);

  while (1)
  {
    struct sockaddr_in cli_addr;
    int clilen = sizeof(cli_addr);
    SOCKET connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &clilen);
    if (connfd == INVALID_SOCKET)
    {
      printf("Erro no accept()\n");
      continue;
    }

    SOCKET *sock_ptr = malloc(sizeof(SOCKET));
    *sock_ptr = connfd;
    CreateThread(NULL, 0, client_handler, sock_ptr, 0, NULL);
  }

  DeleteCriticalSection(&clients_mutex);
  closesocket(listenfd);
  WSACleanup();
  return 0;
}
