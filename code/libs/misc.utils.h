
char *str_trim(char *str) {
    if(str == NULL) {
        return NULL;
    }

    unsigned short index = 0;

    printf("[%s]\n", str);

    int i = 0;
    while (str[i] == ' ') {
        i++;
    }

    //fixme crash here
    for (int j = i; str[j] != ' ' ; ++j) {
        str[index++] = str[j];
    }
    str[index] = '\0';

    char *res = malloc(sizeof(char) * (index + 1));
    strcpy(res, str);

    printf("[[%s]]", res);
    return res;
}
