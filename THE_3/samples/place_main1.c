#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"


int main(int argc, char const *argv[])
{
    Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;

    add_meal(&meals, "Kung Pao", 5);

    add_philosopher(&philosophers, "Lao Tzu", "Kung Pao", 1424);
    add_philosopher(&philosophers, "Confucius", "Kung Pao", 1145);
    add_philosopher(&philosophers, "Mozi", "Kung Pao", 1976);
    add_philosopher(&philosophers, "Zhuang Zhou", "Kung Pao", 1001);
    add_philosopher(&philosophers, "Sun Tzu", "Kung Pao", 123);

    place_philosophers(&table, philosophers);
    print_table(table);

    return 0;
}
