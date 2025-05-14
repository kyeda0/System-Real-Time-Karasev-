#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <errno.h>

void shift_left_2(char* input, char* output) {
    int len = strlen(input);

    if (len <= 2) {
        strcpy(output, input);
        return;
    }

    strcpy(output, input + 2);
    strncat(output, input, 2);
    output[len] = '\0'; 
}

void server(void) {
    int rcvid;
    int chid;
    char message[512];
    char shifted[512];

    printf("Server start working\n");

    if ((chid = ChannelCreate(0)) == -1) {
        perror("ChannelCreate");
        exit(EXIT_FAILURE);
    }

    printf("Channel id: %d\n", chid);
    printf("Pid: %d\n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        if (rcvid == -1) {
            perror("MsgReceive");
            continue;
        }

        printf("Received message: \"%s\"\n", message);

        shift_left_2(message, shifted);
        printf("Shifted message: \"%s\"\n", shifted);

        if (MsgReply(rcvid, 0, shifted, strlen(shifted) + 1) == -1) {
            perror("MsgReply");
        }
    }
}

int main(void) {
    printf("Server program\n");
    server();
    return EXIT_SUCCESS;
}
