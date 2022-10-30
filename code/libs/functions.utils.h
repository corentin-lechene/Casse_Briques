
char *str_cat(const char *first, const char *last);
char *str_trim(char *str);
char *str_get_left(char *line, char separator);
char *str_get_right(char *line, char separator);

char *file_get_value(const char *attribute, const char *dir);


void text_color(int color);
void text_color_default();

void clear_console();
void exit_error(char *desc);
void errorf(char *err);
void warningf(char *warn);

char *set_value(char *value);

void die();


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


void text_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void text_color_default() {
    text_color(COLOR_DEFAULT);
}

void clear_console() {
    system("cls");
//    printf("\033[2J\033[1;1H");
}
void exit_error(char *desc) {
    text_color(color_red);
    printf("Erreur-> %s", desc);
    text_color_default();
    exit(0);
}
void errorf(char *err) {
    text_color(color_red);
    printf("Erreur-> %s\n", err);
    text_color_default();
}
void warningf(char *warn) {
    text_color(color_yellow);
    printf("Warning-> %s\n", warn);
    text_color_default();
}

char *set_value(char *value) {
    char *v = malloc(sizeof(char) * strlen(value));
    strcpy(value, v);
    return v;
}

void die() {
    exit(0);
}
