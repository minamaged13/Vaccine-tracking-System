#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Citizen.h"
#include "HashTable.h"
#include "Queue.h"
#include <vector>
#include <sstream>
using namespace std;

const unsigned int TOTAL_POP = 100000000;
int dose1Total = 0;     //how many people that atleast took 1 dose counter
int dose2Total = 0;     //how many people that atleast took 2 doses counter
string dataFile = "data.csv";

int run(string gov[], HashTable* table, Queue* waitList1, Queue* waitList2);
void newrecord(string gov[], HashTable* table, Queue* waitList1, Queue* waitList2);//register
void newrecord(HashTable* table, vector<string> info, Queue* waitList1, Queue* waitList2);//add data to file 
void signin(HashTable* table);
void admin(HashTable* table, Queue* waitList1, Queue* waitList2);
void viewData(HashTable* table);
void deleteData(HashTable* table);
int idSize(long long _id);
void save(Queue* additions);

Queue* additions;

int main()
{
    HashTable* HT = new HashTable;
    Queue* waitList1 = new Queue();
    Queue* waitList2 = new Queue();
    additions = new Queue();


    string govList[] = {
           "alexandria",
           "assiut",
           "aswan",
           "beheira",
           "bani suef",
           "cairo",
           "daqahliya",
           "damietta",
           "fayyoum",
           "gharbiya",
           "giza",
           "ismailia",
           "kafr el sheikh",
           "luxor",
           "marsa matrouh",
           "minya",
           "monofiya",
           "new valley",
           "north sinai",
           "port said",
           "qalioubiya",
           "qena",
           "red sea",
           "sharqiya",
           "sohag",
           "south sinai",
           "suez"
    };

    //load data from file

    ifstream dataF(dataFile);

    //if file doesnt exist, create it
    if (!dataF)
    {
        ofstream o_dataF(dataFile);
    }

    string line;
    while (getline(dataF, line))
    {
        vector<string> result;

        stringstream lineStream(line);
        string info;

        while (getline(lineStream, info, ','))
        {
            result.push_back(info);
        }

        newrecord(HT, result, waitList1, waitList2);
    }
    dataF.close();
    //For Performance benchmarking
    //float total = 0;
    //for (int i = 0; i < 500; i++)
    //{
    //    cout << HT->collisions[i] << " ";
    //    total += HT->collisions[i];
    //}
    //cout << endl << total / 500 << endl;


    cout << "Welcome to the Egyptian Vaccine Tracking System" << endl;

    while(run(govList, HT, waitList1, waitList2)); //keep running until value returned is 0

    save(additions);
    cout << "Program closed.\n";
    
}

int run(string gov[], HashTable* table, Queue* waitList1, Queue* waitList2)
{
    cout << "_______________________________________________________\n";
    cout << "For new record registeration kindly press 1 " << endl;
    cout << "Already have a record kindly press 2" << endl;
    cout << "Administrator press 3" << endl;
    cout << "To end program press 4" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        newrecord(gov, table, waitList1, waitList2);
        return 1;

    case 2:
        signin(table);
        return 1;

    case 3:
        admin(table, waitList1, waitList2);
        return 1;

    case 4:
        return 0;

    default:
        cout << "Invalid entry." << endl;
        return 0;
    }
}

void newrecord(string gov[], HashTable* table, Queue* waitList1, Queue* waitList2)
{
    long long ID;
    string fullname;
    string password;
    char gender;
    int age;
    string governorate;
    cout << "National ID: ";
    cin >> ID;
    //Checking that ID does not exceed 13 digits
    if (idSize(ID) != 13)
    {
        cout << "Invalid National ID number entered." << endl;
        return;
    }

    //Checking for ID not being repeated
    if (table->searchItem(ID)->getId() != 0)
    {
        cout << "ID already exists.\n";
        return;
    }

    cout << "Full Name: ";
    getline(cin, fullname);
    getline(cin, fullname);

    while (any_of(fullname.begin(), fullname.end(), ::isdigit))
    {
        cout << "Full Name: ";
        getline(cin, fullname);
    }

    cout << "Create Password: ";
    cin >> password;
    do
    {
        cout << "Gender(f/m): ";
        cin >> gender;
        gender = tolower(gender);
    } while (gender != 'm' && gender != 'f');

    cout << "Age: ";
    cin >> age;
    if (age < 18)
    {
        cout << "You are not eligible for taking the vaccine." << endl;
        return;
    }

    cout << "Governorate: ";
    getline(cin, governorate);
    getline(cin, governorate);

    for (int i = 0; i < governorate.size(); i++)
    {
        governorate[i] = tolower(governorate[i]);
    }

    bool flag = false;
    // TODO use better search algorithm
    for (int i = 0; i < 27; i++)
    {
        if (governorate == gov[i])
        {
            flag = true;
            break;
        }
    }

    if (flag == false)
    {
        cout << "Governorate entered does not exist in Egypt." << endl;
        return;
    }
    Citizen* C = new Citizen(ID, fullname, password, gender, age, governorate);
    table->insertItem(C);
    waitList1->enqueue(C);
    additions->enqueue(C);
    cout << "Record added successfully into waiting list. You are number " << waitList1->size() << " in line.\n";
}

//for loading from file
void newrecord(HashTable* table, vector<string> info, Queue* waitList1, Queue* waitList2)
{
    if (info[0].size() != 13)
    {
        return;
    }

    long long ID = stoll(info[0]);
    string fullname = info[1];
    string password = info[2];
    char gender = info[3][0];
    int age = stoi(info[4]);
    string governorate = info[5];
    bool dose1 = stoi(info[6]);
    bool dose2 = stoi(info[7]);

    Citizen* C = new Citizen(ID, fullname, password, gender, age, governorate);
    C->setVacc1(dose1);
    C->setVacc2(dose2);

    table->insertItem(C);
    if (!C->getVacc1())
    {
        waitList1->enqueue(C);
    }
    else if (C->getVacc1() && !C->getVacc2())
    {
        waitList2->enqueue(C);
        dose1Total++;
    }
    else
    {
        dose2Total++;
    }
}

void signin(HashTable* table)
{
    Citizen* c;
    int choice;
    long long id;
    string password;
    cout << "ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> password;
    cout << "______________________________________\n";
    c = table->searchItem(id);
    if (c->getId() == 0)
    {
        cout << "\nthis user is not registered\n\n";   
        return;
    }

    // password check
    if (c->getPass() == password)
    {
        c->CitDisplay();
        cout << "___________________________________\nTo edit your info press 1\n";
        cout << "To delete your record press 2\n\n";
        cout << "To return main menu press 3\n\n";
        cin >> choice;
        // editing data
        if (choice == 1)
        {
            Citizen* c = table->searchItem(id);
            c->Update();
            c->CitDisplay();
            return;
        }
        if (choice == 2) 
        {
            Citizen* c = table->searchItem(id);
            table->deleteItem(id);
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "password is not correct.\n\n";
    }
}

void admin(HashTable* table, Queue* waitList1, Queue* waitList2)
{
    do 
    {
        cout << "Please enter admin password: ";
        string p;
        cin >> p;
        if (p != "0000")
        {
            cout << "Invalid entry." << endl;
            cout << "1- Try again." << endl << "2- Return to main menu." << endl;
            int choice;
            cin >> choice;
            if (choice == 1) {
                continue;
            }
            else 
            {
                return;
            }
        }
        else 
        {
            while (true) 
            {
                cout << "1- View data\n2- Delete data\n3- Proceed Line (start vaccination)\n4- View statistics\n5- Return to main menu\n";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    viewData(table);
                }
                else if (choice == 2) {
                    deleteData(table);
                    cout << "Data deleted.\n\n";
                }
                else if (choice == 3)
                {
                    cout << " 1- First dose\n2- Second dose\n";
                    cin >> choice;
                    if (choice == 1)
                    {
                        Citizen* temp = waitList1->dequeue();
                        temp->setVacc1(true);
                        waitList2->enqueue(temp);   //dequeue first in line 1 and enqueue them in line 2
                        cout << "Dose 1 was registered to " << temp->getName() << ". Please wait for your second vaccination. You are number " << waitList2->size() << " in line.\n";
                        dose1Total++;
                    }
                    else
                    {
                        Citizen* temp = waitList2->dequeue();
                        temp->setVacc2(true);
                        dose2Total++;
                    }
                }
                else if (choice == 4)
                {
                    //Percentage of the unvaccinated **.
                    //Percentage of those who received at least one dose** .
                    //Percentage of those who got fully vaccinated** 
                    cout << "\n______________________________________________________________________________________________________________\n";

                    float percentage = float(table->getSize()) / TOTAL_POP;
                    percentage *= 100;

                    cout << "Percentage of those who applied for vaccination -whether vaccinated or not- to the total population of Egypt is: " << percentage << "%.\n\n";

                    percentage = float(table->getSize() - (dose1Total + dose2Total)) / TOTAL_POP;
                    percentage *= 100;

                    cout << "Percentage of the unvaccinated citizens in Egypt is: " << percentage << "%.\n";

                    percentage = float(table->getSize() - (dose1Total + dose2Total)) / table->getSize();
                    percentage *= 100;

                    cout << "Percentage of the unvaccinated users that applied is: " << percentage << "%.\n\n";

                    percentage = float(dose1Total + dose2Total) / TOTAL_POP;
                    percentage *= 100;

                    cout << "Percentage of the citizens who received atleast one dose in Egypt is: " << percentage << "%.\n";

                    percentage = float(dose1Total + dose2Total) / table->getSize();
                    percentage *= 100;

                    cout << "Percentage of the users that applied who received atleast one dose is: " << percentage << "%.\n\n";

                    percentage = float(dose2Total) / TOTAL_POP;
                    percentage *= 100;

                    cout << "Percentage of the citizens who received both doses in Egypt is: " << percentage << "%.\n";

                    percentage = float(dose2Total) / table->getSize();
                    percentage *= 100;

                    cout << "Percentage of the users that applied who received both doses is: " << percentage << "%.";

                    cout << "\n______________________________________________________________________________________________________________\n";
                }
                else 
                {
                    return;
                }
            }
        }
    } while (true);
}
void viewData(HashTable* table) {
    while (true) {
        if (table->getSize() == 0)
        {
            cout << "No data to view.\n";
        }
        int choice;
        cout << "_______________________________________________________\n";
        cout << "To view all users' data press 1" << endl;
        cout << "To view only one user's data press 2" << endl;
        cout << "To return to main menu press 3" << endl;
        cin >> choice;
        if (choice == 1)
        {
            table->printTable();
        }
        else if (choice == 2)
        {
            cout << "Please enter ID: ";
            long long NatID;
            cin >> NatID;
            table->searchItem(NatID)->CitDisplay();
        }
        else
        {
            return;
        }

    }
}
void deleteData(HashTable* table) {
    while (true)
    {
        int choice;
        cout << "To delete all users' data press 1" << endl;
        cout << "To delete only one user's data press 2" << endl;
        cout << "To return to main menu press 3" << endl;

        cin >> choice;
        if (choice == 1)
        {
            table->deleteAll();
        }
        else if (choice == 2)
        {
            cout << "Please enter ID: ";
            long long NatID;
            cin >> NatID;
            table->deleteItem(NatID);
            cout << "Total users: " << table->getSize() << endl;
        }
        else
        {
            return;
        }
    }
}

int idSize(long long _id)
{
    int noOfDigits = 0;
    while (_id > 0)
    {
        noOfDigits++;
        _id = _id / 10;
    }
    return noOfDigits;
}

//add new records to file
void save(Queue* additions)
{
    Citizen* c;
    ofstream out(dataFile, ios::app);

    while (!additions->isEmpty())
    {
        c = additions->dequeue();
        out << c->getId() << "," << c->getName() << "," << c->getPass() << "," << c->getGender() << "," << c->getAge() << "," << c->getGov() << "," << c->getVacc1() << "," << c->getVacc2() << "\n";
    }
    out.close();

}
