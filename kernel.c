void kernel_main(void) {
    char *memory = (char*) 0xB8000;
    const char *message = "hello from OS";

    for (int i = 0; message[i] != '\0'; ++i) {
        memory[i * 2] = message[i];
        memory[i * 2 + 1] = 0x07;
    }

    while (1);
}