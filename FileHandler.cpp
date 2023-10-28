#include "FileHandler.h"

void FileHandler::saveTextToFile(const char* fileName, const char* text) {
    FILE* file = fopen(fileName, "a");
    if (file != NULL) {
        fputs(text, file);
        fclose(file);
        printf("\nText has been saved successfully");
    }
    else {
        printf("Error while opening file");
    }
}

void FileHandler::loadTextFromFile(const char* fileName, char** buffer) {
    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        char fileText[100];
        while (fgets(fileText, sizeof(fileText), file) != NULL) {
            *buffer = (char*)realloc(*buffer, strlen(*buffer) + strlen(fileText) + 1);
            strcat(*buffer, fileText);
        }
        fclose(file);
        printf("\nText has been loaded successfully");
    }
    else {
        printf("Error while opening file");
    }
}
