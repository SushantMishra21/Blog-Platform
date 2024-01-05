#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

struct BlogPost {
    char title[100];
    char content[500];
};

struct User {
    char username[50];
    char password[50];
    struct BlogPost *posts;
    int postCount;
};

int userCount = 0;
struct User users[MAX_USERS];

void registerUser() {
    if (userCount < MAX_USERS) {
        printf("Enter your username: ");
        scanf("%s", users[userCount].username);
        printf("Enter your password: ");
        scanf("%s", users[userCount].password);

        users[userCount].posts = NULL;
        users[userCount].postCount = 0;

        printf("Registration successful!\n");
        userCount++;
    } else {
        printf("Maximum user limit reached. Cannot register more users.\n");
    }
}

int loginUser() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return i;  // Return the index of the logged-in user
        }
    }

    printf("Invalid username or password. Login failed.\n");
    return -1;  // Return -1 to indicate login failure
}

void collectUserRequirements(struct User *user) {
    int choice;
    do {
        printf("\nMenu:\n1. Register\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                return;  // Return to continue with the logged-in user
            case 3:
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);
}

void createBlogPost(struct User *user) {
    struct BlogPost newPost;
    printf("Enter the title of your blog post: ");
    scanf(" %[^\n]", newPost.title);
    printf("Write your blog post content: ");
    scanf(" %[^\n]", newPost.content);

    user->posts = realloc(user->posts, (user->postCount + 1) * sizeof(struct BlogPost));
    user->posts[user->postCount] = newPost;
    user->postCount++;
    printf("Blog post created successfully!\n");
}

void displayUserBlog(struct User *user) {
    printf("\n%s's Blog:\n", user->username);
    for (int i = 0; i < user->postCount; ++i) {
        printf("Title: %s\n", user->posts[i].title);
        printf("Content: %s\n", user->posts[i].content);
        printf("----------------------------\n");
    }
}

int main() {
    int loggedInUserIndex;

    do {
        collectUserRequirements(&users[userCount]);
        loggedInUserIndex = loginUser();
    } while (loggedInUserIndex == -1);

    int choice;
    do {
        printf("\nMenu:\n1. Create Blog Post\n2. Display Blog\n3. Logout\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createBlogPost(&users[loggedInUserIndex]);
                break;
            case 2:
                displayUserBlog(&users[loggedInUserIndex]);
                break;
            case 3:
                printf("Logging out... Thank you!\n");
                loggedInUserIndex = -1;  // Reset logged-in user index
                break;
            case 4:
                printf("Exiting... Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    free(users[loggedInUserIndex].posts);

    return 0;
}
