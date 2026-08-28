char *memory = (char*) 0xB8000;
int cursor_row = 0;
int cursor_col = 0;

void print(char *message) {
    for (int i = 0; message[i] != '\0'; ++i) {
        int index = (cursor_row * 80 + cursor_col) * 2;
        memory[index] = message[i];
        memory[index + 1] = 0x07;
        cursor_col++;
    }
}

void kernel_main(void) {
    print("Hello m OS!");
    print(" This is a test.");

    while (1) { }
}