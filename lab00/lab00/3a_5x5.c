#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define N 5
#define CELL_MAX (N * N - 1)


void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[N][N]) {
    int cell = 0;

    print_sep(N);
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(N);
    }
}

char get_winner(char board[N][N])
{
    char winner = '-';
    int i = 0, j = 1;
    while (i < N){
        //  líneas vericales
        //  loop donde los valores en ´x´ son constantes
        while ((board[i][j] == board[i][j - 1]) && j < N && (board[i][j] != '-')){
            //  si se llega al final del array y todas los valores en una columna son iguales
            //  el ganador es el jugador de ese valor
            if (j == N - 1){
                winner = board[i][j];
                return winner;
            }
            j = j + 1;
        }

        //  líneas horizontales
        //  loop donde los valores en ´y´ son constantes
        j = 1;
        while ((board[j][i] == board[j - 1][i]) && j < N && (board[j][i] != '-')) {
            //  si se llega al final del array y todas los valores en una fila son iguales
            //  el ganador es el jugador de ese valor
            if (j == N - 1){
                winner = board[j][i];
                return winner;
            }
            j = j + 1;
        }
        j = 1; i = i + 1;
    }

    //  diagonales de izquierda a derecha
    //  loop donde ´x´ e ´y´ son iguales
    while (j < N && (board[j][j] == board[j - 1][j - 1]) && (board[j][j] != '-')) {
        if (j == N - 1){
            winner = board[j][j];
            return winner;
        }
        j = j + 1;
    }

    //  diagonales de derecha a izquierda
    //  se comparan los valores de adentro hacia afuera 
    //  con los valores de ´x´ aumentando e ´y´ disminuyendo
    //  empezando en la segunda casilla desde las esquinas
    //  [0, 3], [1, 2], [2, 1], [3, 0]
    j = 1; i = N - 2;
    while (j < N && (board[j][i] == board[j - 1][i + 1]) && (board[j][i] != '-')){
        if (j == N - 1){
            winner = board[j][i];
            return winner;
        }
        j = j + 1; i = i - 1;
    }
    return winner;
}

bool has_free_cell(char board[N][N]) {
    //  se recorre toda la matriz hasta encontrar una celda vacía
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < N) {
            //  si encuentra una celda vacía:
            if (board[i][j] == '-') {
                //  interrumpe la función y devuelve true
                return true;
            } else {
                j = j + 1;
            }
        }
        i = i + 1;
    }
    //  si al terminar la matriz no encontró ninguna celda vacía devuelve false
    return false;
}

int main(void)
{
    printf("TicTacToe [incompleto]\n");

    //  se declara
    char board[N][N];
    
    //  se inicializa
    int x = 0;
    while (x < N) {
        int y = 0;
        while (y < N) {
            board[x][y]='-';
            y = y + 1;
        }
        x = x + 1;
    }
    
    //  turno ´X´ y ganador vacío
    char turn = 'X';
    char winner = '-';

    //  si no terminó:
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);

        //  se pide al jugador que juegue su turno por consola
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        
        //  se revisa que no haya errores en el escanéo
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        
        //  si la celda elegida existe:
        if (cell >= 0 && cell <= CELL_MAX) {
            
            //  la fila elegida es el piso de la división entre el número de filas
            int row = cell / N;
            //  la columna elegida es el resto de la división entre el número de columnas
            int colum = cell % N;
            
            //  si la celda está vacía se juga el turno
            if (board[row][colum] == '-') {
                //  se coloca el caractér necesario en la posición necesaria
                board[row][colum] = turn;
                
                //  se cambia el turno
                turn = turn == 'X' ? 'O' : 'X';
                
                //  se decide si hay ganador
                winner = get_winner(board);
            } else {    //  si la celda no está vacía, error
                printf("\nCelda ocupada!\n");
            }
        } else {    //  si la celda elegida no existe, error
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
