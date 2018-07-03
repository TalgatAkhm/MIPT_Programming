#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define DEFAULT_PORT 8081
#define BACKLOG 10
#define ENDLESS 1
#define MAX_MESSAGE_SIZE 255

int clients_online;
int socket_;
int port;
struct sockaddr_in address;
int clients[BACKLOG];
void send_message(char *text, int from);

void sigint_handler(int sig) {
  signal(sig, SIG_IGN);
  printf("\n-%s \n", "SERVER IS TURNING OFF");
  for (size_t i = 0; i < clients_online; ++i) {
    shutdown(clients[i], SHUT_RDWR);
    close(clients[i]);
  }
  printf("-%s \n", "EXIT");
  exit(0);
}

void init_server() {
  socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
  address.sin_port = htons(port);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
}

void chating(void *args) {
  int *client_number = (int *)args;
  char buf[MAX_MESSAGE_SIZE];

  while(strcmp(buf, "quit\n")!=0 && strcmp(buf, "quit\r\n")!=0 &&
      strcmp(buf, "quit")!=0){
    int eos = (int) recv(*client_number, buf, MAX_MESSAGE_SIZE, 0);
    buf[eos] = '\0';
    if (strlen(buf) != 0) {
      send_message(buf, *client_number);
    }
  }
  shutdown(*client_number, SHUT_RDWR);
  close(*client_number);
}

void send_message(char *text, int from) {
  char chat_message[MAX_MESSAGE_SIZE + 12];
  sprintf(chat_message, "%d-> %s", from, text);
  for (int i = 0; i < clients_online; ++i) {
    if (clients[i] != from) {
      send(clients[i], chat_message, strlen(chat_message) + 1, 0);
      printf("%s \n", chat_message);
    }
  }
}

int main(int argc, char *argv[]) {
  signal(SIGINT, sigint_handler);

  if (argc == 2) {
    port = atoi(argv[1]);
  } else {
    port = DEFAULT_PORT;
  }

  init_server();

  if (bind(socket_, &address, sizeof(address)) != 0) {
    perror("BINDING ERROR");
    exit(1);
  }
  listen(socket_, BACKLOG);

  pthread_t id[BACKLOG];
  for (clients_online = 0; ENDLESS; ++clients_online) {
    clients[clients_online] = accept(socket_, NULL, NULL);
    pthread_create(&id[clients_online], NULL, &chating, (void *) &clients[clients_online]);
  }

  return 0;
}

