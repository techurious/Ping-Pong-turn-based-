#include <math.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int speed;
} Ball;

typedef struct {
    int x;
    int y;
    int height;
} Paddle;

void ball_init(Ball *ball);

void ball_move(Ball *ball);

void ball_bounce_wall(Ball *ball);

int ball_hits_paddle(Ball ball, Paddle left_paddle, Paddle right_paddle);

void ball_check_score(Ball *ball, int *score1, int *score2);

int main() {
    Ball ball;
    Paddle left_paddle, right_paddle;
    int score1 = 0, score2 = 0;

    ball_init(&ball);
    left_paddle.x = 1;
    left_paddle.height = 3;
    left_paddle.y = ((25 - left_paddle.height) / 2);
    right_paddle.x = 78;
    right_paddle.height = 3;
    right_paddle.y = ((25 - right_paddle.height) / 2);

    while (score1 < 21 && score2 < 21) {
        printf("\033[H\033[J");
        char input;
        char second;
        int valid = 0;

        while (valid == 0) {
            scanf("%c%c", &input, &second);

            if (input != '\n' && second == '\n' &&
                (input == 'a' || input == 'z' || input == 'k' || input == 'm' || input == ' ')) {
                valid = 1;
            }
            while (getchar() != '\n') {
            }
        }

        if (input == 'a') {
            if (left_paddle.y > 0) {
                left_paddle.y = left_paddle.y - 1;
            }
        }

        else if (input == 'z') {
            if (left_paddle.y < 25 - left_paddle.height) {
                left_paddle.y = left_paddle.y + 1;
            }

        } else if (input == 'k') {
            if (right_paddle.y > 0) {
                right_paddle.y = right_paddle.y - 1;
            }
        } else if (input == 'm') {
            if (right_paddle.y < 25 - right_paddle.height) {
                right_paddle.y = right_paddle.y + 1;
            }
        } else if (input == ' ') {
        }

        ball_move(&ball);
        ball_bounce_wall(&ball);
        if (ball_hits_paddle(ball, left_paddle, right_paddle) == 1) {
            ball.dx = -ball.dx;
        }
        ball_check_score(&ball, &score1, &score2);
    }

    return 0;
}

void ball_init(Ball *ball) {
    ball->x = 40;
    ball->y = 12;
    ball->dx = 1;
    ball->dy = 1;
    ball->speed = 1;
}

void ball_move(Ball *ball) {
    ball->x += ball->dx * ball->speed;
    ball->y += ball->dy * ball->speed;
}

void ball_bounce_wall(Ball *ball) {
    if (ball->y <= 0 || ball->y >= 24) {
        ball->dy = -ball->dy;
    }
}

int ball_hits_paddle(Ball ball, Paddle left_paddle, Paddle right_paddle) {
    int collide_check = 0;

    if (ball.dx == -1 && ball.x == 2 && ball.y >= left_paddle.y &&
        ball.y <= left_paddle.y + left_paddle.height - 1) {
        collide_check = 1;
    } else if (ball.dx == 1 && ball.x == 77 && ball.y >= right_paddle.y &&
               ball.y <= right_paddle.y + right_paddle.height - 1) {
        collide_check = 1;
    }

    return collide_check;
}

void ball_check_score(Ball *ball, int *score1, int *score2) {
    if (ball->x < 0) {
        (*score2)++;
        ball_init(ball);
    } else if (ball->x > 79) {
        (*score1)++;
        ball_init(ball);
    }
}