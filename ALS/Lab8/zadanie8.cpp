#include <iostream>
#include <fstream>

using namespace std;

const int T = 4; // stopień drzewa

struct BTreeNode {
    int* keys;
    BTreeNode** children;
    int n;
    bool isLeaf;
};

BTreeNode* createNode(bool isLeaf) {
    BTreeNode* node = new BTreeNode;
    node->keys = new int[T - 1];
    node->children = new BTreeNode * [T];
    node->n = 0;
    node->isLeaf = isLeaf;
    return node;
}

void traverse(BTreeNode* node) {
    if (!node) return;

    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->isLeaf) {
            traverse(node->children[i]);
        }
        cout << node->keys[i] << " ";
    }
    if (!node->isLeaf) {
        traverse(node->children[i]);
    }
}

void drawTree(BTreeNode* node, int level = 0) {
    if (!node) return;

    // Wypisz klucze węzła na bieżącym poziomie
    for (int i = 0; i < level; i++) {
        cout << "  "; // Indentacja dla poziomów
    }
    cout << "{ ";
    for (int i = 0; i < node->n; i++) {
        cout << node->keys[i] << " ";
    }
    cout << "}" << endl;

    // Rekurencyjnie wywołaj dla dzieci
    if (!node->isLeaf) {
        for (int i = 0; i <= node->n; i++) {
            drawTree(node->children[i], level + 1);
        }
    }
}

BTreeNode* search(BTreeNode* node, int key) {
    if (!node) return nullptr;

    int i = 0;
    while (i < node->n && key > node->keys[i]) {
        i++;
    }

    if (i < node->n && node->keys[i] == key) {
        return node;
    }

    if (node->isLeaf) {
        return nullptr;
    }

    return search(node->children[i], key);
}

void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    int median = (T - 1) / 2;
    BTreeNode* newChild = createNode(child->isLeaf);

    for (int j = 0; j < median; j++) {
        newChild->keys[j] = child->keys[j + median + 1];
    }

    if (!child->isLeaf) {
        for (int j = 0; j <= median; j++) {
            newChild->children[j] = child->children[j + median + 1];
        }
    }

    newChild->n = median;
    child->n = median;

    for (int j = parent->n; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = child->keys[median];

    parent->n++;
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    }
    else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->n == T - 1) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(BTreeNode*& root, int key) {
    if (!root) {
        root = createNode(true);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    if (root->n == T - 1) {
        BTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;

        splitChild(newRoot, 0, root);

        int i = (key > newRoot->keys[0]) ? 1 : 0;
        insertNonFull(newRoot->children[i], key);

        root = newRoot;
    }
    else {
        insertNonFull(root, key);
    }
}

void deleteTree(BTreeNode* node) {
    if (!node) return;

    if (!node->isLeaf) {
        for (int i = 0; i <= node->n; i++) {
            deleteTree(node->children[i]);
        }
    }

    delete[] node->keys;
    delete[] node->children;
    delete node;
}

int main() {
    BTreeNode* root = nullptr;
    int choice, key;
    string fileName;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Dodaj węzeł\n";
        cout << "2. Szukaj węzła\n";
        cout << "3. Wyświetl drzewo (in-order)\n";
        cout << "4. Wyświetl strukturę drzewa\n";
        cout << "5. Usuń całe drzewo\n";
        cout << "6. Wczytaj dane z pliku\n";
        cout << "7. Wyjście\n";
        cout << "Twój wybór: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Podaj wartość do dodania: ";
            cin >> key;
            insert(root, key);
            break;
        case 2:
            cout << "Podaj wartość do wyszukania: ";
            cin >> key;
            if (search(root, key)) {
                cout << "Wartość znaleziona." << endl;
            }
            else {
                cout << "Wartość nieznaleziona." << endl;
            }
            break;
        case 3:
            cout << "Drzewo in-order: ";
            traverse(root);
            cout << endl;
            break;
        case 4:
            cout << "Struktura drzewa: " << endl;
            drawTree(root);
            break;
        case 5:
            deleteTree(root);
            root = nullptr;
            cout << "Drzewo usunięte." << endl;
            break;
        case 6:
            cout << "Podaj nazwę pliku: ";
            cin >> fileName;
            {
                ifstream file(fileName);
                if (file.is_open()) {
                    while (file >> key) {
                        insert(root, key);
                    }
                    file.close();
                    cout << "Dane załadowane." << endl;
                }
                else {
                    cout << "Nie można otworzyć pliku." << endl;
                }
            }
            break;
        case 7:
            deleteTree(root);
            return 0;
        default:
            cout << "Nieprawidłowa opcja." << endl;
        }
    }
}
