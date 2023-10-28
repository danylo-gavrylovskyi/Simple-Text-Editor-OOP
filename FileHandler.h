#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class IFileHandler {
public:
    virtual ~IFileHandler() {}

    virtual void saveTextToFile(const char* fileName, const char* text) = 0;

    virtual void loadTextFromFile(const char* fileName, char** buffer) = 0;
};

class FileHandler: public IFileHandler {
public:
    void saveTextToFile(const char* fileName, const char* text) override;

    void loadTextFromFile(const char* fileName, char** buffer) override;
};