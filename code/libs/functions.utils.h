
char *str_cat(char *first, char *last) {
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

int tab_length(char *tab[]) {
    for (int i = 0; i < 5; ++i) {
        if(tab[i] == NULL) {
            return i;
        }
    }
    return 0;
}