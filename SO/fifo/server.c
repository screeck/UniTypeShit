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



void handle_client(int client_fifo) {
    char buffer[4096];
    int fd;
    // Wykonaj polecenie "ls" i zapisz wynik do bufora
    FILE *fp = popen("ls", "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        write(client_fifo, buffer, strlen(buffer) + 1);
    }
    fclose(fp);
    close(client_fifo);
}





int main() {
    int server_fifo;
    int client_fifo;
    char client_fifo_name[256];
    // Tworzenie globalnej FIFO serwera
    if (mkfifo(FIFO_SERVER, 0777) == -1 && errno != EEXIST) {
        perror("mkfifo server");
        exit(1);
    }
    // Otwarcie FIFO serwera w trybie odczytu
    server_fifo = open(FIFO_SERVER, O_RDONLY);
    if (server_fifo == -1) {
        perror("open server fifo");
        exit(1);
    }
    while (1) {
        // Czekaj na połączenie od klienta (otrzymanie nazwy FIFO klienta)
        if (read(server_fifo, client_fifo_name, sizeof(client_fifo_name)) <= 0) {continue;}

        printf("Otrzymano FIFO klienta: %s\n", client_fifo_name);
        // Tworzymy FIFO klienta
        client_fifo = open(client_fifo_name, O_WRONLY);
        if (client_fifo == -1) {
            perror("open client fifo");
            continue;
        }
        // Obsłuż żądanie klienta
        handle_client(client_fifo);
    }
    close(server_fifo);
    unlink(FIFO_SERVER);
    return 0;
}
