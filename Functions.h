using namespace  std;

void create_file(string filename); // створення файлу
void read_file(string filename); // відображення вмісту
void cipher_file(string filename); // шифрування файлу
void create_newfile(string filename,string newFilename);
string shift(string, int);
void change_last_line(string);


void create_file_cstyle(char*);
void cipher_file_cstyle(char*); // шифрування файлу
void read_file_cstyle(char* );
void create_newfile_cstyle(char*,char*);
void change_last_line_cstyle(char*);
void copy_file_cstyle(char* source, char* target);
