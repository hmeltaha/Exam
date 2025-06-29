#include <stdlib.h>
#include <stdio.h>

void print_board(int *board, int n)
{
    int i;
    /* int j; */

    for (i = 0; i < n - 1; i++)
        printf("%d ", board[i]);
    printf("%d\n", board[i]);
}

int    *copy_board(int *board, int n)
{
    int    *new_board;
    int    i;

    if (!board)
    {
        new_board = malloc(n * sizeof(int));
        if (!new_board)
            return (NULL);
        for (i = 0; i < n; i++)
            new_board[i] = -1;
        return (new_board);
    }
    new_board = malloc(n * sizeof(int));
    if (!new_board)
        return (NULL);
    for (i = 0; i < n; i++)
        new_board[i] = board[i];
    return (new_board);
}

void    nqueens(int *board, int new_queen_y, int n)
{
    int    y = 0;
    int    x = 0;
    int    valid;

    board = copy_board(board, n);
    if (new_queen_y == n)
    {
        print_board(board, n);
        return ;
    }
    while (x < n)
    {
        y = 0;
        valid = 1;
        while (y < new_queen_y)
        {
            if (x == board[y]
                || x - board[y] == y - new_queen_y
                || x - board[y] == new_queen_y - y)
            {
                valid = 0;
                break ;
            }
            y++;
        }
        if (valid)
        {
            board[new_queen_y] = x;
            nqueens(board, new_queen_y + 1, n);
        }
        x++;
    }
}

int    main(int argc, char **argv)
{
    int    n;
    /* int    i; */

    if (argc != 2)
        return (1);
    n = atoi(argv[1]);
    /* i = -1; */
    nqueens(NULL, 0, n);
    return (0);
}