#include <iostream>
#include <cctype>
using namespace std;

enum Error_code { success, overflow, underflow };
typedef double Stack_entry;
const int maxstack = 10;

class Stack {
public:
    Stack() { count = 0; }
    bool empty() const { return count == 0; }

    Error_code push(const Stack_entry &item) {
        if (count >= maxstack) return overflow;
        entry[count++] = item;
        return success;
    }

    Error_code pop() {
        if (count == 0) return underflow;
        --count;
        return success;
    }

    Error_code top(Stack_entry &item) const {
        if (count == 0) return underflow;
        item = entry[count - 1];
        return success;
    }

private:
    int count;
    Stack_entry entry[maxstack];
};

void introduction() {
    cout << "Postfix Calculator" << endl;
}

void instructions() {
    cout << "[?] push number  [=] print top  [+][-][*][/] arithmetic [x]exchange  [Q]uit" << endl;
}

char get_command() {
    char command;
    bool waiting = true;
    cout << "Select command and press <Enter>: ";
    while (waiting) {
        cin >> command;
        command = tolower(command);
        if (command == '?' || command == '=' || command == '+' ||
            command == '-' || command == '*' || command == '/' ||
            command == 'q' || command == 'x') //x for exchange
            waiting = false;
        else {
            cout << "Invalid command. [?]=push [=]print top [+][-][*][/] [Q]uit: ";
        }
    }
    return command;
}

bool do_command(char command, Stack &numbers) {
    double p, q;
    switch (command) {
    case '?':
        cout << "Enter a real number: ";
        cin >> p;
        if (numbers.push(p) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
        break;
    case '=':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
            cout << p << endl;
        break;
    case '+':
        if (numbers.top(p) == underflow) { cout << "Stack empty" << endl; break; }
        numbers.pop();
        if (numbers.top(q) == underflow) { cout << "Stack has just one entry" << endl; numbers.push(p); break; }
        numbers.pop();
        if (numbers.push(q + p) == overflow) cout << "Warning: Stack full, lost result" << endl;
        break;
    case '-':
        if (numbers.top(p) == underflow) { cout << "Stack empty" << endl; break; }
        numbers.pop();
        if (numbers.top(q) == underflow) { cout << "Stack has just one entry" << endl; numbers.push(p); break; }
        numbers.pop();
        if (numbers.push(q - p) == overflow) cout << "Warning: Stack full, lost result" << endl;
        break;
    case '*':
        if (numbers.top(p) == underflow) { cout << "Stack empty" << endl; break; }
        numbers.pop();
        if (numbers.top(q) == underflow) { cout << "Stack has just one entry" << endl; numbers.push(p); break; }
        numbers.pop();
        if (numbers.push(q * p) == overflow) cout << "Warning: Stack full, lost result" << endl;
        break;
    case '/':
        if (numbers.top(p) == underflow) { cout << "Stack empty" << endl; break; }
        numbers.pop();
        if (numbers.top(q) == underflow) { cout << "Stack has just one entry" << endl; numbers.push(p); break; }
        numbers.pop();
        if (p == 0) { cout << "Division by zero" << endl; numbers.push(q); break; }
        if (numbers.push(q / p) == overflow) cout << "Warning: Stack full, lost result" << endl;
        break;
        //second increment, added exchange
    case 'x':
        //we pop the two numbers on top of the stack
        if (numbers.top(p) == underflow){cout << "Stack empty" << endl; break; }
        numbers.pop();
        if (numbers.top(q) == underflow){cout << "Stack has just one entry" << endl; break;}
        numbers.pop();
        //we reorder them by pushing them back in a different order
        if (numbers.push(p) == overflow){cout << "Stack is full" << endl; break;}
        if (numbers.push(q) == overflow){cout << "Stack is full" << endl; break;}
        break;
        
    case 'q':
        cout << "Calculation finished." << endl;
        return false;
    }
    return true;
}

int main() {
    Stack stored_numbers;
    introduction();
    instructions();
    while (do_command(get_command(), stored_numbers));
    return 0;
}