#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

enum Condition
{
    FAILURE = 0,
    SUCCESS = 1,
};

enum Condition compressor(FILE * file_input, FILE * file_output);
void decompressor(FILE * file_input, FILE * file_output);

#define $ fprintf(stderr, "%s:%d in function: %s\n", __FILE__, __LINE__, __func__);

int main(void)
{
    FILE * file_input = fopen("input.txt", "rb");
    if (file_input == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return 0;
    }

    FILE * file_output = fopen("output.txt", "rb");
    if (file_output == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return 0;
    }

    FILE * decrypted_file = fopen("decrypted.txt", "wb");
    if (decrypted_file == NULL)
    {
        fprintf(stderr, "The file could not be opened.\n");
        return 0;
    }

    compressor(file_input, file_output);
    decompressor(file_output, decrypted_file);

    if (fclose(file_input))
    {
        fprintf(stderr, "Error closing the file.\n");
        return 0;
    }

    if (fclose(file_output))
    {
        fprintf(stderr, "Error closing the file.\n");
        return 0;
    }

    if (fclose(decrypted_file))
    {
        fprintf(stderr, "Error closing the file.\n");
        return 0;
    }

    return 0;
}

enum Condition compressor(FILE * file_input, FILE * file_output)
{
    assert(file_input != NULL);
    assert(file_output != NULL);

    int next_char = 0;
    int previous_char = 0;
    int number_of_repetitions = 0;
    bool series_of_repetitions = false;

    if ((previous_char = getc(file_input)) == EOF) { return FAILURE; }
    while ((next_char = getc(file_input)) != EOF)
    {
        if (next_char == previous_char)
        {
            series_of_repetitions = true;
            number_of_repetitions++;
        }
        else
        {
            (series_of_repetitions) ? fprintf(file_output, "%c%c", number_of_repetitions + 1, previous_char)
                                    : fprintf(file_output, "%c%c",                         1, previous_char);

            series_of_repetitions = false;
            number_of_repetitions =     0;
        }
        previous_char = next_char;
    }
    fprintf(file_output, "%c%c", 1, previous_char);
    return SUCCESS;
}

void decompressor(FILE * file_input, FILE * file_output)
{
    assert(file_input != NULL);
    assert(file_output != NULL);

    int quantity = 0;
    int current_char = 0;

    while ((quantity = getc(file_input)) != EOF)
    {
        if ((current_char = getc(file_input)) == EOF) { break; }
        for (int i = 0; i < quantity; i++)
        {
            putc(current_char, file_output);
        }
    }
}
