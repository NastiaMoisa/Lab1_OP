#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "Functions.h"


int main(int argc, char* argv[]) {

    string filename = "MyFile.txt";
    string newfilename = "MyEncryptedFile.txt";
    char* filename_cstyle = "MyFileCstyle.txt";
    char* new_filename_cstyle = "MyEncryptedFileCstyle.txt";

    if (argc<3){
        cerr << "Choose a mode (filestream or filepointer)\n" << endl;
        return 1;
    }

    //argv[2]="filepointer";

    if(!strcmp(argv[2],"filestream")){

        create_file(filename); // створення файлу
        read_file(filename); // відображення вмісту
        cipher_file(filename); // шифрування файлу

        create_newfile(filename,newfilename); //зміна вмісту старого файлу
        change_last_line(newfilename);
        read_file(newfilename); //відображення вмісту зміненого файлу

    } else if(!strcmp(argv[2],"filepointer")) {

        create_file_cstyle(filename_cstyle); // створення файлу
        read_file_cstyle(filename_cstyle); // відображення вмісту

        cipher_file_cstyle(filename_cstyle); // шифрування файлу

        create_newfile_cstyle(filename_cstyle, new_filename_cstyle); //зміна вмісту старого файлу
        change_last_line_cstyle(new_filename_cstyle);

        read_file_cstyle(new_filename_cstyle);
    }
    return 0;

}
