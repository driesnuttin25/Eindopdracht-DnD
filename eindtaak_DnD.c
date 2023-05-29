#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPELL_AMOUNT 4
#define HISTORY_FILE "history.txt"

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
    newNode->next = *head; // making a circle instead of a straight line
  }
}

// Function to parse JSON and extract the required values, just this took me way too long and i dont like it. next time im using jansson or c-json.
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

  free(jsonCopy); // gotta save that memory
}

// this actually displays the values in the console
void displayCard(Node *current) {
  printf("Index: %s\n", current->spell.index);
  printf("Name: %s\n", current->spell.name);
  printf("URL: %s\n\n", current->spell.url);
}

// writing all my actions in a file because extra points
void writeHistory(const char *action, Node *current) {
  FILE *file = fopen(HISTORY_FILE, "a");
  if (file == NULL) {
    printf("Error opening history file.\n");
    return;
  }

  fprintf(file, "Action: %s\n", action);
  fprintf(file, "Index: %s\n", current->spell.index);
  fprintf(file, "Name: %s\n", current->spell.name);
  fprintf(file, "URL: %s\n\n", current->spell.url);

  fclose(file);
}

// only use if your teachers ask you to, but for reasons only my tired brain can understand I'm going to leave it out
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

// Function to remove the current card from the linked list, could have written this in the main but wanted to be fancy
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
  Node *head = NULL;
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

    // Allocate memory for the JSON string cause otherwise i get lovely segmentation faults
    char *jsonString = (char *)malloc(fileSize + 1);

    // Read the file content into the JSON string
    fread(jsonString, 1, fileSize, file);
    jsonString[fileSize] = '\0'; // Gotta end that string on a null terminator

    fclose(file);

    // Parse that bad boy
    parseJSON(jsonString, &head);

    // Look at me using memory correctly
    free(jsonString);
  }

  //printList(head);

  Node *current = head;
  char choice[10];

  while (1) {
    printf("next, previous, use\n");
    scanf("%s", choice);

    if (strcmp(choice, "next") == 0) {
      system("clear");
      current = current->next;
      displayCard(current);
      writeHistory("next", current);
    } else if (strcmp(choice, "previous") == 0) {
      system("clear");
      Node *temp = head;
      // only way i got it work. isn't modular but its 22 at night and i could find out how.
      while (temp->next != current) {
        temp = temp->next;
      }

      current = temp;
      displayCard(current);
      writeHistory("previous", current);
    } else if (strcmp(choice, "use") == 0) {
      system("clear");
      Node *temp = current->next;
      writeHistory("use", current);
      printf("You used\n");
      displayCard(current);
      removeCard(&head, current);
      current = temp;
    } else {
      system("clear");
      printf("I have no clue what you're trying to type, man.\n");
    }
  }

  return 0;
}
