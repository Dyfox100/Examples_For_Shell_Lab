#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 10


// unix pipe communication.

int main() {
    char* first_msg = "message_1";
    char* second_msg = "message_2";
    char* third_msg = "message_3";

    char input_buff[BUFFSIZE * 3];
    // pipe_file_descriptors[0] == read end
    // pipe_file_descriptors[1] == write end
    int pipe_file_descriptors[2];
    // pipe function takes in an array of 2 integers and puts 
    // file descriptor into that array.
    if (pipe(pipe_file_descriptors) < 0) {
        exit(1);
    } 
    // not exactly the same as writing to file using fprintf
    write(pipe_file_descriptors[1], first_msg, BUFFSIZE);
    write(pipe_file_descriptors[1], second_msg, BUFFSIZE);

    int num_bytes_read = read(pipe_file_descriptors[0], input_buff, BUFFSIZE);
    printf("%s\n", input_buff);

    read(pipe_file_descriptors[0], &input_buff[num_bytes_read], BUFFSIZE + 2);

    printf("%s\n", &input_buff[num_bytes_read]);
    
    return 0;
}