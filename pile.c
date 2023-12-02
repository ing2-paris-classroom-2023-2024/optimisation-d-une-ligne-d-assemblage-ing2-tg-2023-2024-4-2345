
Pile* creerPile(int capacite) {
    Pile* pile = (Pile*)malloc(sizeof(Pile));
    pile->capacite = capacite;
    pile->top = -1;
    pile->items = (int*)malloc(sizeof(int) * capacite);
    return pile;
}

bool estPileVide(Pile* pile) {
    return pile->top == -1;
}

void empiler(Pile* pile, int item) {
    pile->items[++pile->top] = item;
}

int depiler(Pile* pile) {
    if (!estPileVide(pile)) {
        return pile->items[pile->top--];
    }
    return -1;
}
int sommetEnHaut(Pile* pile) {
    if (!estPileVide(pile)) {
        return pile->items[pile->top];
    }
    return -1;
}
void afficherPile(Pile* pile) {
    for (int i = 0; i <= pile->top; i++) {
        printf("%d ", pile->items[i] + 1);
    }
    printf("\n");
}
