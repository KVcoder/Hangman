#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int is_in_array(char *array, char item)
{
    int length_of_array = sizeof(array) / sizeof(array[0]);
    //printf("%d", length_of_array);
    for (int i = 0; i < length_of_array; i++)
    {
        if (array[i] == item)
        {
            return 1;
        }
    }
    return 0;
}

void add_to_array(char *array, char item)
{
    int length_of_array = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < length_of_array; i++)
    {
        if (array[i] == '\0')
        {
            array[i] = item;
            break;
        }
    }
}

void game(char *chosen_word)
{
    printf(chosen_word);
    char guess_array[26] = {'\0'};
    printf("Welcome to Hangman!\n");
    printf("Let's Begin\n");
    printf(" \n\n");
    int running = 1;

    while (running)
    {
        char guess;
        printf("Enter a letter: ");
        // get our guess
        scanf("%c", &guess);
        // eat all other characters
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            

        // test if guess is alphabetic
        if (!isalpha(guess))
        {
            printf("Please enter a letter!\n\n");
            continue;
        }
        // convert guess to lowercase
        tolower(guess);

        if (!is_in_array(guess_array, guess))
        {
            add_to_array(guess_array, guess);
        }
        int length_of_word = strlen(chosen_word);
        int count = 0;
        for (int i = 0; i < length_of_word-3 ; i++)
        {
            if (is_in_array(guess_array, chosen_word[i])== 1)
            {
                printf("%c", chosen_word[i]);
                count+=1;
            }
            else
            {
                printf("_");
            }
        }
        printf("\n");

        if (count == length_of_word-3)
        {
            printf("You win!\n");
            break;
        }
    }
}

int lineCounter(FILE *file)
{
    int linesCount = 0;
    char ch;
    if (file == NULL)
    {
        printf("File does not exist!!!\n");
        return -1;
    }
    // read character by character and check for new line
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    /* Points the file pointer to the beginning of the file.
     It just checks the beginning of the file with no offset to where we look at the file*/
    fseek(file, 0, SEEK_SET);
    return linesCount;
}

int main()
{
    srand(time(0));

    FILE *file = fopen("./randomWords.txt", "r");
    fseek(file, 0, SEEK_SET);

    int num_lines = lineCounter(file);
    if (num_lines == -1)
    {
        printf("No Lines in File!\n");
        exit(-1);       
    }
    // chooses a random line
    int chosen_line = rand() % num_lines;
    // char *chosen_word;
    if (file != NULL)
    { 
        int count = 0;
        char line[256];
        while (fgets(line, sizeof line, file) != NULL)
        {           
            if (count == chosen_line)
            {
                char* chosen_word[sizeof(line)];
                strncpy(chosen_word, line, sizeof(line));
                game(chosen_word);
                break;
            }
            count++;
        }
        
        fclose(file);
    }
    else
    {
        printf("file does not exist");
        return 0;
    } 
    return 0;
}
