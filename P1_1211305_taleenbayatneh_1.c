//Taleen Bayatneh-1211305-section:1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lineLength 200
#define MaxLength 50

//////////////////////////
//structure definitions

struct node {
    int coff;
    int exp;
    struct node* next;
};
typedef struct node* Node;
typedef Node List;
////
struct _node {
    List equation;
    struct _node* next;
};
typedef struct _node* ptrToNode;
typedef ptrToNode Stack;

//////////////////////////
//function declarations
//List
List CreateList();
int IsEmpty(List L);
void Insert(List L, int exp, int coff);
void PrintList(List L);
void DeleteNode(List L, int exp, int coff);
void DeleteList(List L);
Node SearchNode(List L, int exp);
//Stack
Stack CreateStack();
void Push(Stack Top, List L);
void Pop(Stack Top);
int isEmpty(Stack Top);
void MakeEmpty(Stack Top);
List Top(Stack Top);
void DisposeStack(Stack Top);
void Printlist(Stack S);

List Load(char* line);
List sumofequations(Stack listofequations);
List subofequations(Stack listofequations);
List multiofequations(Stack listofequations);
Stack CopyStack(Stack original);//a function to copy the stack

int main() {
    int c;
    char line[lineLength];
    List equation = CreateList();
    List sum_list = CreateList();
    List sub_list = CreateList();
    List multi_list = CreateList();
    List p = CreateList();
    Stack listOfequations = CreateStack();
    Stack resultstack = CreateStack();
    Stack resu_s = CreateStack();

    do {
        printf("\nChoose one of the following:\n");
        printf("1. Load the polynomials file\n");
        printf("2. Print the polynomials\n");
        printf("3. Add the polynomials\n");
        printf("4. Subtract the polynomials\n");
        printf("5. Multiply the polynomials\n");
        printf("6. Print the results to the screen\n");
        printf("7. Print the results to file\n");
        printf("8. Exit\n");
        scanf("%d", &c);

        FILE* input_file;
        FILE* output_file;

        switch (c) {
            case 1: //load equations from file
                input_file = fopen("input.txt", "r");
                if (input_file == NULL) {
                    printf("Error opening file\n");
                    break;
                }
                while (fgets(line, lineLength, input_file) != NULL) {
                    equation = Load(line);
                    Push(listOfequations, equation);
                }
                fclose(input_file);
                break;

            case 2: //print equations from the stack
                Printlist(listOfequations);
                break;

            case 3: //addition of all equations
                sum_list = sumofequations(listOfequations);
                Push(resultstack, sum_list);
                PrintList(sum_list);
                break;

            case 4: //subtraction of all equations
                sub_list = subofequations(listOfequations);
                Push(resultstack, sub_list);
                PrintList(sub_list);
                break;

            case 5: //multiplication of all equations
                multi_list = multiofequations(listOfequations);
                Push(resultstack, multi_list);
                PrintList(multi_list);
                break;

            case 6: //print all results
                Printlist(resultstack);
                break;

            case 7: //print the results to the output file
                output_file = fopen("output.txt", "w");
                if (output_file == NULL) {
                    printf("Error opening file\n");
                    break;
                }
                resu_s = resultstack;
                while (!isEmpty(resu_s)) {
                    p = Top(resu_s);
                    Node temp = p->next;
                    while (temp != NULL) {
                        fprintf(output_file, "%dx^%d ", temp->coff, temp->exp);
                        if (temp->next != NULL) fprintf(output_file, "+ ");
                        temp = temp->next;
                    }
                    fprintf(output_file, "\n");
                    Pop(resu_s);
                }
                fclose(output_file);
                break;

            case 8: //exit
                exit(0);
                break;

            default:
                printf("Invalid choice, please enter a number from 1 to 8.\n");
        }
    } while (c != 8);

    //free memory
    DisposeStack(listOfequations);
    DisposeStack(resultstack);
    DisposeStack(resu_s);
    DeleteList(equation);
    DeleteList(sum_list);
    DeleteList(sub_list);
    DeleteList(multi_list);
    DeleteList(p);

    return 0;
}
//////////////////////////////
//create an empty list
List CreateList() {
    List L = (List)malloc(sizeof(struct node));
    if (L == NULL) {
        printf("Memory allocation failed for list\n");
        return NULL;
    }
    L->next = NULL;
    return L;
}
//////////////////////////////
//check if the list is empty
int IsEmpty(List L) {
    return (L->next == NULL);
}
//////////////////////////////
//insert a term into the list
void Insert(List L, int exp, int coff) {
    Node newNode = (Node)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Out of memory!\n");
        return;
    }
    newNode->exp = exp;
    newNode->coff = coff;
    newNode->next = NULL;

    if (IsEmpty(L)) {
        L->next = newNode;
    } else {
        Node temp = L->next;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
//////////////////////////////
//print the list
void PrintList(List L) {
    if (L == NULL) {
        printf("Linked list not found\n");
        return;
    }
    if (IsEmpty(L)) {
        printf("Linked list is empty\n");
        return;
    }

    Node temp = L->next;
    while (temp != NULL) {
        printf("%dx^%d", temp->coff, temp->exp);
        if (temp->next != NULL) printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}
//////////////////////////////
//delete a term from the list
void DeleteNode(List L, int exp, int coff) {
    if (L == NULL || IsEmpty(L)) return;

    Node temp = L;
    while (temp->next != NULL) {
        if (temp->next->exp == exp && temp->next->coff == coff) {
            Node toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete);
            return;
        }
        temp = temp->next;
    }
}
//////////////////////////////
//delete the list
void DeleteList(List L) {
    if (L == NULL) return;

    Node temp = L->next;
    while (temp != NULL) {
        Node toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    free(L);
}
//////////////////////////////
//search for a term in the list
Node SearchNode(List L, int exp) {
    if (L == NULL || IsEmpty(L)) return NULL;

    Node temp = L->next;
    while (temp != NULL) {
        if (temp->exp == exp) return temp;
        temp = temp->next;
    }
    return NULL;
}
//////////////////////////////
//create an empty stack
Stack CreateStack() {
    Stack S = (Stack)malloc(sizeof(struct _node));
    if (S == NULL) {
        printf("Out of memory!\n");
        return NULL;
    }
    S->next = NULL;
    return S;
}
//////////////////////////////
//push a polynomial onto the stack
void Push(Stack Top, List L) {
    ptrToNode newNode = (ptrToNode)malloc(sizeof(struct _node));
    if (newNode == NULL) {
        printf("Out of memory!\n");
        return;
    }
    newNode->equation = L;
    newNode->next = Top->next;
    Top->next = newNode;
}
//////////////////////////////
//pop a polynomial from the stack
void Pop(Stack Top) {
    if (Top == NULL || isEmpty(Top)) return;

    ptrToNode toDelete = Top->next;
    Top->next = toDelete->next;
    free(toDelete);
}
//////////////////////////////
//Check if the stack is empty
int isEmpty(Stack Top) {
    return (Top->next == NULL);
}
//////////////////////////////
//make the stack empty
void MakeEmpty(Stack Top) {
    while (!isEmpty(Top)) {
        Pop(Top);
    }
}
//////////////////////////////
//get the top of the stack
List Top(Stack Top) {
    if (Top == NULL || isEmpty(Top)) return NULL;
    return Top->next->equation;
}
//////////////////////////////
//dispose of the stack
void DisposeStack(Stack Top) {
    MakeEmpty(Top);
    free(Top);
}
//////////////////////////////
//print the stack
void Printlist(Stack S) {
    if (S == NULL || isEmpty(S)) {
        printf("Stack is empty\n");
        return;
    }

    ptrToNode temp = S->next;
    while (temp != NULL) {
        PrintList(temp->equation);
        temp = temp->next;
    }
}
//////////////////////////////
//load a polynomial from a line of text
List Load(char* line) {
    List L = CreateList();
    int size_line = (int)strlen(line);

    // Replace '-' with '+-' for easier parsing
    for (int i = 0; i < size_line - 1; i++) {
        if (line[i] == '-') {
            for (int j = size_line - 1; j >= i; j--) {
                line[j + 1] = line[j];
            }
            line[i] = '+';
            size_line++;
            line[size_line] = '\0';
            i++;
        }
    }

    // Parse terms separated by '+'
    char* term = strtok(line, "+");
    while (term != NULL) {
        char co[MaxLength] = "";
        char ex[MaxLength] = "";
        int k = 0;

        while (term[k] != 'x' && term[k] != '\0') {
            co[k] = term[k];
            k++;
        }

        if (term[k] == 'x') {
            int t = 0;
            for (int m = k + 2; term[m] != '\0'; m++) {
                ex[t] = term[m];
                t++;
            }
        }

        Insert(L, atoi(ex), atoi(co));
        term = strtok(NULL, "+");
    }

    return L;
}
//////////////////////////////
//add all polynomials in the stack
List sumofequations(Stack listofequations) {
    if (listofequations == NULL || isEmpty(listofequations)) return NULL;

    List result = CreateList();
    Stack tempStack = CopyStack(listofequations);

    while (!isEmpty(tempStack)) {
        List currentEquation = Top(tempStack);
        Pop(tempStack);

        Node term = currentEquation->next;
        while (term != NULL) {
            Node existing = SearchNode(result, term->exp);
            if (existing) {
                existing->coff += term->coff;
            } else {
                Insert(result, term->exp, term->coff);
            }
            term = term->next;
        }
    }

    DisposeStack(tempStack);
    return result;
}
//////////////////////////////
//subtract all polynomials in the stack
List subofequations(Stack list_equations) {
    if (list_equations == NULL || isEmpty(list_equations)) return NULL;

    List result = CreateList();
    Stack tempStack = CopyStack(list_equations);

    List firstEquation = Top(tempStack);
    Pop(tempStack);

    Node term = firstEquation->next;
    while (term != NULL) {
        Insert(result, term->exp, term->coff);
        term = term->next;
    }

    while (!isEmpty(tempStack)) {
        List currentEquation = Top(tempStack);
        Pop(tempStack);

        term = currentEquation->next;
        while (term != NULL) {
            Node existing = SearchNode(result, term->exp);
            if (existing) {
                existing->coff -= term->coff;
            } else {
                Insert(result, term->exp, -term->coff);
            }
            term = term->next;
        }
    }

    DisposeStack(tempStack);
    return result;
}
//////////////////////////////
//multiply all polynomials in the stack
List multiofequations(Stack lofequations) {
    if (lofequations == NULL || isEmpty(lofequations)) return NULL;

    List result = CreateList();
    Stack tempStack = CopyStack(lofequations);

    List firstEquation = Top(tempStack);
    Pop(tempStack);

    Node term1 = firstEquation->next;
    while (term1 != NULL) {
        Insert(result, term1->exp, term1->coff);
        term1 = term1->next;
    }

    while (!isEmpty(tempStack)) {
        List currentEquation = Top(tempStack);
        Pop(tempStack);

        List tempResult = CreateList();
        term1 = result->next;

        while (term1 != NULL) {
            Node term2 = currentEquation->next;
            while (term2 != NULL) {
                int newExp = term1->exp + term2->exp;
                int newCoff = term1->coff * term2->coff;

                Node existing = SearchNode(tempResult, newExp);
                if (existing) {
                    existing->coff += newCoff;
                } else {
                    Insert(tempResult, newExp, newCoff);
                }
                term2 = term2->next;
            }
            term1 = term1->next;
        }

        result = tempResult;
    }

    DisposeStack(tempStack);
    return result;
}
//////////////////////////////
//copy the stack
Stack CopyStack(Stack original) {
    if (original == NULL) return NULL;

    Stack copy = CreateStack();
    ptrToNode temp = original->next;

    while (temp != NULL) {
        Push(copy, temp->equation);
        temp = temp->next;
    }

    return copy;
}
//////////////////////////////
