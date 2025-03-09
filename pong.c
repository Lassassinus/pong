#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define PLAYER_SPEED 1

#define WALL '#'
#define PLAYER_CHAR '@'
#define BALL_CHAR '@'
#define EMPTY_SPACE '.'

#define P1_UP 'a'
#define P1_DOWN 'z'
#define P2_UP 'k'
#define P2_DOWN 'm'
#define PASS_TURN ' '

void draw_game_field(int player1, int player2, int ball_x, int ball_y);

int player_is_here(int y_coord, int player_y);

int main() {

  int player_1, player_2;
  player_1 = HEIGHT / 2;
  player_2 = HEIGHT / 2;
  int score_1, score_2;
  score_1 = 0;
  score_2 = 0;

  int ball_x, ball_y, x_speed, y_speed;
  ball_x = WIDTH / 2;
  ball_y = HEIGHT / 2;
  x_speed = -1;
  y_speed = -1;

  while (1) {
    // clear screen
    printf("\e[1;1H\e[2J");
    printf("Score 1: %d\nScore 2: %d\n", score_1, score_2);
    draw_game_field(player_1, player_2, ball_x, ball_y);

    // USER INPUT STARTS HERE
    char player_input;
    scanf("%c\n", &player_input);

    if (player_input == P1_UP) {
      player_1 -= PLAYER_SPEED;
    } else if (player_input == P1_DOWN) {
      player_1 += PLAYER_SPEED;
    } else if (player_input == P2_UP) {
      player_2 -= PLAYER_SPEED;
    } else if (player_input == P2_DOWN) {
      player_2 += PLAYER_SPEED;
    }
    // USER INPUT ENDS HERE

    // BALL LOGICK HERE
    ball_x += x_speed;
    ball_y += y_speed;

    // Rebound from top and bottom walls
    if (ball_y + y_speed == 0 || ball_y + y_speed == HEIGHT) {
      y_speed *= -1;
    }

    if ((ball_x + x_speed == -1) || (ball_x + x_speed == WIDTH)) {
      
    if (ball_x + x_speed == -1) {
        score_2 += 1;
        printf ("Player_2 scored! Score: %d - %d\n", score_1, score_2);
      }
      if (ball_x + x_speed == WIDTH){
        score_1 += 1;
        printf ("Player_1 scored! Score: %d - %d\n", score_1, score_2);
      }
      player_1 = HEIGHT / 2;
      player_2 = HEIGHT / 2;
      ball_x = WIDTH / 2;
      ball_y = HEIGHT / 2;
      
      // x_speed *= -1;
    }
  }
}
void draw_game_field(int player1, int player2, int ball_x, int ball_y) {
  char raw[WIDTH + 1];
  raw[WIDTH - 1] = '\0';

  for (int i = 0; i <= HEIGHT; ++i) {
    char filler;

    // Generate top and bottom walls
    if (i == 0 || i == HEIGHT) {
      filler = WALL;
      // Generate middle raws
    } else {
      filler = EMPTY_SPACE;
    }

    // Left and right walls and ball
    raw[0] = raw[WIDTH - 2] = '#';
    for (int j = 1; j <= WIDTH - 3; ++j) {
      raw[j] = filler;

      // Draw ball
      if (j == ball_x && i == ball_y) {
        raw[j] = BALL_CHAR;
      }
    }

    if (player_is_here(i, player1)) {
      raw[2] = PLAYER_CHAR;
    }
    if (player_is_here(i, player2)) {
      raw[WIDTH - 4] = PLAYER_CHAR;
    }

    printf("%s\n", raw);
  }
}

int player_is_here(int y_coord, int player_y) {

  if (y_coord == player_y || (y_coord >= player_y - RACKET_SIZE / 2 &&
                              y_coord <= player_y + RACKET_SIZE / 2)) {
    return 1;
  } else {
    return 0;
  }
}