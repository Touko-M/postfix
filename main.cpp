#include <iostream>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
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
    cout << "[?] push number  [=] print top  [+][-][*][/] arithmetic [x]exchange [s]sum [a]average [Q]uit" << endl;
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
            command == 'q' || command == 'x' || command == 's' ||
            command == 'a')
            waiting = false;                                  
        else {
            cout << "Invalid command. [?]=push [=]print top [+][-][*][/] [x][s][a][Q]: ";
        }
    }
    return command;
}
//new function for fifth increment
void dc_calculate(){
    double a, b;
    double sum = 0;
    double temp = 0;
    double average = 0;
    int count = 0;
    Stack numbers;
    string line;
    //read the whole line of user input
    getline(cin, line);
    //convert it into a stringstream
    stringstream ss(line);

    string token;
    //while loop that goes through the whole user input
    while(ss>>token){

        if (token=="+"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (numbers.top(b)==underflow){cout << "Stack has just one entry" << endl; return;}
            numbers.pop();
            numbers.push(b+a);

        }else if(token=="q"){
            exit(0);
        }else if(token=="-"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (numbers.top(b)==underflow){cout << "Stack has just one entry" << endl; return;}
            numbers.pop();
            numbers.push(b-a);

        }else if(token=="*"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (numbers.top(b)==underflow){cout << "Stack has just one entry" << endl; return;}
            numbers.pop();
            numbers.push(b*a);

        }else if(token=="/"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (numbers.top(b)==underflow){cout << "Stack has just one entry" << endl; return;}
            numbers.pop();
            if (a==0){cout << "Division by zero" << endl; return;}
            numbers.push(b/a);

        }else if(token=="%"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (numbers.top(b)==underflow){cout << "Stack has just one entry" << endl; return;}
            numbers.pop();
            //fmod is % for doubles
            numbers.push(fmod(b,a));

        }else if(token=="^"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (numbers.top(b)==underflow){cout << "Stack has just one entry" << endl; return;}
            numbers.pop();
            numbers.push(pow(b,a));

        }else if(token=="v"){
            if (numbers.top(a)==underflow){cout << "Stack is empty" << endl; return;}
            numbers.pop();
            if (a<0){cout << "Cannot sqrt negative number" << endl; return;}
            numbers.push(sqrt(a));
        
        } else if(token=="x"){
        if (numbers.top(a) == underflow){cout << "Stack empty" << endl; return; }
        numbers.pop();
        if (numbers.top(b) == underflow){cout << "Stack has just one entry" << endl; return;}
        numbers.pop();
        if (numbers.push(a) == overflow){cout << "Stack is full" << endl; return;}
        if (numbers.push(b) == overflow){cout << "Stack is full" << endl; return;}
        
        }else if(token=="s"){
        while (!numbers.empty()){
            if (numbers.top(temp) == underflow){cout << "stack is empty" << endl; return;}
            sum += temp;
            numbers.pop();
        }
        if(numbers.push(sum)==overflow){cout <<"stack is full" << endl; return;}
        
        } else if(token=="a"){
        while (!numbers.empty()){
            if (numbers.top(temp) == underflow){cout << "stack is empty" << endl; return;}
            sum += temp;
            numbers.pop();
            count ++;
        }
        average=sum/count;
        if(numbers.push(average)==overflow){cout << "stack is full" << endl;return;}
        
        }else{//try catch to fix a nasty bug
            try{
        //turn user input string into a double
        double num = stod(token);
        //push double into stack
        numbers.push(num);
        } catch (...) {
        cout << "invalid input! " << token << endl;
        return;
        }}
    }
        double result;
        //save top double of stack into result and make sure stack isn't empty
        if (numbers.top(result)==underflow){cout << "stack is empty" << endl; return;}
        //print the result
        cout << result << endl;
    }

bool do_command(char command, Stack &numbers) {
    double p, q;
    double sum = 0;
    double temp = 0;
    int count = 0;
    double average = 0;
    switch (command) {
    case '?': 
        //fixed a nasty bug
        cout << "Enter a real number: ";
        if (cin >> p) {
        if (numbers.push(p) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
    } else {
        cout << "Invalid input, expected a number" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
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
        //third increment, added sum
    case 's':
        //while stack isn't empty
        while (!numbers.empty()){
            //add top to temp variable
            if (numbers.top(temp) == underflow){cout << "stack is empty" << endl; break;}
            //add temp to sum
            sum += temp;
            //pop the top number
            numbers.pop();
        }
        //push sum to stack
        if(numbers.push(sum)==overflow){cout <<"stack is full" << endl; break;}
         break;
        //fourth increment, added average
    case 'a':
        //sum logic with count++ added
        while (!numbers.empty()){
            if (numbers.top(temp) == underflow){cout << "stack is empty" << endl; break;}
            sum += temp;
            numbers.pop();
            count ++;
        }
        //After while loop average is equal to sum/count
        average=sum/count;
        //push average to stack
        if(numbers.push(average)==overflow){cout << "stack is full" << endl; break;}
        break;


    case 'q':
        cout << "Calculation finished." << endl;
        return false;
    }
    return true;
}
//added parameteres to main for argument handling (needed for -p)
int main(int argc, char* argv[]) {
    Stack stored_numbers;
    //if there are more arguments than just the program name
    //and the argument converted to string is equal to -p
    //we use the old structure
    if (argc > 1 && string(argv[1])=="-p"){
    introduction();
    instructions();
    while (do_command(get_command(), stored_numbers));
    } else {
        //we are being held as hostages until q
        while(true){
        dc_calculate();
        }
    }
    return 0;
    
}