#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *trim(char *str)
{
    char *start = str;
    char *end = str + strlen(str);

    while (*start && isspace(*start))
        start++;

    while (end > start && isspace(*(end - 1)))
        end--;

    *end = '\0';
    return start;
}

int parse_line(char *line, char **key, char **value)
{
    char *ptr = strchr(line, '=');
    if (ptr == NULL)
        return -1;

    *ptr++ = '\0';
    *key = trim(line);
    *value = trim(ptr);

    return 0;
}

int main()
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    char *key, *value;

    printf("\nEnter the State or Union Territory: ");

    fp = fopen("contact_data.txt", "r");
    if (fp == NULL)
    {
        printf("Please specify the correct filename with location on disk.\n");
        return -1;
    }

    char state[15];
    gets(state);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (parse_line(line, &key, &value))
            continue;

        if (strcmp(state, key) == 0)
        {
            printf("\nPlease inform the Directorate General, Fire Services of %s in order to subjugate the threat.\n\nCONTACT NUMBER : %s\n", state,value);
            break;
        }
    }

    free(line);
    fclose(fp);
    return 0;
}