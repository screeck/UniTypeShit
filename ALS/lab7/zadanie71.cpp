#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Struktura węzła AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Funkcja pomocnicza - wysokość węzła
int height(Node* node) {
    return node ? node->height : 0;
}

// Oblicz balans węzła
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Tworzenie nowego węzła
Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// Rotacja w prawo
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotacja w lewo
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Wstawianie węzła
Node* insert(Node* node, int key) {
    if (!node)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Rotacje
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Znajdź minimalną wartość w prawym poddrzewie
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Usuwanie węzła
Node* deleteNode(Node* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Przejścia drzewa
void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

// Funkcja rysowania drzewa
void narysuj(string sp, string sn, Node* korzen) {
    string temp;
    string cr = "  ";
    string cl = "  ";
    string cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;

    if (korzen) {
        temp = sp;
        if (sn == cr) {
            temp[temp.length() - 2] = ' ';
        }

        narysuj(temp + cp, cr, korzen->right);

        temp = temp.substr(0, sp.length() - 2);
        cout << temp << sn << korzen->key << ":" << getBalance(korzen) << endl;

        temp = sp;
        if (sn == cl) {
            temp[temp.length() - 2] = ' ';
        }

        narysuj(temp + cp, cl, korzen->left);
    }
}

// Wczytywanie danych z pliku
void loadFromFile(Node*& root, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            root = insert(root, value);
        }
        file.close();
    }
    else {
        cout << "Nie można otworzyć pliku!\n";
    }
}

// Menu programu
void menu() {
    Node* root = nullptr;
    int choice, value;
    string filename;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Dodaj węzeł\n";
        cout << "2. Usuń węzeł\n";
        cout << "3. Wyświetl drzewo\n";
        cout << "4. Przejścia drzewa (in-order, pre-order, post-order)\n";
        cout << "5. Wczytaj dane z pliku\n";
        cout << "6. Wyjście\n";
        cout << "Twój wybór: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Podaj wartość do dodania: ";
            cin >> value;
            root = insert(root, value);
            break;
        case 2:
            cout << "Podaj wartość do usunięcia: ";
            cin >> value;
            root = deleteNode(root, value);
            break;
        case 3:
            cout << "Drzewo AVL:\n";
            narysuj("", "", root);
            break;
        case 4:
            cout << "In-order: ";
            inOrder(root);
            cout << "\nPre-order: ";
            preOrder(root);
            cout << "\nPost-order: ";
            postOrder(root);
            cout << endl;
            break;
        case 5:
            cout << "Podaj nazwę pliku: ";
            cin >> filename;
            loadFromFile(root, filename);
            break;
        case 6:
            return;
        default:
            cout << "Nieprawidłowy wybór!\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
