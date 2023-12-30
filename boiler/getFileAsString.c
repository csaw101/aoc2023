char* getFileAsString(char *fileName) {
    FILE *stream;
    size_t fileLength;
    char *buffer;

    stream = fopen(fileName, "r");

    fseek(stream, 0, SEEK_END);
    fileLength = ftell(stream);
    rewind(stream);

    buffer = malloc(fileLength * sizeof(char) + 1);
    buffer[fileLength] = '\0';
    fread(buffer, 1, fileLength, stream);
    fclose(stream);

    return buffer;
}
