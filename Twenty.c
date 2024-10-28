#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    char* question; // Question or guess
    struct node* yes;  // Pointer to the next node if the answer is yes
    struct node* no;   // Pointer to the next node if the answer is no
};

struct node* createNode(char* question) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->question = strdup(question); // Copy the question/guess into the node
    newNode->yes = NULL;
    newNode->no = NULL;
    return newNode;
}

struct node* insert(struct node* root, char* question, char* yesGuess, char* noGuess) {
    if (root == NULL) {
        root = createNode(question);
    }

    if (yesGuess != NULL) {
        root->yes = createNode(yesGuess);
    }

    if (noGuess != NULL) {
        root->no = createNode(noGuess);
    }

    return root;
}

struct node* create_game_tree() {
    struct node* root = NULL;

    root = insert(root, "Does it grow underground?", NULL, NULL);
    root->yes = insert(root->yes, "Is it long in shape?", NULL, NULL);
    root->yes->yes = insert(root->yes->yes, "Is it orange in color?", "It's a carrot!", "It's a parsnip!");
    root->yes->no = insert(root->yes->no, "Is it red in color?", "It's a radish!", "It's a potato!");

    root->no = insert(root->no, "Does it grow on a tree?", NULL, NULL);
    root->no->yes = insert(root->no->yes, "Is it red in color?", "It's an apple!", "It's a peach!");
    root->no->no = insert(root->no->no, "Is it red in color?", "It's a tomato!", "It's a pea!");

    return root;
}

void play_game(struct node* root) {
    struct node* current = root;
    char answer[3];

    while (current != NULL) {
        printf("%s\n", current->question);
        printf("y/n: ");
        scanf("%s", answer);

        if (strcmp(answer, "y") == 0) {
            if (current->yes != NULL && current->yes->question != NULL) {
                current = current->yes;
            } else {
                printf("I win!\n");
                return;
            }
        } else if (strcmp(answer, "n") == 0) {
            if (current->no != NULL && current->no->question != NULL) {
                current = current->no;
            } else {
                printf("You win!\n");
                return;
            }
        } else {
            printf("Invalid response. Please answer 'y' or 'n'.\n");
        }
    }
}

int main() {
    struct node* game_tree = create_game_tree();

    printf("Welcome! Press 'q' to quit or any other key to continue:\n");

    char c;
    scanf("%c", &c);
    while (c != 'q') {
        play_game(game_tree);
        printf("Press 'q' to quit or any other key to continue:\n");
        scanf(" %c", &c); // The space before %c is to consume the newline character left in the input stream
    }

    printf("Bye Bye!\n");
    return 0;
}
