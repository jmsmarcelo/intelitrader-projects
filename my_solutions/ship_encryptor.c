#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_prompt();
void exec_input(int opt);
void encrypt_msg(const char *msg);
void decrypt_msg(const char *encrypted_msg);
void char_to_binary(unsigned char c, char *out);
char binary_to_char(const char *binary);

int main() {
    start_prompt();
    return 0;
}

void start_prompt() {
    printf("\nWelcome to ShipEncryptor\n\n");
    printf("Options:\n");
    printf(" 1. Encrypt message\n");
    printf(" 2. Decrypt message\n");
    printf(" 3. Quit\n");

    char buffer[8];
    int value;

    while(1) {
        printf("\nChoose an option (1, 2 or 3): ");

        if(!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error reading input.\n");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        char *endptr;
        value = strtol(buffer, &endptr, 10);
        if(endptr == buffer || *endptr != '\0') {
            printf("Invalid input.\n");
            continue;
        }
        switch(value) {
            case 1:
            case 2:
                exec_input(value);
                continue;
            case 3:
                printf("Goodbye!\n");
                return;
            default:
                printf("Value must be between 1 and 3.\n");
                continue;
        }
    }
}
void exec_input(int opt) {
    size_t capacity = 9;
    char *input = malloc(capacity);
    size_t pos = 0;

    if(!input) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    char buffer[65];
    size_t buffer_length = 0;
    input[0] = '\0';
    char *stop = NULL;

    printf("\nEnter the message to %scrypt: ", (opt ==2) ? "de" : "en");

    while(fgets(buffer, sizeof(buffer), stdin)) {
        stop = strchr(buffer, '\n');
        buffer[strcspn(buffer, "\n")] = '\0';
        buffer_length = strlen(buffer);
        capacity += buffer_length;
        input = realloc(input, capacity);

        if(!input) {
            fprintf(stderr, "Memory reallocation failed\n");
            return;
        }
        memcpy(input + pos, buffer, buffer_length);
        pos += buffer_length;

        if(stop) break;
    }
    input[pos] = '\0';

    if(opt == 1) {
        encrypt_msg(input);
    } else {
        decrypt_msg(input);
    }
    free(input);
}
void encrypt_msg(const char *msg) {
    size_t msg_length = strlen(msg) + 1;

    size_t encrypted_msg_length = (msg_length * 9);
    size_t encrypted_msg_index = 0;
    char *encrypted_msg = malloc(encrypted_msg_length);

    char current_char[9];

    for(int i = 0; i < msg_length; i++) {
        char_to_binary((unsigned char)msg[i], current_char);

        for(int j = 0; j < 8; j++) {
            if(current_char[j] == '0' || current_char[j] == '1') {
                if(j == 2 || j == 3) {
                    encrypted_msg[encrypted_msg_index + 4] = (current_char[j] == '0') ? '1' : '0';
                } else if(j > 3) {
                    encrypted_msg[encrypted_msg_index - 4] = current_char[j];
                } else {
                    encrypted_msg[encrypted_msg_index + 4] = current_char[j];
                }
                encrypted_msg_index++;
            }
        }
        if(i < msg_length - 1) {
            encrypted_msg[encrypted_msg_index++] = ' ';
        }
    }
    encrypted_msg[encrypted_msg_index] = '\0';

    printf("\nEncrypted message: %s\n", encrypted_msg);

    free(encrypted_msg);
}
void decrypt_msg(const char *encrypted_msg) {
    size_t capacity = 16;
    size_t decrypted_msg_index = 0;
    char *decrypted_msg = malloc(capacity);

    char current_char[9] = "";
    int current_char_index = 0;

    if(!decrypted_msg) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return;
    }
    for(int i = 0; i < strlen(encrypted_msg); i++) {
        if(encrypted_msg[i] == '0' || encrypted_msg[i] == '1') {
            if(current_char_index == 6 || current_char_index == 7) {
                current_char[current_char_index - 4] = (encrypted_msg[i] == '1') ? '0' : '1';
            } else if(current_char_index > 3) {
                current_char[current_char_index - 4] = encrypted_msg[i];
            } else {
                current_char[current_char_index + 4] = encrypted_msg[i];
            }
            if(++current_char_index == 8) {
                current_char[8] = '\0';
                
                if(decrypted_msg_index >= capacity - 1) {
                    capacity += 16;
                    decrypted_msg = realloc(decrypted_msg, capacity);
                    if(!decrypted_msg) {
                        fprintf(stderr, "Error: memory reallocation failed\n");
                        return;
                    }
                }
                decrypted_msg[decrypted_msg_index++] = binary_to_char(current_char);
                current_char_index = 0;
            }
        }
    }
    if(current_char_index != 0) {
        fprintf(stderr, "Error: the given binary is not a multiple of 8 in encrypted message.\n");
    }
    if(current_char_index == 0 && decrypted_msg_index > 0){
        decrypted_msg[decrypted_msg_index] = '\0';
        printf("\nDecrypted message: %s\n", decrypted_msg);
    }
    free(decrypted_msg);
}
void char_to_binary(unsigned char c, char *out) {
    for(int i = 7; i >= 0; i--) {
        out[7 - i] = ((c >> i) & 1) ? '1' : '0';
    }
    out[8] = '\0';
}
char binary_to_char(const char *binary) {
    char result = 0;
    for(int i = 0; i < 8; i++) {
        if(binary[i] == '1') {
            result += (1 << (7 - i));
        }
    }
    return result;
}