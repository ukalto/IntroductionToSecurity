#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>


void
initialize_seed(void) {
        unsigned int seed;
        int fd;

        fd = open("/dev/urandom", O_RDONLY);
        if (fd < 0) {
                fprintf(stderr, "Error.\n");
                exit(1);
        }
        read(fd, &seed, sizeof(unsigned int));
        close(fd);
        srand(seed);
}


void
read_file(void) {
        unsigned char content[128];
        FILE *file;

        file = fopen("./flag", "r");
        if (file != NULL) {
                fscanf(file, "%s", content);
                fclose(file);
                printf("You seized the opportunity and stole some secrets: %s\n", content);
        } else {
                fprintf(stderr, "Error while opening the file.\n");
                exit(1);
        }
        return;
}


void
get_information(void) {
        unsigned char correct_hash[20] = {
                0xea, 0x61, 0xdf, 0x0f, 0x8b, 0x18, 0x0b, 0x2c, 0x4a, 0xe0,
                0xcb, 0xd1, 0x49, 0x32, 0x9e, 0xd4, 0xd9, 0x27, 0xc7, 0x91
        };
        unsigned char salt[8] = {0x61,0x73,0x39,0x62,0x32,0x33,0x42,0x45};
        // as9b23BE
        unsigned char password[20];
        unsigned char salted_password[28];
        printf("What we didn't tell you, you still need the password to decipher the information:\n");
        scanf("%45s", password);
        memcpy(salted_password, salt, 8);
        memcpy(salted_password+8, password, 20);
        SHA1(salted_password, strlen((char *)salted_password), password);
        if (memcmp(password, correct_hash, 20) == 0) {
                read_file();
        } else {
                printf("WRONG PASSWORD!\n");
        }
}


void
game(void) {
        int set_coins;
        int user_input;
        int guess;
        unsigned int coins = 10;
        printf("You bought 10 coins to play\n");

        while (true) {
                if (coins == 0) {
                        printf("Thank you for playing. Unfortunately, you lost everything. Bye, see you the next time.\n");
                        return;
                }
                printf("Enter 1 for playing the next round, enter 2 for buying valuable information\n");
                printf("> ");
                fflush(stdout);

                if (scanf("%d", &user_input) != 1) {
                        fprintf(stderr, "SOMETHING WENT WRONG");
                        exit(1);
                }
                if (user_input == 1) {
                        printf("You currently own %d coins - \n", coins);

                        printf("Set coins. If you guess the number we roll, you get back the double amount otherwise you lose them\n");
                        printf("> ");
                        fflush(stdout);

                        if (scanf("%d", &set_coins) != 1) {
                                fprintf(stderr, "SOMETHING WENT WRONG");
                                exit(1);
                        }
                        if (set_coins > (int)coins) {
                                printf("You cannot set more coins than you own!\n");
                                continue;
                        }else {
                                coins = coins - set_coins;
                        }
                        printf("Guess a number between 1 and 12 to win the game:\n");
                        printf("> ");
                        fflush(stdout);

                        if (scanf("%d", &guess) != 1) {
                                fprintf(stderr, "SOMETHING WENT WRONG");
                                exit(1);
                        }

                        if ((rand() % 12) +1 == guess) {
                                printf("You won %d coin\n", set_coins * 2);
                                coins = coins + set_coins * 2;
                        } else {
                                printf("You lost %d coin\n", set_coins);
                        }
                } else if(user_input == 2) {
                        if (coins > 99999999) {
                                get_information();
                                coins = coins - 99999999;
                        } else {
                                printf("You need 99999999 coins to buy the secret.\n");
                        }
                } else {
                        return;
                }
        }
}


int
main(void) {
        initialize_seed();
        game();
        fflush(stdout);
        return 0;
}