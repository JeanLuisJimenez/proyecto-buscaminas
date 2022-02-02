#include <stdio.h>
#include <stdlib.h>
#define MAX_MINES 10

void build_matrix(int rows, int cols, char (*matrix)[rows][cols]);
void set_mines(int rows, int cols, char (*matrix)[rows][cols]);
void print_table(int rows, int cols, char matrix[rows][cols], int show_solution);
void solve_mines(int rows, int cols, char (*matrix)[rows][cols]);
void init_game();

int main()
{
    printf("Pr%cctica #1 - Matrices - Fundamentos de Programaci%cn - ICC-103 - PUCMM\nPresentado por: Jean Luis Jim%cnez\n", 160, 162, 130);
    init_game();

    return 0;
}

void build_matrix(int rows, int cols, char (*matrix)[rows][cols])
{
    int row, col;
    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            (*matrix)[row][col] = '0';
        }
    }
}

void set_mines(int rows, int cols, char (*matrix)[rows][cols])
{
    int row, col, currentMines = 0;
    time_t t;
    srand((char) time(&t));
    for (currentMines = 0; currentMines < MAX_MINES;)
    {
        row = rand() % rows;
        col = rand() % cols;

        if ((*matrix)[row][col] != '*')
        {
            (*matrix)[row][col] = '*';
            currentMines++;
        }
    }
}

void solve_mines(int rows, int cols, char (*matrix)[rows][cols])
{
    int row, col, mines;

    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            mines = 0;
            if ((*matrix)[row][col] == '*') continue;
            if (col - 1 >= 0 && row - 1 >= 0 && (*matrix)[row - 1][col - 1] == '*') mines++;
            if (row - 1 >= 0 && (*matrix)[row - 1][col] == '*') mines++;
            if (col + 1 < cols && row - 1 >= 0 && (*matrix)[row - 1][col + 1] == '*') mines++;
            if (col - 1 >= 0 && (*matrix)[row][col - 1] == '*') mines++;
            if (col + 1 < cols && (*matrix)[row][col + 1] == '*') mines++;
            if (col - 1 >= 0 && row + 1 < rows && (*matrix)[row + 1][col - 1] == '*') mines++;
            if (row + 1 < rows && (*matrix)[row + 1][col] == '*') mines++;
            if (col + 1 < cols && row + 1 < rows && (*matrix)[row + 1][col + 1] == '*') mines++;


            (*matrix)[row][col] = '0' + mines;
        }

    }
}

void print_table(int rows, int cols, char matrix[rows][cols], int show_solution)
{
    int row, col;

    if (show_solution)
    {
        printf("Matriz generada:\n");
    }
    else
    {
        printf("Soluci%cn del juego:\n", 162);
    }

    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            if (matrix[row][col] == '*')
            {
                printf("* ");
            }
            else if (show_solution)
            {
                printf("%c ", matrix[row][col]);
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void init_game()
{
    int option;
    printf("Menu:\n\tJugar Buscaminas: 1\n\tSalir del juego: 2\n\nIndique la opci%cn: ", 162);
    scanf("%d", &option);
    printf("\n\n");
    if (option == 2)
    {
        printf("Bye!");
        return;
    }
    else if (option == 1)
    {
        int rows = 0, cols = 0;
        printf("Indique la dimensi%cn de la matriz filas y columnas (Max: 100, min: 1): ", 162);

        scanf("%d %d", &rows, &cols);

        char matrix[rows][cols];

        build_matrix(rows, cols, &matrix);

        set_mines(rows, cols, &matrix);
        solve_mines(rows, cols, &matrix);
        print_table(rows, cols, matrix, 0); // 0 means to no show table solution
        print_table(rows, cols, matrix, 1); // 1 means to show table solution
    }
    else
    {
        printf("Intenta de nuevo con una opcion v%clida...\n", 160);
        init_game(option);
    }
}
