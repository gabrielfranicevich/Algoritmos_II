#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define CELL_MAX (3 * 3 - 1)

void print_sep(int length) {
    //  length define el tamaño en horizontal
    printf("\t ");
    for (int i = 0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[3][3]){
    int cell = 0;

    print_sep(3);
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}

char get_winner(char board[3][3]){
    char winner = '-';
    int i = 0, j = 1;
    while (i < 3){
        //  líneas vericales
        //  loop donde los valores en ´x´ son constantes
        while ((board[i][j] == board[i][j - 1]) && j < 3 && (board[i][j] != '-')){
            //  si se llega al final del array y todas los valores en una columna son iguales
            //  el ganador es el jugador de ese valor
            if (j == 2){
                winner = board[i][j];
                return winner;
            }
            j = j + 1;
        }

        //  líneas horizontales
        //  loop donde los valores en ´y´ son constantes
        j = 1;
        while ((board[j][i] == board[j - 1][i]) && j < 3 && (board[j][i] != '-')){
            //  si se llega al final del array y todas los valores en una fila son iguales
            //  el ganador es el jugador de ese valor
            if (j == 2){
                winner = board[j][i];
                return winner;
            }            
            j = j + 1;
        }
        j = 1; i = i + 1;
    }

    //  diagonales de izquierda a derecha
    //  loop donde ´x´ e ´y´ son iguales
    while (j < 3 && (board[j][j] == board[j - 1][j - 1]) && (board[j][j] != '-')){
        if (j == 2){
            winner = board[j][j];
            return winner;
        }
        j = j + 1;
    }

    //  diagonales de derecha a izquierda
    //  se comparan los valores del centro con los valores de ´x´ aumentando e ´y´ disminuyendo
    j = 1; i = 1;
    while (j < 3 && (board[j][i] == board[j - 1][i + 1]) && (board[j][i] != '-')){
        if (j == 2){
            winner = board[j][i];
            return winner;
        }
        j = j + 1; i = i - 1;
    }
    return winner;
}

bool has_free_cell(char board[3][3]){
    //  se recorre toda la matriz hasta encontrar una celda vacía
    int i = 0;
    while (i < 3){
        int j = 0;
        while (j < 3){
            //  si encuentra una celda vacía:
            if (board[i][j] == '-'){
                //  interrumpe la función y devuelve true
                return true;
            }else {
                j = j + 1;
            }
        }
        i = i + 1;
    }
    //  si al terminar la matriz no encontró ninguna celda vacía devuelve false
    return false;
}

int main(void){
    
    printf("TicTacToe [Incompleto]\n");

    //  inicialización del tablero vacío, turno ´X´ y ganador vacío
    char board[3][3] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };
    char turn = 'X';
    char winner = '-';
    
    //  si no terminó:
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);

        //  se pide al jugador que juegue su turno por consola
        printf("\nTurno de %c - Elija posición (número del 0 al %d): ", turn,
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
            int row = cell / 3;
            //  la columna elegida es el resto de la división entre el número de columnas
            int colum = cell % 3;
            
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
