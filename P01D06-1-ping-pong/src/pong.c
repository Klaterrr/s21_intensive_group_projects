#include <stdio.h>

int winCondition();
void updateBoard(int fpRocketPosition, int spRocketPosition, int ballPositionX, int ballPositionY);

int main() {
    int isStilPlaying = 1;
    int ballSpeed = 1;
    int ballPositionX = 40;
    int ballPositionY = 12;
    int ballCurrentAngle = 45;
    int onRocket = 0;
    int fpScore = 0;
    int spScore = 0;
    int fpRocketPosition = 12;
    int spRocketPosition = 12;
    char action;
    int winScore = 21;

    while (fpScore < winScore && spScore < winScore) {
        updateBoard(fpRocketPosition, spRocketPosition, ballPositionX, ballPositionY);
        printf("First Player score: %d, Second Player score: %d\n", fpScore, spScore);
        scanf(" %c", &action);
        if (action == 'q') {
            break;
        }
        if (((action == 'a') || (action == 'A')) && (fpRocketPosition > 2)) {
            fpRocketPosition = fpRocketPosition - move;
        } else if (((action == 'z') || (action == 'Z')) && (fpRocketPosition < 23)) {
            fpRocketPosition = fpRocketPosition + move;
        }
        if (((action == 'k') || (action == 'K')) && (spRocketPosition > 2)) {
            spRocketPosition = spRocketPosition - move;
        } else if (((action == 'm') || (action == 'M')) && (spRocketPosition < 23)) {
            spRocketPosition = spRocketPosition + move;
        }

        if (ballPositionX <= 2) {
            if ((ballPositionY == fpRocketPosition) || (ballPositionY - 1 == fpRocketPosition) ||
                (ballPositionY + 1 == fpRocketPosition)) {
                if (ballPositionY == fpRocketPosition) {
                    onRocket = 1;
                } else {
                    onRocket = 2;
                }
                ballSpeed = -ballSpeed;
            } else {
                spScore++;
                onRocket = 0;
                ballPositionX = 40;
                ballPositionY = 12;
            }
        }

        if (ballPositionX >= 78) {
            if ((ballPositionY == spRocketPosition) || (ballPositionY - 1 == spRocketPosition) ||
                (ballPositionY + 1 == spRocketPosition)) {
                if (ballPositionY == spRocketPosition) {
                    onRocket = 1;
                } else {
                    onRocket = 2;
                }
                ballSpeed = -ballSpeed;
            } else {
                fpScore++;
                onRocket = 0;
                ballPositionX = 40;
                ballPositionY = 12;
            }
        }
        if (onRocket == 1) {
            ballCurrentAngle = 0;
        } else if (onRocket == 2) {
            ballCurrentAngle = 45;
        }
        if (ballPositionY == 1 && (ballCurrentAngle != 0)) {
            ballCurrentAngle = -ballCurrentAngle;
        } else if (ballPositionY == 24 && (ballCurrentAngle != 0)) {
            ballCurrentAngle = -ballCurrentAngle;
        }

        ballPositionX = ballPositionX + ballSpeed;
        if (ballCurrentAngle == 45) {
            ballPositionY = ballPositionY + ballSpeed;
        } else if (ballCurrentAngle == -45) {
            ballPositionY = ballPositionY - ballSpeed;
        }

        onRocket = 0;
    }

    if (fpScore >= winScore) {
        printf("First Player Wins\n");
    } else if (spScore >= winScore) {
        printf("Second Player Wins\n");
    }
    return 0;
}

void updateBoard(int fpRocketPosition, int spRocketPosition, int ballPositionX, int ballPositionY) {
    int x, y;
    for (int x = 1; x <= 80; x++) {
        printf("-");
    }
    printf("\n");

    for (y = 1; y <= 24; y++) {
        for (x = 1; x <= 80; x++) {
            if (x == 1 && (y == fpRocketPosition || y == fpRocketPosition + 1 || y == fpRocketPosition - 1)) {
                printf("|");
            } else if (x == 80 &&
                       (y == spRocketPosition || y == spRocketPosition + 1 || y == spRocketPosition - 1)) {
                printf("|");
            } else if (x == ballPositionX && y == ballPositionY) {
                printf("*");
            } else
                printf(" ");
        }
        printf("\n");
    }

    for (x = 1; x <= 80; x++) {
        printf("-");
    }
    printf("\n");
}