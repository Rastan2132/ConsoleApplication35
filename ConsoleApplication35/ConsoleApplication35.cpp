#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main()
{
    setlocale(LC_ALL, "pl_PL");

    ifstream inputFile("input.txt");

    int setSize;
    inputFile >> setSize;

    set<pair<int, int>> relation;
    int x, y;
    while (inputFile >> x >> y) {
        relation.insert(make_pair(x, y));
    }

    // Проверить, является ли отношение отношением эквивалентности
    bool reflexive = true, symmetric = true, transitive = true;
    for (int i = 1; i <= setSize; i++) {
        if (!relation.count(make_pair(i, i))) {
            reflexive = false;
        }
        for (int j = i + 1; j <= setSize; j++) {
            if (relation.count(make_pair(i, j)) && !relation.count(make_pair(j, i))) {
                symmetric = false;
            }
            if (relation.count(make_pair(i, j))) {
                for (int k = 1; k <= setSize; k++) {
                    if (relation.count(make_pair(j, k)) && !relation.count(make_pair(i, k))) {
                        transitive = false;
                    }
                }
            }
        }
    }

    // Print 
    if (reflexive && symmetric && transitive) {
        cout << "Relacja jest relacją równoważności." << endl;
    }
    else {
        cout << "Relacja nie jest relacją równoważności." << endl;
        if (!reflexive) {
            cout << "Zamknięcie refleksyjne:";
            for (int i = 1; i <= setSize; i++) {
                if (!relation.count(make_pair(i, i))) {
                    cout << "(" << i << ", " << i << ") ";
                }
            }
            cout << endl;
        }
        if (!symmetric) {
            cout << "Zamknięcie symetryczne: ";
            for (auto p : relation) {
                if (p.first != p.second) {
                    cout << "(" << p.second << ", " << p.first << ") ";
                }
            }
            cout << endl;
        }
        if (!transitive) {
            cout << "Zamknięcie przechodnie: ";
            set<pair<int, int>> newRelation = relation;
            for (int i = 1; i <= setSize; i++) {
                for (auto p : newRelation) {
                    if (p.first == i) {
                        for (auto q : newRelation) {
                            if (p.second == q.first) {
                                newRelation.insert(make_pair(i, q.second));
                            }
                        }
                    }
                }
            }
            for (auto p : newRelation) {
                if (!relation.count(p)) {
                    cout << "(" << p.first << ", " << p.second << ") ";
                }
            }
            cout << endl;

         }
    }
        return 0;
}