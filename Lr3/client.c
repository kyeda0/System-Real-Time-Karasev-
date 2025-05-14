#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <errno.h>

int main(void) {
    char smsg[512];
    char rmsg[512];
    int coid;
    long serv_pid;

    printf("Rusanov Eugene i914b\n");
    printf("Client program. Enter server PID: ");
    scanf("%ld", &serv_pid);
    printf("You entered: %ld\n", serv_pid);

    // Подключение к каналу сервера
    if ((coid = ConnectAttach(0, serv_pid, 1, 0, 0)) == -1) {
        perror("ConnectAttach");
        exit(EXIT_FAILURE);
    }

    printf("Connection result: %d\n", coid);
    printf("Enter message to shift left (letters only): ");
    scanf("%s", smsg);
    printf("You entered: %s\n", smsg);

    if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) {
        perror("MsgSend");
        exit(EXIT_FAILURE);
    }

    printf("Server response (shifted string): %s\n", rmsg);

    ConnectDetach(coid);
    return EXIT_SUCCESS;
}
