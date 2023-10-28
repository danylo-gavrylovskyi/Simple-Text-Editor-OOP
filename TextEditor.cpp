#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TextEditor.h"

    char* TextEditor::receiveEditedLine(char* token, int index, char* input) {
        char* newLine = (char*)malloc(index + strlen(input) + 1);
        strcpy(newLine, token);

        while (strlen(newLine) < index) {
            strcat(newLine, " ");
        }

        strcat(newLine, input);

        return newLine;
    }

    char* TextEditor::extendResult(char* result, int index, char* token, char* input) {
        result = (char*)realloc(result, strlen(result) + (index - strlen(token)));

        char* newLine = (char*)malloc(index + strlen(input) + 1);
        strcpy(newLine, token);

        while (strlen(newLine) < index) {
            strcat(newLine, " ");
        }

        strcat(newLine, input);
        strcat(result, newLine);

        free(newLine);

        return result;
    }

    void TextEditor::saveToHistory() {
        if (history[2] != NULL) {
            free(history[0]);
            for (int i = 0; i < 2; i++) {
                history[i] = history[i + 1];
            }
            history[2] = NULL;
        }


        history[historyIndex] = _strdup(buffer);

        if (historyIndex < 2) historyIndex++;
    }

    void TextEditor::manualSaveState() {
        history[historyIndex] = _strdup(buffer);
    }

    TextEditor::TextEditor() {
        buffer = (char*)malloc(sizeof(char));
        *buffer = '\0';

        clipboard = NULL;
        historyIndex = 0;
        for (int i = 0; i < 3; i++) {
            history[i] = NULL;
        }

        history[historyIndex] = (char*)malloc(sizeof(char));
        *history[historyIndex] = '\0';
    }

    TextEditor::~TextEditor() {
        free(buffer);
        free(clipboard);
        for (int i = 0; i < 3; i++) {
            free(history[i]);
        }
    }

    void TextEditor::appendText(const char* text) {
        saveToHistory();
        buffer = (char*)realloc(buffer, strlen(buffer) + strlen(text) + 1);
        if (buffer != NULL) {
            strcat(buffer, text);
        }
        else {
            printf("Memory allocation failed.\n");
        }
        //manualSaveState();
    }

    void TextEditor::searchText(char* searchText) {
        char* bufferCopy = (char*)malloc(strlen(buffer) + 1);
        strcpy(bufferCopy, buffer);
        char* token = strtok(bufferCopy, "\n");
        int lineNumber = 0;

        while (token != NULL) {
            char* position = strstr(token, searchText);
            while (position != NULL) {
                int index = position - token;
                printf("Your text is present in this position: %d %d\n", lineNumber, index);
                position = strstr(position + 1, searchText);
            }

            token = strtok(NULL, "\n");
            lineNumber++;
        }

        free(bufferCopy);
    }

    void TextEditor::insertByLineAndIndex(int line, int index, char* input) {
        saveToHistory();
        char* result = (char*)malloc(strlen(buffer) + strlen(input) + 1);
        result[0] = '\0';

        char* token = strtok(buffer, "\n");
        int currentLine = 0;

        while (token != NULL) {
            if (currentLine == line) {
                if (strlen(token) < index) {
                    result = extendResult(result, index, token, input);
                }
                else {
                    strncat(result, token, index);
                    strcat(result, input);
                    strcat(result, token + index);
                }
            }
            else {
                strcat(result, token);
            }

            strcat(result, "\n");
            token = strtok(NULL, "\n");
            currentLine++;
        }

        /*free(buffer);*/
        buffer = result;
    }

    void TextEditor::deleteText(int line, int index, int numOfSymbols) {
        saveToHistory();
        char* result = (char*)malloc(strlen(buffer) - numOfSymbols + 1);
        result[0] = '\0';

        char* token = strtok(buffer, "\n");
        int currentLine = 0;

        while (token != NULL) {
            if (currentLine == line) {
                if (index < 0 || index >= strlen(token) || index + numOfSymbols > strlen(token)) {
                    printf("%s", "Given data is incorrect");
                    break;
                }
                strncat(result, token, index);
                strcat(result, token + index + numOfSymbols);
            }
            else {
                strcat(result, token);
            }

            strcat(result, "\n");
            token = strtok(NULL, "\n");
            currentLine++;
        }

        free(buffer);
        buffer = result;
        manualSaveState();
    }

    void TextEditor::insertWithReplacement(int line, int index, char* input) {
        saveToHistory();
        char* result = (char*)malloc(strlen(buffer) + 1);
        result[0] = '\0';

        char* token = strtok(buffer, "\n");
        int currentLine = 0;

        while (token != NULL) {
            if (currentLine == line) {
                if (index + strlen(input) > strlen(token)) {
                    result = (char*)realloc(result, strlen(result) + (index + strlen(input) - strlen(token) + 1));
                    strncat(result, token, index);
                    strcat(result, input);
                }
                else {
                    strncat(result, token, index);
                    strcat(result, input);
                    strcat(result, token + index + strlen(input));
                }
            }
            else {
                strcat(result, token);
            }

            strcat(result, "\n");
            token = strtok(NULL, "\n");
            currentLine++;
        }

        //free(buffer);
        buffer = result;
        manualSaveState();
    }

    void TextEditor::cut(int line, int index, int numOfSymbols) {
        saveToHistory();
        char* result = (char*)malloc(strlen(buffer) + 1);
        result[0] = '\0';

        char* token = strtok(buffer, "\n");
        int currentLine = 0;

        while (token != NULL) {
            if (line == currentLine) {
                if (index >= strlen(token) || index < 0 || index + numOfSymbols > strlen(token)) {
                    printf("%s", "Given data is incorrect");
                    break;
                }

                if (index + numOfSymbols >= strlen(token)) {
                    strcat(result, "");
                }
                else {
                    strncat(result, token, index);
                    strcat(result, token + index + numOfSymbols);
                }

                free(clipboard);
                clipboard = (char*)malloc(numOfSymbols + 1);
                strncpy(clipboard, token + index, numOfSymbols);
                clipboard[numOfSymbols] = '\0';
            }
            else {
                strcat(result, token);
            }

            strcat(result, "\n");
            token = strtok(NULL, "\n");
            currentLine++;
        }

        free(buffer);
        buffer = result;
        //manualSaveState();
    }

    void TextEditor::copy(int line, int index, int numOfSymbols) {
        char* bufferCpy = (char*)malloc(strlen(buffer));
        strcpy(bufferCpy, buffer);

        char* token = strtok(bufferCpy, "\n");
        int currentLine = 0;

        while (token != NULL) {
            if (line == currentLine) {
                if (index >= strlen(token) || index < 0 || index + numOfSymbols > strlen(token)) {
                    printf("%s", "Given data is incorrect");
                    break;
                }

                free(clipboard);
                clipboard = (char*)malloc(numOfSymbols + 1);
                strncpy(clipboard, token + index, numOfSymbols);
                clipboard[numOfSymbols] = '\0';
            }

            token = strtok(NULL, "\n");
            currentLine++;
        }
    }

    void TextEditor::paste(int line, int index) {
        saveToHistory();
        insertByLineAndIndex(line, index, clipboard);
        manualSaveState();
    }

    void TextEditor::undo() {
        if (historyIndex > 0) {
            historyIndex--;
            char* prevState = _strdup(history[historyIndex]);
            buffer = prevState;
        }
        else {
            printf("Undo is not available.\n");
        }
    }

    void TextEditor::redo() {
        if (historyIndex < 2 && history[historyIndex + 1] != NULL) {
            historyIndex++;
            char* nextState = _strdup(history[historyIndex]);
            free(buffer);
            buffer = nextState;
        }
        else {
            printf("Redo is not available.\n");
        }
    }

    char* TextEditor::getBuffer() {
        return buffer;
    }
