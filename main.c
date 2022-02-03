#include <stdio.h>
#include <stdlib.h>
#define MAX_MINES 10

void build_table(int rows, int cols, char (*table)[rows][cols]);
void set_mines(int rows, int cols, char (*table)[rows][cols]);
void print_table(int rows, int cols, char table[rows][cols], int show_solution);
void solve_mines(int rows, int cols, char (*table)[rows][cols]);
void init_game();

int main()
{
    printf("Pr%cctica #1 - Matrices - Fundamentos de Programaci%cn - ICC-103 - PUCMM\nPresentado por: Jean Luis Jim%cnez\n", 160, 162, 130);
    init_game();

    return 0;
}

void build_table(int rows, int cols, char (*table)[rows][cols])
{
    int row, col;
    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            /* Para crear el tablero, y no dejar los espacios vacios
            decidi llenarlo con 0 los cuales quedaran igual si no se
            detecta ninguna mina cerca */
            (*table)[row][col] = '0';
        }
    }
}

void set_mines(int rows, int cols, char (*table)[rows][cols])
{
    int row, col, currentMines = 0;
    time_t t;
    srand((char) time(&t));
    for (currentMines = 0; currentMines < MAX_MINES;)
    {
        row = rand() % rows;
        col = rand() % cols;

        /* Para evitar que se posicionen 2 minas en el mismo
        lugar primero se verifica que no exista ninguna mina
        en es lugar para el momento. */
        if ((*table)[row][col] != '*')
        {
            (*table)[row][col] = '*';
            currentMines++;
        }
    }
}

void solve_mines(int rows, int cols, char (*table)[rows][cols])
{
    int row, col, mines;

    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            mines = 0;
            // Si es una mina no es necesario verificar minas de alrededor
            if ((*table)[row][col] == '*') continue;

            /* Para analizar cada posicion al rededor de la posicion actual
            cada una de las siguientes lineas revisan una posicion empezando por
            la esquina superior izquierda, y terminando en la esquina inferior derecha
            de las posiciones al rededor. */
            if (col - 1 >= 0 && row - 1 >= 0 && (*table)[row - 1][col - 1] == '*') mines++;
            if (row - 1 >= 0 && (*table)[row - 1][col] == '*') mines++;
            if (col + 1 < cols && row - 1 >= 0 && (*table)[row - 1][col + 1] == '*') mines++;
            if (col - 1 >= 0 && (*table)[row][col - 1] == '*') mines++;
            if (col + 1 < cols && (*table)[row][col + 1] == '*') mines++;
            if (col - 1 >= 0 && row + 1 < rows && (*table)[row + 1][col - 1] == '*') mines++;
            if (row + 1 < rows && (*table)[row + 1][col] == '*') mines++;
            if (col + 1 < cols && row + 1 < rows && (*table)[row + 1][col + 1] == '*') mines++;

            (*table)[row][col] += mines;
        }

    }
}

void print_table(int rows, int cols, char table[rows][cols], int show_solution)
{
    int row, col;

    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            if (table[row][col] == '*')
            {
                printf("* ");
            }
            /* Para no hacer 2 funciones con objetivos similares
            añadi una condicion para decidir si mostrar la solucion o no,
            de esta manera el codigo puede ser reutilizado para imprimir
            tanto la solucion como el tablero solo con minas */
            else if (show_solution)
            {
                printf("%c ", table[row][col]);
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

        char table[rows][cols];

        build_table(rows, cols, &table);

        set_mines(rows, cols, &table);

        solve_mines(rows, cols, &table);

        printf("Matriz generada:\n");
        print_table(rows, cols, table, 0); // 0 no mostrar la solucion

        printf("Soluci%cn del juego:\n", 162);
        print_table(rows, cols, table, 1); // 1 mostrar la solucion
    }
    else
    {
        printf("Intenta de nuevo con una opcion v%clida...\n", 160);
        init_game(option);
    }
}
