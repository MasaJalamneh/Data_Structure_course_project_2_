// Name: Masa Ahmad Jalamneh
// Id: 1212145
// Section: 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


////////////////\\\\\\\\\\\\\\
// Structure function for student information
struct Node {
    int ID;
    char Name[70];
    char Address[100];
    int ClassID;
    char DateOfEnrollment[50];
    struct Node* Left;
    struct Node* Right;
};
typedef struct Node* TNode;// declare TNode Of type

////////////////\\\\\\\\\\\\\\\\
// Function to create a new node for each student
TNode CreateNode(int id, const char* name, const char* address, int classID, const char* enrollmentDate) {
    TNode T = (TNode)malloc(sizeof(struct Node)); // memory allocate the new node
    T->ID = id;                                                                  // store id (int)
    strncpy(T->Name, name, sizeof(T->Name));                                     // store name (string)
    strncpy(T->Address, address, sizeof(T->Address));                            // store address (int)
    T->ClassID = classID;                                                        // store class id (string)
    strncpy(T->DateOfEnrollment, enrollmentDate, sizeof(T->DateOfEnrollment));   // store enrollment date (string)
    T->Left = NULL;         // part of creating the node is to make the left pointer point on null
    T->Right = NULL;        // part of creating the node is to make the right pointer point on null too
    return T;
}

////////////////\\\\\\\\\\\\\\\\
// Function to insert a student node into the BST
TNode Insert(TNode root, TNode T) { // root: tree root , T: new student node
    if (root == NULL) {
        return T;
    }

    if (T->ID < root->ID) //case: if the given id is less then the root id then go to left sub tree
    {
        root->Left = Insert(root->Left, T);
    } else if (T->ID > root->ID) //case: if the given id is greater then the root id then go to right sub tree
    {
        root->Right = Insert(root->Right, T);
    } else // case: where Student with the same ID already exists, support updating student info
      {
        strcpy(root->Name, T->Name);                        // update the new name
        strcpy(root->Address, T->Address);                  // update the new address
        root->ClassID = T->ClassID;                         // update the new class id
        strcpy(root->DateOfEnrollment, T->DateOfEnrollment);// update the new enrollment date
        free(T); // Free the temporary node
      }

    return root;
}

////////////////\\\\\\\\\\\\\\\\
// Function to find a given node
TNode Find(TNode T, int X){
    if( T == NULL)
        return NULL;

    else if( X < T->ID ) // go find in left sub tree if the inserted id is less than the root id
        return Find( T->Left, X );

    else if( X > T->ID )// go find in right sub tree if the inserted id is greater than the root id
        return Find( T->Right, X);

    else
        return T;
}

////////////////\\\\\\\\\\\\\\\
// Function to find the minimum value stored in the tree (left sub tree)
TNode FindMin(TNode T )
{
    if( T != NULL) // left most
        while( T->Left != NULL)
            T = T->Left;
    return T;
}

////////////////\\\\\\\\\\\\\\\
// Function to find the maximum value stored in the tree (right sub tree)
TNode FindMax(TNode T )
{
    if( T != NULL) // right most
        while( T->Right != NULL)
            T = T->Right;
    return T;
}


//============================================= case 2 helping functions begin ===================================================
////////////////\\\\\\\\\\\\\\\\\
// Function to update a student node in the tree based on student ID
TNode UpdateStudent(TNode root, int studentID,  char newName[70], char newAddress[100], int newClassID, char newEnrollmentDate[50] ) {
    // search for the node with the given student ID to update
    if (studentID < root->ID) {
        root->Left = UpdateStudent(root->Left,  studentID,   newName[70],  newAddress[100],  newClassID,  newEnrollmentDate[50]);
    } else if (studentID > root->ID) {
        root->Right = UpdateStudent(root->Right, studentID,  newName[70],  newAddress[100],  newClassID,  newEnrollmentDate[50]);
    } else  // Node with the student ID is found, update the desired fields
        {

        // Update the student information

        strncpy(root->Name, newName, sizeof(root->Name));
        strncpy(root->Address, newAddress, sizeof(root->Address));
        root->ClassID = newClassID;
        strncpy(root->DateOfEnrollment, newEnrollmentDate, sizeof(root->DateOfEnrollment));
    }

    return root;
}
//============================================= case 2 helping functions end ===================================================


//============================================= case 3 helping functions begin ===================================================
/////////////////\\\\\\\\\\\\\\\\
// Function to insert a student into the BST based on students names
TNode InsertStudentByName(TNode root, TNode newNode) {
    if (root == NULL) {
        return newNode;
    }

    int compareResult = strcmp(newNode->Name, root->Name);// Compare names lexicographically

    if (compareResult < 0) // if the new name is lexicographically less than the root name
    {
        root->Left = InsertStudentByName(root->Left, newNode);
    } else if (compareResult > 0) // if the new name is lexicographically greater than the root name
    {
        root->Right = InsertStudentByName(root->Right, newNode);
    } else {
        // Student with the same name already exists, update the student info
        root->ID = newNode->ID;
        strncpy(root->Name, newNode->Name, sizeof(root->Name));
        strncpy(root->Address, newNode->Address, sizeof(root->Address));
        root->ClassID = newNode->ClassID;
        strncpy(root->DateOfEnrollment, newNode->DateOfEnrollment, sizeof(root->DateOfEnrollment));
        free(newNode); // Free the temporary node
    }

    return root;
}

////////////////\\\\\\\\\\\\\\\
// Function to perform in-order traversal of the tree and print student names (To Print)
void InOrderTraversal(TNode root) {
    if (root != NULL) {
        InOrderTraversal(root->Left); // print the left side
        printf("Student ID: %d, Name: %s, address: %s, class id: %d, date of enrollment: %s\n", root->ID, root->Name , root->Address , root->ClassID , root->DateOfEnrollment);
        InOrderTraversal(root->Right);// print the left side
    }
}

////////////////\\\\\\\\\\\\\\\
// Function to help to perform the recursive copying and sorting (by names)
TNode TreeCopy2(TNode root, TNode newTree) {
    if (root == NULL) {
        return newTree;
    }

    newTree = TreeCopy2(root->Left, newTree);       //to copy the left subtree
    newTree = InsertStudentByName(newTree, CreateNode(root->ID, root->Name, root->Address, root->ClassID, root->DateOfEnrollment)); // Insert node to the copy tree by name
    newTree = TreeCopy2(root->Right, newTree);      //to copy the right subtree

    return newTree;
}

////////////////\\\\\\\\\\\\\\\
// Function to copy a binary search tree and sort it by name
TNode copyTree1(TNode root) {
    TNode newTree = NULL;
    newTree = TreeCopy2(root, newTree);
    return newTree;
}
//============================================= case 3 helping functions end ===================================================


//============================================= case 4 helping functions begin ===================================================
//////////////////\\\\\\\\\\\\\\\\\\
// Function to recursively list students from a specific city in lexicographic order
TNode ListStudentsByCity(TNode root, char city[100], TNode cityTree) {
    if (root == NULL) {
        return cityTree;
    }


    cityTree = ListStudentsByCity(root->Left, city, cityTree); // Traverse the left subtree

    if (strcmp(root->Address, city) == 0)  // Check by compare if the student's city matches the search city
 {
        // Create a new node for the student
        TNode newNode = (TNode)malloc(sizeof(struct Node));
        newNode->ID = root->ID;
        strcpy(newNode->Name, root->Name);
        strcpy(newNode->Address, root->Address);
        newNode->ClassID = root->ClassID;
        strcpy(newNode->DateOfEnrollment, root->DateOfEnrollment);
        newNode->Left = NULL;
        newNode->Right = NULL;


        cityTree = InsertStudentByName(cityTree, newNode);// Insert the student into the new tree based on their name so they will be sorted
    }

    cityTree = ListStudentsByCity(root->Right, city, cityTree); // now traverse the right subtree


    return cityTree;
}
//============================================= case 4 helping functions end ===================================================


//============================================= case 5 helping functions begin ===================================================
////////////////\\\\\\\\\\\\\\\
//
TNode InsertStudentByClass(TNode root, TNode newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (newNode->ClassID < root->ClassID) // go to left sub tree
    {
        root->Left = InsertStudentByClass(root->Left, newNode);
    } else if (newNode->ClassID > root->ClassID) // go to right sub tree
    {
        root->Right = InsertStudentByClass(root->Right, newNode);
    } else {
        // case were students with same ClassID -> insert the new node based on name to be sorted
        if (strcmp(newNode->Name, root->Name) <= 0) {
            root->Left = InsertStudentByClass(root->Left, newNode);
        } else {
            root->Right = InsertStudentByClass(root->Right, newNode);
        }
    }

    return root;
}

////////////////\\\\\\\\\\\\\\\
//
TNode listByClass2(TNode root, TNode newTree) {
    if (root == NULL) {
        return newTree;
    }

    newTree = listByClass2(root->Left, newTree);       //to copy the left subtree
    newTree = InsertStudentByClass(newTree, CreateNode(root->ID, root->Name, root->Address, root->ClassID, root->DateOfEnrollment)); // Insert node to the copy tree by name
    newTree = listByClass2(root->Right, newTree);      //to copy the right subtree

    return newTree;
}

///////////////\\\\\\\\\\\\\
//
TNode listByClass1(TNode root)
{
   TNode newTree = NULL;
    newTree = listByClass2(root, newTree);
    return newTree;

}

////////////////\\\\\\\\\\\\\\\
// Function to perform in-order traversal of the tree and print students (To Print for case 5 : Class Id)
void InOrderTraversal2(TNode root) {
    if (root != NULL) {
        InOrderTraversal2(root->Left); // print the left sub tree
        printf(" Class id: %d, Name: %s, Student ID: %d, address: %s,  date of enrollment: %s\n",   root->ClassID ,root->Name ,root->ID, root->Address , root->DateOfEnrollment);
        InOrderTraversal2(root->Right); // print the right sub tree
    }
}
//============================================= case 5 helping functions end ===================================================

///////////////\\\\\\\\\\\\\\\
// Function that delete a student information by giving the id
TNode Delete(int X,TNode T )
{
    TNode TmpCell;
    if( T == NULL )
        printf( "Element not found" );
    else if( X < T->ID ) // Go left
        T->Left = Delete( X, T->Left );
    else if( X > T->ID ) // Go right
        T->Right = Delete( X, T->Right );
    else // Found element to be deleted
        if( T->Left && T->Right )
            // Two children
        {
            // Replace with smallest in right subtree

            TmpCell=FindMin( T->Right );
            T->ID =TmpCell->ID;
            T->Right = Delete( T->ID, T->Right );
        }
        else // One or zero children
        {
            TmpCell= T;
            if( T->Left == NULL )
                //Also handles 0 children
                T= T->Right;
            else if( T->Right == NULL )
                T = T->Left;

            free(TmpCell);
        }
    return T;
} //end of Delete routine


///////////////\\\\\\\\\\\\\\\\
// Main function
int main() {
    TNode root = NULL;

    FILE* file = fopen("students.data", "r");// data in file
    if (file != NULL) {
        while (!feof(file)) {
            TNode newNode = (TNode)malloc(sizeof(struct Node));// newNode to store the student information when read from the file
            // read all data from the file
            if (fscanf(file, "Student ID: %d\nStudent Name: %[^\n]\nStudent Address: %[^\n]\nStudent Class ID: %d\nStudent Enrollment Date: %[^\n]\n\n",
                    &newNode->ID, newNode->Name, newNode->Address, &newNode->ClassID, newNode->DateOfEnrollment) == 5) {
                newNode->Left = NULL;
                newNode->Right = NULL;
                root = Insert(root, newNode);// insert students to the BST (root)
            } else {
                free(newNode);// free the current node to store the new student info from the file
            }
        }

        fclose(file);
        printf("File opened and student data loaded successfully!\n");
    } else {
        printf("Starting with an empty tree. The file is empty or could not be opened.\n");
    }

    int operation;
    do {
        printf("\n------ School Management System ------\n"); // program menu
        printf("--------------------------------------\n");
        printf("1- Insert a student\n");
        printf("2- Find a student by ID\n");
        printf("3- List all students\n");
        printf("4- Search for a city and list all students from it\n");
        printf("5- List all students by their class\n");
        printf("6- Delete a student ID\n");
        printf("7- Save all students in a file\n");
        printf("8- Exit\n\n");
        printf("-----Enter your choice: ");
        scanf("%d", &operation);

        if(operation == 1)  // op 1: insert a new student and save all informations
            {
                int id;
                int classID;
                char name[70], address[100], enrollmentDate[50];

                printf("~Enter student ID: ");
                scanf("%d", &id);

                TNode checkId=Find(root, id);
                if(checkId != NULL)
                {
                    printf(" Student with this id already exists!! \n        ~~Try again~~ \n");
                    continue;
                }

                printf("~Enter student name: ");
                scanf(" %[^\n]", name);

                printf("~Enter student address: ");
                scanf(" %[^\n]", address);

                printf("~Enter class ID: ");
                scanf("%d", &classID);

                printf("~Enter enrollment date: ");
                scanf(" %[^\n]", enrollmentDate);

                TNode newNode = CreateNode(id, name, address, classID, enrollmentDate);
                root = Insert(root, newNode);
                printf("!! Student inserted successfully !!\n");
            }
           else if(operation == 2)  // op 2: find a student by his/her id and display all informations if found
            {
                int id;
                int update=0;
                printf("Enter student ID to find: ");
                scanf("%d", &id);
                TNode foundStudent = Find(root, id);
                if (foundStudent != NULL) {
                    printf("!! Student found !!\n");
                    printf("~Student ID: %d\n", foundStudent->ID);
                    printf("~Student Name: %s\n", foundStudent->Name);
                    printf("~Student Address: %s\n", foundStudent->Address);
                    printf("~Student Class ID: %d\n", foundStudent->ClassID);
                    printf("~Student Enrollment Date: %s\n", foundStudent->DateOfEnrollment);
                    printf("\n Do you want to update this student information ??\n");
                    // offer to update
                    printf(" if YES enter '1'\n if NO enter  '0'\n");
                    scanf("%d",&update);
                if(update == 1)
                {
                    int classID;
                    char name[70], address[100], enrollmentDate[50];

                    printf("~Enter student new name: ");
                    scanf(" %[^\n]", name);

                    printf("~Enter student new address: ");
                    scanf(" %[^\n]", address);

                    printf("~Enter class new ID: ");
                    scanf("%d", &classID);

                    printf("~Enter the new enrollment date: ");
                    scanf(" %[^\n]", enrollmentDate);


                    root=UpdateStudent(root, id,  name,address,classID, enrollmentDate );
                    printf("!! Student information updated successfully !!\n");

                printf("~Student ID: %d\n", foundStudent->ID);
                printf("~Student Name: %s\n", foundStudent->Name);
                printf("~Student Address: %s\n", foundStudent->Address);
                printf("~Student Class ID: %d\n", foundStudent->ClassID);
                printf("~Student Enrollment Date: %s\n", foundStudent->DateOfEnrollment);
               }
            }
            else
            {
                    printf("\n!!!! Student not found !!!!\n");
                 }

            }
            else if(operation == 3)  // op 3: list all students with all informations by their names (in lexicographic order)
            {
                TNode TreeToprint = copyTree1(root);
                printf("List of students:\n");
                InOrderTraversal(TreeToprint);
            }
            else if (operation == 4) // op 4: Search for a city and list all students from that city (in lexicographic order of their names).
            {

                char city[100];
                printf("Enter the city name: \n");
                scanf(" %[^\n]", city);
                printf("Entered City: %s", city);

                TNode CityStudents= NULL; // new tree
                CityStudents = ListStudentsByCity(root, city, CityStudents);// call the function to get A tree with all student from the given city listed

                printf("List of students:\n");
                InOrderTraversal(CityStudents); // print the lest in lexicographic order of their names

            }
            else if (operation == 5)  // op 5: List all students by their class (in lexicographic order of their names).
            {
                TNode TreeToprint = listByClass1(root);
                InOrderTraversal2(TreeToprint);

            }
            else if (operation == 6)  // op 6: Delete a student given his/her student ID
            {
                printf("Enter the Id to delete informations: \n");// take the id to delete the student info with this id
                int studentId;
                scanf("%d",&studentId);
                Delete(studentId, root); // call delete function
            }
            else if (operation == 7)  // op 7: Save all students in file students.data
            {

                FILE* outputFile = fopen("students.data", "w");// Open the output file to write

                if (outputFile == NULL) // Check if the file has opened
                {
                    printf("Failed to open the file.\n");
                    return 1;
                }

                // Save the list of students to the file
                TNode tempNode = root; // a temp tree to print the root nodes in the output file
                while (tempNode != NULL) {
                    fprintf(outputFile, "Student ID: %d\n", tempNode->ID);
                    fprintf(outputFile, "Student Name: %s\n", tempNode->Name);
                    fprintf(outputFile, "Student Address: %s\n", tempNode->Address);
                    fprintf(outputFile, "Student Class ID: %d\n", tempNode->ClassID);
                    fprintf(outputFile, "Student Enrollment Date: %s\n", tempNode->DateOfEnrollment);
                    fprintf(outputFile, "\n");

                    if (tempNode->Left != NULL) {  // print the left sub tree
                        tempNode = tempNode->Left;
                    } else if (tempNode->Right != NULL) {  // print the right sub tree
                        tempNode = tempNode->Right;
                    } else {
                        break; // finish printing the tree
                    }
                }

                fclose(outputFile); // Close the output file

            }
            else if (operation == 8)  // op 8: list all students with all informations by their names (in lexicographic order)
                printf("Exiting the program. Goodbye!\n");

            else
                printf("Invalid choice. Please try again.\n");// if the chosen operation is not one of (1-8)

    } while (operation != 8);// Exit if the chosen operation were = 8


    return 0;
}
