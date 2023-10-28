#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class TextEditor {
private:
    char* clipboard;
    char* history[3];
    int historyIndex;

    char* receiveEditedLine(char* token, int index, char* input);

    char* extendResult(char* result, int index, char* token, char* input);

    void saveToHistory();

    void manualSaveState();
public:
    char* buffer;

    TextEditor();
    ~TextEditor();

    void appendText(const char* text);

    void searchText(char* searchText);

    void insertByLineAndIndex(int line, int index, char* input);

    void deleteText(int line, int index, int numOfSymbols);

    void insertWithReplacement(int line, int index, char* input);

    void cut(int line, int index, int numOfSymbols);

    void copy(int line, int index, int numOfSymbols);

    void paste(int line, int index);

    void undo();

    void redo();

    char* getBuffer();
};
