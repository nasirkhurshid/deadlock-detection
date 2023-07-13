#include <iostream>
using namespace std;

int main() {
    int nop, nor;
    do {
        cout << "Enter number of processes (not > 6): ";
        cin >> nop;
    } while (nop > 6);
    
    cout << "Enter number of resources: ";
    cin >> nor;
    int* resources = new int[nor];
    cout << "Enter number of instances for each resource: \n";
    for (int i = 0; i < nor; i++) {
        cin >> resources[i];
    }

    //allocation matrix
    int** allocation = new int*[nop];
    for (int i = 0; i < nop; i++) {
        allocation[i] = new int[nor];
    }
    for (int i = 0; i < nop; i++) {
        cout << "Enter instances of resources allocated to Process " << i + 1 << ": \n";
        for (int j = 0; j < nor; j++) {
            cin >> allocation[i][j];
        }
    }
    
    //max matrix
    int** max = new int* [nop];
    for (int i = 0; i < nop; i++) {
        max[i] = new int[nor];
    }
    for (int i = 0; i < nop; i++) {
        cout << "Enter maximum instances of resources needed by Process " << i + 1 << ": \n";
        for (int j = 0; j < nor; j++) {
            cin >> max[i][j];
        }
    }
    
    //displaying allocation matrix
    cout << "\nAllocation:\n\t";
    for (int i = 0; i < nor; i++) {
        cout << "R" << i + 1 << "\t";
    }
    cout << endl;
    for (int i = 0; i < nop; i++) {
        cout << "P" << i + 1 << "\t";
        for (int j = 0; j < nor; j++) {
            cout << allocation[i][j] << "\t";
        }
        cout << endl;
    }

    //displayin max matrix
    cout << "\nMax:\n\t";
    for (int i = 0; i < nor; i++) {
        cout << "R" << i + 1 << "\t";
    }
    cout << endl;
    for (int i = 0; i < nop; i++) {
        cout << "P" << i + 1 << "\t";
        for (int j = 0; j < nor; j++) {
            cout << max[i][j] << "\t";
        }
        cout << endl;
    }

    //calculating and displaying avaiable matrix
    int* available = new int[nor];
    for (int i = 0; i < nor; i++) {
        int a = 0;
        for (int j = 0; j < nop; j++) {
            a = a + allocation[j][i];
        }
        available[i] = resources[i] - a;
    }
    cout << "\nAvailable:\n";
    for (int i = 0; i < nor; i++) {
        cout << "R" << i + 1 << "\t";
    }
    cout << endl;
    for (int i = 0; i < nor; i++) {
        cout << available[i] << "\t";
    }
    cout << endl;
    
    //calculating and displaying need matrix
    int** need = new int* [nop];
    for (int i = 0; i < nop; i++) {
        need[i] = new int[nor];
    }
    for (int i = 0; i < nop; i++) {
        for (int j = 0; j < nor; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    cout << "\nNeed:\n\t";
    for (int i = 0; i < nor; i++) {
        cout << "R" << i + 1 << "\t";
    }
    cout << endl;
    for (int i = 0; i < nop; i++) {
        cout << "P" << i + 1 << "\t";
        for (int j = 0; j < nor; j++) {
            cout << need[i][j] << "\t";
        }
        cout << endl;
    }
    
    //running safety algorithm on given data
    int *finish = new int[nop];
    for (int i = 0; i < nop; i++) {
        finish[i] = 0;
    }
    int *sequence = new int[nop];        //array for storing the sequence of executed processes
    int index = 0;
    for (int n = 0; n < nop; n++) {
        for (int i = 0; i < nop; i++) {
            if (finish[i] == 0) {
                bool isless = 1;
                for (int j = 0; j < nor; j++) {       //checking if work/available < need
                    if (need[i][j] > available[j]) {
                        isless = 0;
                        break;
                    }
                }
                if (isless) {       //if yes then returning resources
                    for (int k = 0; k < nor; k++) {
                        available[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    sequence[index] = i;
                    index++;
                }
            }
        }
        if (index == nop) {       //checking if all processes have been executed
            break;
        }
    }

    bool safe = 1;  //considering that system is in safe state
    for (int i = 0; i < nop; i++) {
        if (finish[i] == 0) {       //checking if system is safe or not
            safe = 0;
            break;
        }
    }

    if (safe) {
        cout << "\nSystem is in safe state and following sequence satisfies safety criteria:\n<";
        for (int i = 0; i < index; i++) {
            cout << "P" << sequence[i];
            if (i != index - 1) {
                cout << ", ";
            }
        }
        cout << ">\n";
    }
    else {
        cout << "\nSystem is not in safe state!\n";
    }
    return 0;
}
