#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "Functions.h"
#include <stdio.h>

using namespace std;

void open_file(string s, fstream &f, bool isAppendMode) {
    if (isAppendMode) f.open((char *) s.c_str(), ios::app);
    else f.open((char *) s.c_str());

    if (!f) {
        cout << "Success opening a file!" << endl;
    } else {
        cout << "Error opening a file" << endl;
        exit(1);
    }
}

string input_text() {
    cout << "Enter text , enter \"#\" on a line by itself to stop\n";
    string text;
    string line;
    // поки не натиснута "#" + enter
    do {
        getline(cin, line);
        text += line + '\n';
    } while (int(line[0]) != 35);

    // відкидаємо 3 зайвих символи (1 зайву # і \n)
    text = text.substr(0, text.size() - 3);
    return text;
}

void read_file(string filename) {
    cout << filename << ":" << endl;
    ifstream in_file(filename);

    if (!in_file) {
        cout << "Error opening a file!" << endl;
        exit(1);
    }

    string line;
    while (getline(in_file, line)) {          // takes and read line by line
        cout << line << endl;
    }
}

void create_file(string filename) {

    bool entered = false;
    string choice, text;

    do {
        if (choice == "Y" || choice == "y") {
            ofstream out_file((char *) filename.c_str(), ios::app);
            text = input_text();
            out_file << text;
            out_file.close();
        } else {
            if (!entered) {
                ofstream out_file((char *) filename.c_str());
                text = input_text();
                out_file << text;
                out_file.close();
                entered = true;
            }
        }
        cout << "Do you want to add more text (y/n)" << endl;
        cin >> choice;
    } while (choice == "Y" || choice == "y");
}

void create_newfile(string filename, string newFilename) {
    string change_str(string str);

    ofstream out_file((char *) newFilename.c_str());
    ifstream in_file((char *) filename.c_str());
    bool isOdd = true;
    string line;
    while (getline(in_file, line)) {
        if (isOdd) {
            line = change_str(line);
            out_file << line << endl;
        }
        isOdd = !isOdd;
    }
    out_file.close();
    in_file.close();
}

string change_str(string line) {
    void reverse_string(string &s);

    const char *delims = "., ";
    int i = 0;
    reverse_string(line);

    // Create a copy of the reversed string
    string rev_line = line;

    char *token = strtok((char *) rev_line.c_str(), delims);

    while (token != NULL) {
        i++;
        if (i == 2) {   // a word before the last is found
            break;
        };
        token = strtok(NULL, delims);
    }

    if (token != NULL) {
        int index = rev_line.length() - rev_line.find(token) -
                    strlen(token); //пошук індексу (першого входження) передостаннього слова в оригінал строці
        reverse_string(line);


        // Delete the word before the last
        string word = line.substr(index, strlen(token) + 1); //виділяє передостаннє слово
        line.erase(index, strlen(token) + 1);  // стрели слово з кінця
        line = word + line; // записали слово на початок
    } else {
        reverse_string(line);  //якщо в строці одне слово
    }

    return line;
}

void reverse_string(string &s) {
    int n = s.length();
    for (int i = 0; i < n / 2; i++) {
        // Swap the ith character from the start with the ith character from the end
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

string shift(string s, int k) {
    string s2;

    for (char c: s) {
        if (isupper(c)) {
            int val = c - 'A';
            val = (val + k) % 26;
            char c2 = 'A' + val;
            s2 += c2;
        } else if (islower(c)) {
            int val = c - 'a';
            val = (val + k) % 26;
            char c2 = 'a' + val;
            s2 += c2;
        } else {
            s2 += c;
        }
    }
    return s2;
}

void cipher_file(string filename) {
    ifstream in_file(filename);
    string buffer, line;
    int k;
    if (!in_file) {
        cout << "Error opening a file!" << endl;
        exit(1);
    }

    while (getline(in_file, line)) {          // takes and read line by line
        buffer += line + '\n';
    }

    in_file.close();
    ofstream out_file(filename);

    if (!out_file) {
        cout << "Error opening a file!" << endl;
        exit(1);
    }

    cout << "\nEnter a k parameter (number of chars to shift)" << endl;
    cin >> k;
    out_file << shift(buffer, k);
}

void change_last_line(string filename) {
    ifstream in_file(filename);

    string buffer, line;

    while (getline(in_file, line)) {          // takes and read line by line
        buffer += line + '\n';
    }

    buffer.erase(buffer.length() - 1, 1);
    int index = buffer.find_last_of('\n') == -1 ? 0 : buffer.find_last_of('\n');

    string last_line = buffer.substr(index);

    const char *delims = "., ";
    int i = 0;

    string last_line_copy = last_line;

    char *token = strtok((char *) last_line_copy.c_str(), delims);

    while (token != NULL) {
        i++;
        if (i == 2) {   // a word before the last is found
            break;
        };
        token = strtok(NULL, delims);
    }

    int letter = token[strlen(token) - 2];
    buffer.erase(index);
    last_line += ":" + to_string(letter) + '\n';
    buffer = buffer + last_line;

    in_file.close();
    ofstream out_file(filename);
    out_file << buffer;
    out_file.close();
}


void create_file_cstyle(char *filename) {
    void fill_file_cstyle(char *filename, char *mode);

    bool entered = false;
    string choice;
    do {
        if (choice == "Y" || choice == "y") {
            fill_file_cstyle(filename, (char *) "a");
        } else {
            if (!entered) {
                fill_file_cstyle(filename, (char *) "w");
                entered = true;
            }
        }
        cout << "Do you want to add more text (y/n)" << endl;
        cin >> choice;
        cin.ignore();
    } while (choice == "Y" || choice == "y");
}

void fill_file_cstyle(char *filename, char *mode) {

    FILE *fptr = fopen(filename, mode);
    if (!fptr) {
        cerr << "Error opening a file \"" << filename;
    }

    char line[257];

    cout << "Enter text (up to 256 symbols), type in \"#\" to stop\n";

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#' && line[1] == '\n') {
            break;
        }
        int line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
            line_len--;
        }
        fprintf(fptr, "%s\n", line);
    }
    fclose(fptr);
}

void read_file_cstyle(char *filename) {
    FILE *fptr = fopen(filename, "r");
    char ch;

    if (fptr == NULL) {
        cerr << "Error opening a file!\n" << endl;
        return;
    }

    cout << "\n" << filename << ":\n";

    do {
        ch = fgetc(fptr);
        printf("%c", ch);
    } while (ch != EOF);
}

//writes ciphered text to the same file
void cipher_file_cstyle(char *filename) {

    void shift_cstyle(char *line, int k);
    char *copy = "copy.txt";

    FILE *in_file = fopen(filename, "r");
    FILE *new_out_file = fopen(copy, "w");

    char line[256];
    int k;

    cout << "\nEnter a k parameter (number of chars to shift)" << endl;
    cin >> k;

    if (!in_file || !new_out_file) {
        cout << "Error opening a file!" << endl;
        exit(1);
    }

    while (fgets(line, sizeof(line), in_file)) {
        shift_cstyle(line, k);
        fprintf(new_out_file, "%s", line);
        strset(line, 0);
    };

    fclose(in_file);
    fclose(new_out_file);

    copy_file_cstyle(copy, filename);

}

void copy_file_cstyle(char *source, char *target) {
    int ch;
    FILE *source_file = fopen(source, "r");
    FILE *target_file = fopen(target, "w");

    if (source_file == NULL || target_file == NULL) {
        cerr << "Error while working with a file!" << endl;
    }

    while ((ch = getc(source_file)) != EOF)putc(ch, target_file);
    fclose(source_file);
    fclose(target_file);
}

void shift_cstyle(char *line, int k) {

    for (int i = 0; i < strlen(line); i++) {
        if (isupper(line[i])) {
            int val = line[i] - 'A';
            val = (val + k) % 26;
            char c2 = 'A' + val;
            line[i] = c2;
        } else if (islower(line[i])) {
            int val = line[i] - 'a';
            val = (val + k) % 26;
            char c2 = 'a' + val;
            line[i] = c2;
        }
    }
}

void create_newfile_cstyle(char *filename, char *newFilename) {
    void change_str_cstyle(char *str);
    FILE *new_out_file = fopen(newFilename, "w");
    FILE *in_file = fopen(filename, "r");

    bool isOdd = true;
    char line[256];

    while (fgets(line, sizeof(line), in_file)) {
        if (isOdd) {
            change_str_cstyle(line);
            fprintf(new_out_file, "%s", line);
        }
        isOdd = !isOdd;
    };

    fclose(new_out_file);
    fclose(in_file);

}

void reverse_string_cstyle(char *str) {
    if (str == NULL) {
        return;
    }

    char *start = str;
    char *end = start + strlen(str) - 1;

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void change_str_cstyle(char *str) {
    void reverse_string_cstyle(char *line);
    const char *delims = "., ";
    int i = 0;

    // Create a copy of the reversed string
    char rev_line[256];
    strcpy(rev_line, str); //

    int str_len = strlen(str);   // довжина строки
    reverse_string_cstyle(rev_line);    // міняємо порядок у строці
    reverse_string_cstyle(str);
    // пошук 2 слова
    char *token = strtok(rev_line, delims);

    while (token != NULL) {
        i++;
        if (i == 2) {   // a word before the last is found
            break;
        };
        token = strtok(NULL, delims);
    }


    if (token != NULL) { // token is a second-to-last word
        char *pos = strstr(str, token); // position of a word in reversed string - покажчик на порядок слова у строці
        // first second third fourth
        // first  third fourth' '
        char* spaced_token= (char*)malloc(sizeof(token)+1);


        memset(spaced_token, ' ', sizeof(char));
        strcpy(spaced_token+1,token);


        strcpy(pos, pos + strlen(token));   // pos - призначення, pos + strlen(token) - звідки - пересовуємо на місце

        str[strlen(str)]=' ';
        strcpy(str + str_len - strlen(token) , spaced_token);  // з кінця віднімаємо кількість в токені - куди ми копіюємо, звідки


        reverse_string_cstyle(str);
//        cout << str << token << endl;
        free(spaced_token);


    } else {
        strcpy(str, rev_line);
    }
}

void change_last_line_cstyle(char *filename) {
    char last_line[260];
    char line_2[260];
    int lines_count = 0;
    copy_file_cstyle(filename, "copy.txt");

    FILE *in_file = fopen("copy.txt", "r"); // копія файлу
    FILE *out_file = fopen(filename, "w");  //


    while (fgets(last_line, sizeof(last_line), in_file) != NULL) {   //проходимося по копії, щоб порахувати к-ть ліній та знайти останню
        lines_count++;
    };

    rewind(in_file);    //покажчик на початок

    for (int i = 0; i < lines_count - 1; i++) {          // на 1 лінію менше ніж в орігінал файлі
        fgets(line_2, sizeof(line_2), in_file);     // беремо по лінії з файлу копії
        fprintf(out_file, "%s ", line_2);              // вписуємо в оригінал файл
    }

    //cout << "\nLast line " << last_line << endl;


    char copied_line[260];
    strcpy(copied_line, last_line);

    int str_len = strlen(last_line);

    const char *delims = "., ";
    int word_count = 0;


    char *token = strtok(copied_line, delims);


    while (token != NULL) {
        word_count++;
        if (word_count == 2) {   // a word before the last is found
            break;
        };
        token = strtok(NULL, delims);
    }


    if (token != NULL) { // token is a second word
        int code = token[strlen(token) - 2]; //code of a character before last
        last_line[str_len - 1] = ':';
        itoa(code, last_line + str_len, 10);
    }

    fprintf(out_file, "%s", last_line);

    fclose(in_file);
    fclose(out_file);
}

