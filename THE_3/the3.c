#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"
#define ALLOCATE(x) (x*) malloc(sizeof(x)) 
/*
INPUT:
    Node **meals_head: reference of the meal's linked list
    char *name: name of the meal
    int count: number of the meals

METHOD:
    Creates a meal and a node containing that meal. Append it to meal's linked list end.
*/
void add_meal(Node **meals_head, char *name, int count){
    Meal *mealptr;
    Node *current;
    mealptr = ALLOCATE(Meal);
    mealptr->name = name;
    mealptr->count = count;

    if(*meals_head == NULL) {

        *meals_head = ALLOCATE(Node);
        (*meals_head)->node = mealptr;
        (*meals_head)->next = NULL;
        /*printf("%p %p\n", mealptr, (*meals_head)->node);
        printf("%p \n", (*meals_head)->next);
        printf("%p %c %c %c\n",mealptr->name,*mealptr->name, (mealptr->name)[1], (mealptr->name)[2]);*/

    }
    else {
        for(current = *meals_head;current != NULL;current = current->next) {
            if(current->next == NULL) {
                current->next = ALLOCATE(Node);
                current->next->node = mealptr;
                current->next->next = NULL;
                /*printf("%p %p\n", mealptr, current->next->node);*/
                break;
                
            }
        }
    }
}

/*
INPUT:
    Node **philosophers_head: reference of the philosopher's linked list
    char *name: name of the philosopher
    char *favorite_meal: favorite meal
    int age: age of the philosopher

METHOD:
    Creates a philosopher and a node containing that philosopher. 
    Append it to philosopher's linked list end.
*/
void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age){
    Philosopher *philptr;
    Node *current;
    philptr = ALLOCATE(Philosopher);
    philptr->name = name;
    philptr->favorite_meal = favorite_meal;
    philptr->age = age;
    if(*philosophers_head == NULL) {
        *philosophers_head = ALLOCATE(Node);
        (*philosophers_head)->node = philptr;
        (*philosophers_head)->next = NULL;
        /*printf("\n%d\n",((Philosopher*)(*philosophers_head)->node)->age);*/
        /*printf("%p %p\n %p",philptr, (*philosophers_head)->node, *philosophers_head);*/
    }
    else {
        for(current = *philosophers_head;current != NULL;current = current->next) {
            if(current->next == NULL) {
                current->next = ALLOCATE(Node);
                current->next->node = philptr;
                current->next->next = NULL;
                /*printf("\n%d\n",((Philosopher*)(current)->next->node)->age);*/
                /*printf("%p %p\n", current->next, current->next->node);*/
                break;
            }
        }
    }

}
    
/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    Node *philosophers: philosopher's linked list

METHOD:
    Places philosophers into a circular linked list in ascending order of ages.
*/
void place_philosophers(Node **table_head, Node *philosophers){
    Node *current_philosopher;
    Node *current_table;
    Node *temp;
    for(current_philosopher = philosophers;current_philosopher!=NULL;current_philosopher=current_philosopher->next) {
        if (*table_head == NULL) {
            *table_head = ALLOCATE(Node);
            (*table_head)->node = current_philosopher->node;
            (*table_head)->next = NULL;
        }
        else {
            for(current_table = *table_head;current_table!=NULL;current_table=current_table->next) {
                if (current_table->next==NULL && current_table==*table_head) {
                    if(((Philosopher*)current_table->node)->age < ((Philosopher*)current_philosopher->node)->age) {
                        current_table->next = ALLOCATE(Node);
                        current_table->next->node = current_philosopher->node;
                        current_table->next->next = NULL;
                        break;

                    }
                    else if (((Philosopher*)current_table->node)->age > ((Philosopher*)current_philosopher->node)->age) {
                        *table_head = ALLOCATE(Node);
                        (*table_head)->node = current_philosopher->node;
                        (*table_head)->next = current_table;
                        (*table_head)->next->next = NULL;
                        break;

                    }
                }
                else if (current_table->next==NULL && current_table!=*table_head) {
                    if(((Philosopher*)current_table->node)->age < ((Philosopher*)current_philosopher->node)->age) {
                        current_table->next = ALLOCATE(Node);
                        current_table->next->node = current_philosopher->node;
                        current_table->next->next = NULL;
                        break;
                    }

                }
                else if(current_table->next != NULL && current_table == *table_head) {
                    if(((Philosopher*)current_table->node)->age > ((Philosopher*)current_philosopher->node)->age) {
                        *table_head = ALLOCATE(Node);
                        (*table_head)->node = current_philosopher->node;
                        (*table_head)->next = current_table;
                        break;
                    }

                }
                if (((Philosopher*)current_table->next->node)->age > ((Philosopher*)current_philosopher->node)->age) {
                    temp = current_table->next;
                    current_table->next = ALLOCATE(Node);
                    current_table->next->node = current_philosopher->node;
                    current_table->next->next = temp;
                    break;
                }
                
            }
        }
        ((Philosopher*)current_philosopher->node)->sitting = 1;
    }
    for(current_table = *table_head;current_table!=NULL;current_table=current_table->next) {
        if(current_table->next==NULL) {
            current_table->next = *table_head;
            break;    
        }
    }
}
    
/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    int index: index of the philosopher to be removed
    int size_of_table: number of philosophers in the table

METHOD:
    Removes a philosopher from table.
*/
void remove_philosopher(Node **table_head, int index, int size_of_table){
    int i=0;
    Node *temp;
    Node *current;
    /*printf("\nTHIS IS A REMOVE CALL\n");*/
    for(current=*table_head;current!=NULL;current=current->next) {
        i+= 1;
        if(index==i || index==i-size_of_table) {
            ((Philosopher*)current->next->node)->sitting = 0;
            temp = current->next->next;
            current->next = temp;
            if(index==i-size_of_table) {
                (*table_head)=temp;
            }
            break;
        }
    }
}
    
/*
INPUT:
    Node *table: Circular linked list
    Node *meals: Meal's linked list

METHOD:
    Serves favorite meals and reduce their counts. Use strcmp function from string.h
*/
void serve_meals(Node *table, Node *meals){
    int i=0;
    Node* current_phil;
    Node* current_meal;
    /*printf("SERVE MEALS RESULTS:");*/
    for(current_phil=table;current_phil!=NULL;current_phil=current_phil->next) {
        i += 1;
        if(i>1 && current_phil==table) {
            break;
        }
        for(current_meal=meals;current_meal!=NULL;current_meal=current_meal->next) {
            if(!strcmp(((Philosopher*)current_phil->node)->favorite_meal,((Meal*)current_meal->node)->name)) {
                ((Meal*)current_meal->node)->count -= 1;
            }
        }
    }
    /*for(current_meal=meals;current_meal!=NULL;current_meal=current_meal->next) {
        printf("\n%d ",((Meal*)current_meal->node)->count);
    }*/
}
/*
INPUT:
    Node *list: A linked list
    void (*helper_print)(void *): Reference of a helper print function

METHOD:
    Prints items in the linked list using helper print function
*/
void print_list(Node *list, void (*helper_print)(void *)){
    Node *current;
    for(current=list;current!=NULL;current=current->next)
        (*helper_print)(current->node);
}

/*
INPUT:
    void *meal: void meal pointer

METHOD:
    Cast void pointer to a meal pointer and prints it's content
*/
void print_meal_node(void *meal){
    printf("Name: %s, count: %d\n",((Meal*)meal)->name, ((Meal*)meal)->count);
}

/*
INPUT:
    void *philosopher: void philosopher pointer

METHOD:
    Cast void pointer to a philosopher pointer and prints it's content
*/
void print_philosopher_node(void *philosopher){
    printf("Name: %s, favorite meal: %s, age: %d\n", ((Philosopher*)philosopher)->name, ((Philosopher*)philosopher)->favorite_meal, ((Philosopher*)philosopher)->age);
}

/*
INPUT:
    Node *table: Circular linked list

METHOD:
    Prints the formation as <prev> <current> <next>
*/
void print_table(Node *table){
    Node *first;
    for(first = table;first != NULL; first=first->next) {
        if(first->next==table) {
            while(first) {
                printf("%s -> %s -> %s\n", ((Philosopher*)first->node)->name, 
                    ((Philosopher*)first->next->node)->name, 
                    ((Philosopher*)first->next->next->node)->name);
                if(first->next->next==table) {
                    break;
                }
                first=first->next;
            }
            break;
        }
    }
}

/*
INPUT:
    Node *list: A linked list

OUTPUT:
    Size of the linked list in an integer format

METHOD:
    Calculates the size of the linked list and returns it.
*/
int get_length(Node *list){
    Node *current;
    int length=0;
    for(current=list;;current=current->next) {
        if(length>1 && current==list) {
            return length;
        }
        else if(current==NULL) {
            return length;
        }
        else {
            length++;
        }
    }
}

/*
INPUT:
    Node *philosophers: Philosopher's linked list

OUTPUT:
    Philosopher pointer at given index.

METHOD:
    Finds the philosopher at given index and returns it's reference.
*/
Philosopher *get_philosopher(Node *philosophers, int index){
    Node *current;
    int current_index=-1;
    for(current=philosophers;current!=NULL;current=current->next) {
        current_index+=1;
        if(index==current_index) {
            return ((Philosopher*)current->node);
        }
    }
    return NULL;
}
