#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Task {
    string name;
    Date date;
    string description;

};

vector<Task> tasks_list;

void menu() {
    cout << "WELCOME TO THE TO-DO APP" << endl;
    cout << "+======================+" << endl;
    cout << "| [1] CREATE NEW TASK  |" << endl;
    cout << "| [2] LIST YOUR TASKS  |" << endl;
    cout << "+======================+" << endl;
}

void add_task(vector<Task> &tasks, string name, int d, int m, int y, string descrpt) {
    Task task_tmp;
    task_tmp.name = name;
    task_tmp.date.day = d;
    task_tmp.date.month = m;
    task_tmp.date.year = y;
    task_tmp.description = descrpt;

    tasks.push_back(task_tmp);
}

void list_tasks(vector<Task> &tasks) {
    for (auto i = tasks.cbegin(); i != tasks.cend(); ++i) {
        cout << "........................." << endl;
        cout << "Name: " << i->name << endl;
        cout << "Date: " << i->date.day << "/" << i->date.month << "/" << i->date.year << endl;
        cout << "Description: " << endl;
        cout << i->description << endl;
        cout << "........................." << endl;
    }
}

int main()
{
    /*
     funcionamento do to-do app
     1 - Pode criar uma nova terefa
     2 - Listar as taferas de maneira ordenada
     ex.:
    */

    //show the menu
    menu();

    //choose an option
    int opt; cout << "Choose an option: "; cin >> opt;

    //crate the task
    Task task;
    if(opt == 1){
        cout << "day of task: "; cin >> task.date.day;
        cout << "month of task: "; cin >> task.date.month;
        cout << "year of task: "; cin >> task.date.year;
        cin.ignore();
        cout << "Name of task: "; getline(cin, task.name);
        cout << "description of the task: " << endl; getline(cin, task.description);
    }

    add_task(tasks_list, task.name, task.date.day, task.date.month, task.date.year, task.description);

    cout << endl;
    cout << "Here are your tasks!" << endl;
    cout << "...................." << endl;

    list_tasks(tasks_list);

    return 0;
}
