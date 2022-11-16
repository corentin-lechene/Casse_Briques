
int my_getch();

char *str_cat(const char *first, const char *last);
char *str_trim(char *str);
char *str_get_left(char *line, char separator);
char *str_get_right(char *line, char separator);

char *file_get_value(const char *attribute, const char *dir);
short file_display_content(const char *path);
char *file_get_content(const char *filename, int start_of_file);
short file_get_nb(const char *dir);
short file_get_size(FILE *f);

void text_color(int color);
void text_color_default();
enum colors_index get_random_color();

void increment_or_reset(unsigned short *val, short max);
void decrement_or_reset(unsigned short *val, short max);
double random_between(double min, double max);
int min_distance(int top, int right, int bottom, int left);

void clear_console();
void exit_error(char *desc);
void infof(char *err);
void errorf(char *err);
void warningf(char *warn);

char *set_value(char *value);

void die();
void pause();


/* ---===       --------        ===--- */

char *str_cat(const char *first, const char *last) {
    unsigned short len = strlen(first) + strlen(last) ;
    char *cat = malloc(sizeof(char) * (len + 1));
    strcat(strcpy(cat, first), last);
    cat[len] = '\0';
    return cat;
}
char *str_trim(char *str) {
    unsigned int len = strlen(str);
    if(len <= 0 || str[0] == '\0' || str[0] == '\n') {
        return NULL;
    }
    char temp[len + 1];

    int offset = 0;
    while(str[offset] == ' ') {
        offset++;
    }

    if(offset == len) {
        return NULL;
    }

    int index = 0;
    for(int i = offset ; str[i] != '\0' && str[i] != '\n' ; i++ ) {
        temp[index++] = str[i];
    }

    while(temp[index - 1] == ' ') {
        index--;
    }
    temp[index] = '\0';
    char *res = malloc(sizeof(char) * index + 1);
    strcpy(res, temp);
    return res;
}
char *str_get_left(char *line, char separator) {
    if(strlen(line) <= 0) {
        return NULL;
    }

    char *temp = malloc(sizeof(char) * 255);
    int i = 0;
    while (line[i] != separator) {
        if(line[i] == '\0' || line[i] == '\n') {
            break;
        }
        temp[i] = line[i];
        i++;
    }
    temp[i] = '\0';
    return str_trim(temp);
}
char *str_get_right(char *line, char separator) {
    if(strlen(line) <= 0) {
        return NULL;
    }

    char *temp = malloc(sizeof(char) * 255);
    for (int i = 0; i < strlen(line); ++i) {
        if(line[i] == separator) {
            i++;
            int index = 0;
            while (line[i] != '\n' && line[i] != '\0') {
                temp[index] = line[i];
                index++;
                i++;
            }
            temp[index] = '\0';
            break;
        }
    }
    return str_trim(temp);
}

char *file_get_value(const char *attribute, const char *dir) {
    FILE *f = fopen(dir, "r");

    if(f != NULL) {
        char *line = malloc(sizeof(char) * 255);
        char *file_att, *file_value;

        while (fgets(line, 255, f) != NULL) {
            if(strcmp(line, "\n") == 0) {
                continue;
            }
            file_att = str_get_left(line, '=');
            file_value = str_get_right(line, '=');
            if(strcmp(attribute, file_att) == 0) {
                fclose(f);
                free(file_att);
                return file_value;
            }
        }
    }
    printf("-= FILE NOT FOUND =-\n");
    return NULL;
}
char *file_set_value(const char *attribute, void *value, const char *dir) {
    FILE *f = fopen(dir, "rb+");

    if(f != NULL) {
        char *file_temp = calloc(0, sizeof(char) * (file_get_size(f) + 1));
        char *line = malloc(sizeof(char) * 255);
        char *file_att, *file_val;

        while (fgets(line, 255, f) != NULL) {
            if(strcmp(line, "\n") == 0) {
                continue;
            }
            file_att = str_get_left(line, '=');
            file_val = str_get_right(line, '=');

            if(strcmp(attribute, file_att) == 0) {
                char *file_content = file_get_content(dir, ftell(f));

                if(file_content == NULL) {
                    printf("-= FILE CONTENT =-\n");
                    return NULL;
                }

                fseek(f, -(strlen(file_val) + 1), SEEK_CUR);
                printf("[%s%s = %s\n%s]", file_temp, file_att, value, file_content);
                fclose(f);

                f = fopen(dir, "wb");
                fprintf(f, "%s%s = %s\n%s", file_temp, file_att, value, file_content);

                fclose(f);
                free(file_att);
                free(file_val);
                free(file_temp);
                free(file_content);
                return NULL;
            }
            strncat(file_temp, line, strlen(line));
        }
    }
    printf("-= FILE NOT FOUND =-\n");
    return NULL;
}
char *file_get_content(const char *filename, int start_of_file) {
    FILE *f = fopen(filename, "rb");

    if(f != NULL) {
        fseek (f, 0, SEEK_END);
        int len = ftell(f) - start_of_file;
        char *content = malloc(sizeof(char) * (len + 1));

        if(content != NULL) {
            fseek (f, start_of_file, SEEK_SET);
            fread(content, 1, len, f);
            content[len] = '\0';

            fseek(f, 0, SEEK_SET);
            fclose(f);
            return content;
        }
        fseek (f, 0, SEEK_SET);
        fclose(f);
        return NULL;
    }
    return NULL;
}
short file_display_content(const char *path) {
    FILE *f = fopen(path, "r");

    if(f != NULL) {
        while (!feof(f)) {
            printf("%c", fgetc(f));
        }
        fclose(f);
        return 1;
    }
    return 0;
}
short file_get_nb(const char *dir_name) {
    struct dirent *dir;
    DIR *d = opendir(dir_name);
    short count = 0;

    if(d != NULL) {
        while ((dir = readdir(d)) != NULL) {
            if(dir->d_name[0] != '.') {
                count += 1;
            }
        }
        closedir(d);
        return count;
    }
    warningf("Ouverture du dossier impossible");
    return 0;
}
short file_get_size(FILE *f) {
    fseek (f, 0, SEEK_END);
    short len = ftell(f);
    fseek (f, 0, SEEK_SET);
    return len;
}

void text_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void text_color_default() {
    text_color(COLOR_DEFAULT);
}

enum colors_index get_random_color() {
    enum colors_index colors[] = {
            color_blue,
            color_green,
            color_magenta,
            color_yellow,
            color_cyan,
            color_light_blue,
            color_light_green,
            color_light_cyan,
            color_red,
            color_light_magenta
    };
    return colors[(int) random_between(0, 10)];
}
double random_between(double min, double max) {
    return min + ((int)rand() % (int)max);
}
int min_distance(int top, int right, int bottom, int left) {
    int values[] = {top, right, bottom, left};

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (values[i] > values[j]) {
                int t = values[i];
                values[i] = values[j];
                values[j] = t;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        if(values[i] != 0) {
            return values[i];
        }
    }
    return 0;
}
void increment_or_reset(unsigned short *val, short max) {
    if(*val + 1 > max) {
        *val = 0;
        return;
    }
    *val += 1;
}

void decrement_or_reset(unsigned short *val, short max) {
    if(*val - 1 < 0) {
        *val = max;
        return;
    }
    *val -= 1;
}


void clear_console() {
    system("cls");
//    printf("\033[2J\033[1;1H");
}
void exit_error(char *desc) {
    text_color(color_red);
    printf("Erreur-> %s\n", desc);
    text_color_default();
    pause();
    exit(0);
}
void infof(char *err) {
    text_color(color_light_blue);
    printf("[INFO] -> %s\n", err);
    text_color_default();
}
void errorf(char *err) {
    text_color(color_red);
    printf("Erreur-> %s\n", err);
    text_color_default();
    pause();
}
void warningf(char *warn) {
    text_color(color_yellow);
    printf("Warning-> %s\n", warn);
    text_color_default();
}

char *set_value(char *value) {
    char *v = malloc(sizeof(char) * strlen(value) + 1);
    strcpy(v, value);
    return v;
}

void pause() {
    system("pause");
}
void die() {
    exit(0);
}

int my_getch()  {
    int ch = _getch ();

    if (ch == 0 || ch == 224) {
        int ch2 = _getch();
        switch (ch2) {
            case 72:
            case 80:
            case 75:
            case 77:
            case 13:
            case 27:
                return ch2;

            default:
                return -1;
        }
    } else {
        switch (ch) {
            case 'z':
            case 's':
            case 'q':
            case 'd':
            case 'p':
            case 32:
            case 13:
            case 27:
                return ch;
            default:
                return -1;
        }
    }
}

int gt_zero(int num) {
    return num >= 0;
}
int lt_row(unsigned short x, Map *map) {
    return x < map->rows;
}
int lt_column(unsigned short y, Map *map) {
    return y < map->columns;
}
int is_in_rows(int x, Map *map) {
    return gt_zero(x) && lt_row(x, map);
}
int is_in_column(int y, Map *map) {
    return gt_zero(y) && lt_column(y, map);
}
int is_in_map(int x, int y, Map *map) {
    return is_in_rows(x, map) && is_in_column(y, map);
}