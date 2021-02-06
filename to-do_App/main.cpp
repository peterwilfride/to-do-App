#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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

//global variable
vector<Task> tasks_list;
fstream file;
string database = "db.txt";
//o - modo de escrita
//i - modo de leitura

void menu() {
    cout << "WELCOME TO THE TO-DO APP" << endl;
    cout << "+======================+" << endl;
    cout << "| [1] CREATE NEW TASK  |" << endl;
    cout << "| [2] LIST YOUR TASKS  |" << endl;
    cout << "+======================+" << endl;
}

void save_to_db(vector<Task> &tasks) {
    //recebe como parâmetro um vetor de tarefas para escrever em um banco de dados
    file.open(database, ios::app);
    for (auto i = tasks.cbegin(); i != tasks.cend(); ++i) {
        file << "Name: " << i->name << endl;
        file << "Day: " << i->date.day << endl;
        file << "Month: " << i->date.month << endl;
        file << "Year: " << i->date.year << endl;
        file << "Description: " << i->description << endl;
    }
    file.close();
}

void add_task(vector<Task> &tasks, string name, int d, int m, int y, string descrpt) {
    //variavel temporária para salvar a tarefa
    Task task_tmp;
    task_tmp.name = name;
    task_tmp.date.day = d;
    task_tmp.date.month = m;
    task_tmp.date.year = y;
    task_tmp.description = descrpt;
    //adiciona a nova tarefa ao vetor e tarefas
    tasks.push_back(task_tmp);
    //salva em banco de dados
    save_to_db(tasks);
}

//recebe como arquivo de texto como parâmetro, ler cada tarefa e gera um vetor de tarefas
vector<Task> read_from_db(ifstream& stream) {
    string key, str;
    //opem de database
    stream.open(database);
    //position in list of tasks global variable
    int pos = 0;

    if(!stream.is_open()) {
        cout << "Error when trying to read the database" << endl;
        cout << "Exiting..." << endl;
        exit(0);
    }

    while(getline(stream, str)) {
        if(stream.good()) {
            stringstream ss(str);
            ss >> key;
            cout << key << endl;
            if(key.compare("Name:") == 0){
                string name;
                ss >> name;
                cout << name << " ";
                tasks_list[pos].name = name;
            }else if(key.compare("Day:") == 0){
                int day;
                ss >> day;
                cout << day << " ";
                tasks_list[pos].date.day = day;
            }else if(key.compare("Month:") == 0){
                int month;
                ss >> month;
                cout << month << " ";
                tasks_list[pos].date.month = month;
            }else if(key.compare("Year:") == 0){
                int year;
                ss >> year;
                cout << year << " ";
                tasks_list[pos].date.year = year;
            }else if(key.compare("Description:") == 0){
                string descrpt;
                ss >> descrpt;
                cout << descrpt << " ";
                tasks_list[pos].description = descrpt;
                pos++;
            }else {
                continue;
            }
        }else {
            break;
        }
    }
    cout << "Sucessfuly for reading the database!" << endl;
    cout << "[pos] " << pos << endl;
    stream.close();
    return tasks_list;
}

//o - modo de escrita
//i - modo de leitura
void list_tasks(vector<Task> &tasks) {
    ifstream file(database);
    tasks = read_from_db(file);

    cout << endl;
    cout << "Here are your tasks!" << endl;
    cout << "...................." << endl;

    /*
    for (auto i = tasks.cbegin(); i != tasks.cend(); ++i) {
        cout << "........................." << endl;
        cout << "Name: " << i->name << endl;
        cout << "Date: " << i->date.day << "/" << i->date.month << "/" << i->date.year << endl;
        cout << "Description: " << endl;
        cout << i->description << endl;
        cout << "........................." << endl;
    }
    */
}

int main()
{
    //show the menu
    menu();

    int opt;
    Task task;

    //choose an option
    do {
        cout << endl << "Choose an option: "; cin >> opt;
        if(opt == 1){
            cout << "Enter with a new task" << endl;
            cout << "day of task: "; cin >> task.date.day;
            cout << "month of task: "; cin >> task.date.month;
            cout << "year of task: "; cin >> task.date.year;
            cin.ignore();
            cout << "Name of task: "; getline(cin, task.name);
            cout << "description of the task: " << endl; getline(cin, task.description);

            //adiciona tarefas ao vetor e salva no banco de dados
            add_task(tasks_list, task.name, task.date.day, task.date.month, task.date.year, task.description);
        }else
        if(opt == 2) {
            //lista todas a tarefas na tela
            list_tasks(tasks_list);
        }
    } while(true);

    return 0;
}
