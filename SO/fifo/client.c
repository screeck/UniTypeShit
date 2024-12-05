#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#define FIFO_SERVER "/tmp/fifo_server"

void handle_request() {
    int server_fifo, client_fifo;
    char client_fifo_name[256];
    char buffer[4096];
    pid_t pid = getpid();

    snprintf(client_fifo_name, sizeof(client_fifo_name), "/tmp/fifo_%d", pid);
    if (mkfifo(client_fifo_name, 0777) == -1 && errno != EEXIST) {
        perror("mkfifo client");
        exit(1);
    }

    server_fifo = open(FIFO_SERVER, O_WRONLY | O_NONBLOCK);
    if (server_fifo == -1) {
        perror("open server fifo");
        unlink(client_fifo_name);
        exit(1);
    }

    if (write(server_fifo, client_fifo_name, strlen(client_fifo_name) + 1) == -1) {
        perror("write to server fifo");
        close(server_fifo);
        unlink(client_fifo_name);
        exit(1);
    }
    close(server_fifo);

    usleep(100000); // Wait briefly to ensure server processes the request

    client_fifo = open(client_fifo_name, O_RDONLY);
    if (client_fifo == -1) {
        perror("open client fifo");
        unlink(client_fifo_name);
        exit(1);
    }

    printf("Process %d received data from server:\n", pid);
    while (read(client_fifo, buffer, sizeof(buffer)) > 0) {
        printf("[Process %d]: %s", pid, buffer);
    }

    close(client_fifo);
    unlink(client_fifo_name);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        exit(1);
    }

    int num_processes = atoi(argv[1]);
    if (num_processes <= 0) {
        fprintf(stderr, "Number of processes must be a positive integer.\n");
        exit(1);
    }

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            handle_request();
            exit(0);
        }
    }

    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}
