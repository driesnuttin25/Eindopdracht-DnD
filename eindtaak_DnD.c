#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPELL_AMOUNT 4

// Define the struct to hold the parsed data
typedef struct {
  char index[100];
  char name[100];
  char url[100];
} SpellInfo;

// Define the linked list node
typedef struct Node {
  SpellInfo spell;
  struct Node *next;
} Node;

// Function to add a new node to the linked list
void addNode(Node **head, SpellInfo spell) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->spell = spell;
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
    newNode->next = newNode; // Connect the first node to itself
  } else {
    Node *current = *head;
    while (current->next != *head) {
      current = current->next;
    }
    current->next = newNode;
    newNode->next = *head; // Connect the last node to the first node
  }
}

// Function to parse JSON and extract the required values
void parseJSON(char *jsonString, Node **head) {
  SpellInfo spell;
  bool foundIndex = false;
  bool foundURL = false;

  char *jsonCopy = strdup(jsonString); // Make a copy of the JSON string
  char *token = strtok(jsonCopy, ",{}\":");
  while (token != NULL) {
    if (strcmp(token, "index") == 0) {
      if (!foundIndex) {
        token = strtok(NULL, ",{}\": ");
        strcpy(spell.index, token);
        foundIndex = true;
      }
    } else if (strcmp(token, "name") == 0) {
      token = strtok(NULL, ",{}\": ");
      strcpy(spell.name, token);
    } else if (strcmp(token, "url") == 0) {
      if (!foundURL) {
        token = strtok(NULL, ",{}\": ");
        strcpy(spell.url, token);
        foundURL = true;
        // Add the parsed data to the linked list
        addNode(head, spell);
      }
    }

    token = strtok(NULL, ",{}\":");
  }

  free(jsonCopy); // Free the copied string
}

// Function to print a single card from the linked list
void displayCard(Node *current) {
  printf("Index: %s\n", current->spell.index);
  printf("Name: %s\n", current->spell.name);
  printf("URL: %s\n\n", current->spell.url);
}

// Function to print the linked list
// Function to print the linked list
void printList(Node *head) {
  if (head == NULL) {
    printf("The list is empty.\n");
    return;
  }

  Node *current = head;
  do {
    displayCard(current);
    current = current->next;
  } while (current != head);
}


// Function to remove the current card from the linked list
void removeCard(Node **head, Node *current) {
  if (*head == NULL) {
    printf("No cards left in the deck.\n");
    return;
  }

  if (current == *head) {
    *head = (*head)->next;
  } else {
    Node *prev = *head;
    while (prev->next != current) {
      prev = prev->next;
    }
    prev->next = current->next;
    if (current->next == *head) {
      *head = prev; // Update the head pointer if the last node is removed
    }
  }

  free(current);
}

int main() {
  // Create a linked list to store the parsed data
  Node *head = NULL;

  // JSON file names
  char jsonFiles[SPELL_AMOUNT][100] = {"sacred-flame.json", "acid-splash.json",
                                       "aid.json", "calm-emotions.json"};

  // Parse each JSON file and populate the linked list
  for (int i = 0; i < SPELL_AMOUNT; i++) {
    FILE *file = fopen(jsonFiles[i], "r");
    if (file == NULL) {
      printf("Error opening file: %s\n", jsonFiles[i]);
      continue;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the JSON string
    char *jsonString = (char *)malloc(fileSize + 1);

    // Read the file content into the JSON string
    fread(jsonString, 1, fileSize, file);
    jsonString[fileSize] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    // Parse the JSON and populate the linked list
    parseJSON(jsonString, &head);

    // Free the allocated memory
    free(jsonString);
  }

  // Print the linked list
  //printList(head);

  Node *current = head;
  char choice[10];

  while (1) {
    printf("next, previous, use \n");
    scanf("%s", choice);

    if (strcmp(choice, "next") == 0) {
      system("clear");
  current = current->next;
  displayCard(current);
} else if (strcmp(choice, "previous") == 0) {
  system("clear");
  Node *temp = head;

  // Find the previous node in the circular linked list
  while (temp->next != current) {
    temp = temp->next;
  }

  current = temp;
  displayCard(current);
}

     else if (strcmp(choice, "use") == 0) {
       system("clear");
      Node *temp = current->next;
      removeCard(&head, current);
      current = temp;
      printf("Card removed from the deck.\n");
    } else {
       system("clear");
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
