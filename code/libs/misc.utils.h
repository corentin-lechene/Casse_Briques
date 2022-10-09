
char *str_trim(char *str) {
    if(str == NULL) {
        return NULL;
    }

    char *res;
    unsigned short index = 0;
    unsigned short new_len = strlen(str);
    for (int i = 0; i < strlen(str); ++i) {
        if(str[i] == ' ') {
            new_len--;
            continue;
        }
        str[index++] = str[i];
    }
    str[new_len] = '\0';

    res = malloc(sizeof(char) * (new_len + 1));
    strcpy(res, str);
    return res;
}
