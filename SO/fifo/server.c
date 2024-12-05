#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define FIFO_SERVER "/tmp/fifo_server"

void handle_client(const char *client_fifo_name) {
    char buffer[4096];
    FILE *fp = popen("ls", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    int client_fifo = open(client_fifo_name, O_WRONLY);
    if (client_fifo == -1) {
        perror("open client fifo");
        pclose(fp);
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        write(client_fifo, buffer, strlen(buffer) + 1);
    }

    close(client_fifo);
    pclose(fp);
}

int main() {
    int server_fifo;
    char client_fifo_name[256];

    if (mkfifo(FIFO_SERVER, 0777) == -1 && errno != EEXIST) {
        perror("mkfifo server");
        exit(1);
    }

    server_fifo = open(FIFO_SERVER, O_RDONLY | O_NONBLOCK);
    if (server_fifo == -1) {
        perror("open server fifo");
        exit(1);
    }

    printf("Server started, waiting for clients...\n");

    while (1) {
        ssize_t bytes_read = read(server_fifo, client_fifo_name, sizeof(client_fifo_name));
        if (bytes_read > 0) {
            printf("Received client FIFO: %s\n", client_fifo_name);

            pid_t pid = fork();
            if (pid == 0) {
                // Child process handles the client
                handle_client(client_fifo_name);
                exit(0);
            }
        }
        // Allow the parent to handle the next request without waiting
        usleep(100000); // Short sleep to avoid busy-waiting
    }

    close(server_fifo);
    unlink(FIFO_SERVER);
    return 0;
}
