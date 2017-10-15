/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// board blank
int BS = 0;

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int position1, int position2);
int get_tile_position(int number);
bool is_left(int tpos, int zpos);
bool is_right(int tpos, int zpos);
bool is_below(int tpos, int zpos);
bool is_above(int tpos, int zpos);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    printf("initializing: \n");
    for(int i = 0, n = d * d - 1, j = n;i <= n; i++, j-- ) {
        board[i/d][i%d] = j;
        printf("board[%i][%i] = %i\n", i/d, i%d, board[i/d][i%d]);
    }
    if (d % 2 == 0) {
        swap(d * d - 2, d * d - 3);
    }
    printf("After swap: \n");
    for(int i = 0, n = d * d - 1; i <= n; i++) {
        printf("board[%i][%i] = %i\n", i/d, i%d, board[i/d][i%d]);
    }
}

int get_tile_position(int number) {
    for(int i = 0, n = d * d - 1; i <= n; i++) {
        if(board[i/d][i%d] == number)
            return i;
    }
    return -1;
}

void swap(int position1, int position2) {
    int temp = board[position1/d][position1%d];
    board[position1/d][position1%d] = board[position2/d][position2%d];
    board[position2/d][position2%d] = temp;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0, n = d*d; i < n; i++) {
        if(board[i/d][i%d] == 0) {
            printf(" _");
        }
        else {
            printf("%2i", board[i/d][i%d]);
        }
        if(i % d == (d - 1)) {
            printf("\n");
        }
        else {
            printf(" ");
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    int tpos = get_tile_position(tile);
    int zpos = get_tile_position(0);
    if(is_left(tpos, zpos) || is_right(tpos, zpos) || is_above(tpos, zpos) || is_below(tpos, zpos)) {
        swap(tpos, zpos);
        return true;
    }else {
        return false;
    }
}

bool is_left(int tpos, int zpos) {
    //make sure they're on the same line
    bool same_line = tpos / d == zpos / d;
    //and that tile position is one less column than zero tile.
    bool tile_one_column_less = zpos % d - tpos % d == 1;
    //however, make sure zero position is greater or equals to one
    bool zero_not_zero_column = zpos % d > 0;
    return same_line && tile_one_column_less && zero_not_zero_column;
}

bool is_right(int tpos, int zpos) {
    //make sure they're on the same line
    bool same_line = tpos / d == zpos / d;
    //and that tile position is one more column than zero tile.
    bool tile_one_column_more = tpos % d - zpos % d == 1;
    //however, make sure that zero column is not the last one.
    bool zero_not_last_column = zpos % d < d - 1;
    return same_line && tile_one_column_more && zero_not_last_column;
}

bool is_below(int tpos, int zpos) {
    //make sure they're on the same column,
    bool same_column = tpos % d == zpos % d;
    //and that tile position is one more row that zero tile.
    bool tile_one_row_more = tpos / d - zpos / d == 1;
    //however, make sure that tile is at most, in the last row, that is, zero is nt in the last row
    bool zero_not_last_row = zpos / d < d - 1;
    return same_column && tile_one_row_more && zero_not_last_row;

}

bool is_above(int tpos, int zpos) {
    // make sure they're on the same column,
    bool same_column = tpos % d == zpos % d;
    // and that the tile position is one less row than zero tile.
    bool tile_one_row_less = zpos / d - tpos / d == 1;
    //however, make sure that tile is at least zero, or that zero tile is never zero.
    bool zero_not_first_row = zpos / d > 0;
    return same_column && tile_one_row_less && zero_not_first_row;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    for(int i = 0, n = d * d - 1; i < n; i++) {
        if(board[i/d][i%d] != i + 1) {
            return false;
        }
    }
    return board[d - 1][d - 1] == 0;
}
