#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Console.h"
#include "FileHandler.h"
#include "Encryption.h"
#include "TextEditor.h"

int Console::getCommandsChoice() {
    int choice;
    printf("\nChoose the command:\n\t");
    printf("0.Exit\n\t");
    printf("1.Append text symbols to the end\n\t");
    printf("2.Start a new line\n\t");
    printf("3.Load text from file\n\t");
    printf("4.Save current text to file\n\t");
    printf("5.Print the current text to console\n\t");
    printf("6.Insert text by line and symbol index\n\t");
    printf("7.Search\n\t");
    printf("8.Delete\n\t");
    printf("9.Undo\n\t");
    printf("10.Redo\n\t");
    printf("11.Cut\n\t");
    printf("12.Paste\n\t");
    printf("13.Copy\n\t");
    printf("14.Insert with replacement\n\t");
    printf("15.Caesar encryption normal mode\n\t");
    printf("16.Caesar encryption secret mode\n >> ");
    scanf("%d", &choice);
    getchar();
    return choice;
}

void Console::clearConsole() {
    system("cls");
}

void Console::printText(char* text) {
    clearConsole();
    printf("%s\n", text);
}

void Console::run(TextEditor editor, FileHandler fileHandler, Encryption encryption) {
        while (true) {
            int choice = getCommandsChoice();

            if (choice == 0) {
                break;
            }

            switch (choice) {
            case 1: {
                char input[256];
                printf("Enter text to append: ");
                scanf("%255[^\n]", input);
                editor.appendText(input);
                break;
            }
            case 2: {
                const char newline[] = "\n";
                editor.appendText(newline);
                printf("%s", "New line is started");
                break;
            }
            case 3: {
                char fileName[256];
                printf("Enter the file name for loading: ");
                scanf("%255s", fileName);
                fileHandler.loadTextFromFile(fileName, &editor.buffer);
                break;
            }
            case 4: {
                char fileName[256];
                printf("Enter the file name for saving: ");
                scanf("%255s", fileName);
                fileHandler.saveTextToFile(fileName, editor.buffer);
                break;
            }
            case 5:
                printText(editor.getBuffer());
                break;
            case 6: {
                int line;
                int index;
                char input[256];
                printf("Enter line: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter text to append: ");
                getchar();
                scanf("%255[^\n]", input);
                editor.insertByLineAndIndex(line, index, input);
                break;
            }
            case 7: {
                char input[256];
                printf("Enter text to search: ");
                scanf("%255[^\n]", input);
                editor.searchText(input);
                break;
            }
            case 8: {
                int line, index, numOfSymbols;
                printf("%s", "Choose line, index and number of symbols: ");
                scanf("%d %d %d", &line, &index, &numOfSymbols);
                editor.deleteText(line, index, numOfSymbols);
                break;
            }
            case 9: {
                editor.undo();
                break;
            }
            case 10: {
                editor.redo();
                break;
            }
            case 11: {
                int line, index, numOfSymbols;
                printf("%s", "Choose line, index and number of symbols: ");
                scanf("%d %d %d", &line, &index, &numOfSymbols);
                editor.cut(line, index, numOfSymbols);
                break;
            }
            case 12: {
                int line, index;
                printf("%s", "Choose line and index: ");
                scanf("%d %d", &line, &index);
                editor.paste(line, index);
                break;
            }
            case 13: {
                int line, index, numOfSymbols;
                printf("%s", "Choose line, index and number of symbols: ");
                scanf("%d %d %d", &line, &index, &numOfSymbols);
                editor.copy(line, index, numOfSymbols);
                break;
            }
            case 14: {
                char input[256];
                int line, index;
                printf("%s", " Choose line and index: ");
                scanf("%d %d", &line, &index);
                printf("Enter text to append: ");
                getchar();
                scanf("%255[^\n]", input);
                editor.insertWithReplacement(line, index, input);
                break;
            }
            case 15: {
                int mode, key;
                char inputPath[256], outputPath[256];
                cout << "Choose type of operation (1 - encrypt, 2 - decrypt): ";
                cin >> mode;
                cout << endl << "Enter input file path: ";
                cin >> inputPath;
                cout << endl << "Enter output file path: ";
                cin >> outputPath;
                cout << endl << "Enter key: ";
                cin >> key;
                cout << endl;

                char* text = (char*)malloc(sizeof(char));
                *text = '\0';
                fileHandler.loadTextFromFile(inputPath, &text);
                if (mode == 1) {
                    encryption.encrypt(text, key);
                }
                else if (mode == 2) {
                    encryption.decrypt(text, key);
                }

                fileHandler.saveTextToFile(outputPath, text);
                break;
            }
            case 16: {
                srand(time(NULL));
                char inputPath[256], outputPath[256];
                cout << "Enter input file path: ";
                cin >> inputPath;
                cout << endl << "Enter output file path: ";
                cin >> outputPath;
                cout << endl << "Enter key: ";

                int key = rand() % 25 + 1;
                char* text = (char*)malloc(sizeof(char));
                *text = '\0';
                fileHandler.loadTextFromFile(inputPath, &text);
                encryption.encrypt(text, key);
                fileHandler.saveTextToFile(outputPath, text);
                break;
            }
            default:
                clearConsole();
                printf("The command is not implemented\n");
                break;
            }
        }
    }