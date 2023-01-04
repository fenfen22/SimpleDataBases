#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

// there will be an infinite loop thant prints prompt, 
// gets a line of imput, and then process the line of input in main function.

typedef struct 
{
    char* buffer;
    size_t buffer_length; //size_t is an unsigned integral data type
    size_t input_length;

} InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;

}
void print_prompt(){
    printf("db > ");

}

void read_input(InputBuffer* input_buffer){
    //use getline() to read a line of input.
    /*
    first parameter: a ponter to the variable we use to point to the buffer containing the read line, 
    should be freed by user;

    second parameter: a pointer to the variable we use to save the size of allocated buffer;
    
    third parameter: the number of bytes read, which may less than the size of the buffer.
    
    we use getline function to store the read line in input_buffer->buffer and the size of 
    allocated buffer in input_buffer->buffer_length.

    we store the return value in input_buffer->input_length.
    */
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    //ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;

}

void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_FAILURE);
        }
        else{
            printf("Unrecognized command '%s' .\n", input_buffer->buffer);
        }
    }
    
    

}