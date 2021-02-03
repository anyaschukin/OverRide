void log_wrapper(FILE *log_file, char *message, char *filename) {

    // Copy message and filename to log buffer
	char log[264]; /* rbp-0x110 */
    strcpy(log, message);
    snprintf(&log[strlen(log)], 254 - strlen(log), filename);
    log[strcspn(log, "\n")] = 0;

	// Print log to log file
    fprintf(log_file, "LOG: %s\n", log);
    return;
}

int main(int argc, char **argv)
{
	// Accept 1 argument (filename)
    if (argc != 2)
        printf("Usage: %s filename\n", argv[0]);

	// Open log_file
    FILE *log_file = fopen("./backups/.log", "w"); /* rbp-0x88 */
    if (log_file == 0) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }
    log_wrapper(log_file, "Starting back up: ", argv[1]);

	// Open arg_file
    FILE *arg_file = fopen(argv[1], "r"); /* rbp-0x80 */
    if (arg_file == 0) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

	// Read filename
    char filename[100]; /* rbp-0x70 */
    strcpy(filename, "./backups/");
    strncat(filename, argv[1], 99 - (strlen(filename) - 1);

	// Open file
    int fd; /* rbp-0x78 */
    fd = open(filename, 0xc1);
    if (fd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

	// Write to file
    int c; /* rbp-0x71 */
    while (c = fgetc(arg_file) != 255) {
        write(fd, c, 1);
    }
    log_wrapper(log_file, "Finished back up ", argv[1]);

	// Close
    fclose(arg_file);
    close(fd);
    return 0;
}
