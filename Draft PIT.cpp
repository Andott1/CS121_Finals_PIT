#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

// Base class Student
class Student {
public:
    string name;
    string id;
    string course;
    string mobile;

    Student(string name = "", string id = "", string course = "", string mobile = "")
        : name(name), id(id), course(course), mobile(mobile) {}

    virtual string getYearLevel() const = 0; // Pure virtual function

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "- Student Name: " << student.name << endl;
        os << "- Student ID: " << student.id << endl;
        os << "- Student Course: " << student.course << endl;
        os << "- Student Mobile Number: " << student.mobile << endl;
        os << "- Year Level: " << student.getYearLevel() << endl;
        return os;
    }

    virtual ~Student() {} // Virtual destructor
};

// Derived classes for each year level
class Freshman : public Student {
public:
    Freshman(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getYearLevel() const {
        return "Freshman";
    }
};

class Sophomore : public Student {
public:
    Sophomore(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getYearLevel() const {
        return "Sophomore";
    }
};

class Junior : public Student {
public:
    Junior(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getYearLevel() const {
        return "Junior";
    }
};

class Senior : public Student {
public:
    Senior(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getYearLevel() const {
        return "Senior";
    }
};

class StudentMonitoringSystem {
private:
    vector<Student*> students;
    string adminU;
    string adminP;
    const char* filename;

    void display_intro() const {
        cout << "-----------------------------------------------" << endl
             << "------     STUDENT MONITORING SYSTEM     ------" << endl
             << "----------     CS121 Midterm PIT     ----------" << endl
             << "-----------------------------------------------" << endl << endl << endl;
    }

    void login() const {
        string username, password;

        cout << "----------------     Login     ----------------" << endl << endl;

        while (true) {
            cout << "> Enter Username: ";
            cin >> username;

            cout << "> Enter Password: ";
            cin >> password;

            if ((username == adminU) && (password == adminP)) {
                cout << endl << "------     ! Successfully Logged In !     ------" << endl << endl;
                break;
            } else {
                cout << endl << "--     ! Invalid Username and Password !     --" << endl << endl;
            }
        }
    }

    Student* create_student_record() {
        string name, id, course, mobile;
        int yearLevel;

        cout << "> Enter Student Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "> Enter Student ID: ";
        getline(cin, id);

        cout << "> Enter Student Course: ";
        getline(cin, course);

        cout << "> Enter Student Mobile Number: ";
        getline(cin, mobile);

        cout << "> Enter Year Level (1- Freshman, 2- Sophomore, 3- Junior, 4- Senior): ";
        cin >> yearLevel;

        switch (yearLevel) {
            case 1: return new Freshman(name, id, course, mobile);
            case 2: return new Sophomore(name, id, course, mobile);
            case 3: return new Junior(name, id, course, mobile);
            case 4: return new Senior(name, id, course, mobile);
            default: throw invalid_argument("Invalid year level");
        }
    }

    void input_record() {
        try {
            Student* student = create_student_record();
            students.push_back(student);
            cout << endl << "-------     ! Student Record Added !     ------" << endl << endl;
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }

    void view_records() const {
        cout << "-----------------------------------------------" << endl << endl;
        if (!students.empty()) {
            for (size_t i = 0; i < students.size(); ++i) {
                cout << "- Record Number [" << i + 1 << "]" << endl << endl;
                cout << *students[i] << endl;
            }
            cout << "-----------------------------------------------" << endl << endl;
        } else {
            cout << endl << "----------    ! No Record Found !    ----------" << endl << endl;
        }
    }

    int find_record_recursive(const string& key, int index) {
    if (index >= students.size()) {
        return -1; // Not found
    }

    // Check if key is a substring of student name or ID (case insensitive)
    string name_lower = students[index]->name;
    string id_lower = students[index]->id;
    transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);
    transform(id_lower.begin(), id_lower.end(), id_lower.begin(), ::tolower);

    string key_lower = key;
    transform(key_lower.begin(), key_lower.end(), key_lower.begin(), ::tolower);

    if (name_lower.find(key_lower) != string::npos || id_lower.find(key_lower) != string::npos) {
        return index; // Found
    }

    return find_record_recursive(key, index + 1); // Recur to the next index
}

    void find_record() {
    string key;
    cout << "> Enter Student Name or ID: ";
    cin.ignore();
    getline(cin, key);

    vector<int> found_indices;
    int index = 0;
    while ((index = find_record_recursive(key, index)) != -1) {
        found_indices.push_back(index);
        index++; // Move to the next index after finding a match
    }

    if (!found_indices.empty()) {
        cout << endl << "--------    ! Student Record(s) Found !    -------" << endl << endl;
        for (size_t i = 0; i < found_indices.size(); ++i) {
            int idx = found_indices[i];
            cout << "- Record Number [" << idx + 1 << "]" << endl; // Display record number starting from 1
            cout << *students[idx] << endl;
        }

        int chosen_record_number;
        cout << "Enter Record Number to Access: ";
        cin >> chosen_record_number;

        // Convert record number to index
        int chosen_index = chosen_record_number - 1;

        // Ensure the chosen index is valid
        if (find(found_indices.begin(), found_indices.end(), chosen_index) != found_indices.end()) {
            // Prompt user to choose action for the chosen record
            int choice;
            while (true) {
                cout << "> Choose an action for the above record:" << endl;
                cout << "[1] Update record" << endl;
                cout << "[2] Delete record" << endl;
                cout << "[3] Done/Proceed" << endl;
                cout << "> ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        update_record(chosen_index);
                        save_records();
                        break;
                    case 2:
                        delete_record(chosen_index);
                        save_records();
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Invalid choice! Please try again." << endl;
                        continue;
                }
                break; // Exit while loop after a valid choice
            }
        } else {
            cout << "Invalid record number chosen!" << endl;
        }
    } else {
        cout << endl << "-----     ! Student Record Not Found !     ----" << endl << endl;
    }
}

    void delete_record(int index) {
    delete students[index];
    students.erase(students.begin() + index);
    cout << endl << "------     ! Student Record Deleted !     -----" << endl << endl;
}

    void update_record(int index) {
    Student* student = students[index];
    int record_part;

    while (true) {
        cout << endl << "-----------------------------------------------" << endl
             << "- Name [1] | ID [2] | Course [3] | Number [4] -" << endl
             << "----------------- | Done [5] | ----------------" << endl << endl
             << "> Choose Which Part to Update: ";
        cin >> record_part;

        if (record_part == 5) {
            cout << endl;
            return;
        }

        cout << endl;
        switch (record_part) {
            case 1:
                cout << "> Enter New Student Name: ";
                cin.ignore();
                getline(cin, student->name);
                cout << endl << "-------     ! Student Name Updated !     ------" << endl;
                break;
            case 2:
                cout << "> Enter New Student ID: ";
                cin.ignore();
                getline(cin, student->id);
                cout << endl << "--------     ! Student ID Updated !     -------" << endl;
                break;
            case 3:
                cout << "> Enter New Student Course: ";
                cin.ignore();
                getline(cin, student->course);
                cout << endl << "------     ! Student Course Updated !     -----" << endl;
                break;
            case 4:
                cout << "> Enter New Student Mobile Number: ";
                cin.ignore();
                getline(cin, student->mobile);
                cout << endl << "--     ! Student Mobile Number Updated !     --" << endl;
                break;
            default:
                cout << "-------    ! Invalid Part Number !     --------" << endl;
                break;
        }
        save_records();
    }
    
}

    void prompt() const {
        cout << "-----     * Press enter to continue *     -----" << endl;
        cin.ignore();
        while (true) {
            if (cin.get() == '\n') {
                break;
            }
        }
    }

    void load_records() {
        ifstream file(filename);
        if (!file) {
            cerr << "Could not open file for reading!" << endl;
            return;
        }

        students.clear();
        string name, id, course, mobile;
        int yearLevel;

        while (file >> yearLevel) {
            file.ignore();
            getline(file, name);
            getline(file, id);
            getline(file, course);
            getline(file, mobile);

            Student* student = NULL;
            switch (yearLevel) {
                case 1: student = new Freshman(name, id, course, mobile); break;
                case 2: student = new Sophomore(name, id, course, mobile); break;
                case 3: student = new Junior(name, id, course, mobile); break;
                case 4: student = new Senior(name, id, course, mobile); break;
                default: throw invalid_argument("Invalid year level in file");
            }
            students.push_back(student);
        }

        file.close();
    }

    void save_records() const {
        ofstream file(filename);
        if (!file) {
            cerr << "Could not open file for writing!" << endl;
            return;
        }

        for (size_t i = 0; i < students.size(); ++i) {
            const Student* student = students[i];
            int yearLevel = 0;
            if (dynamic_cast<const Freshman*>(student)) yearLevel = 1;
            else if (dynamic_cast<const Sophomore*>(student)) yearLevel = 2;
            else if (dynamic_cast<const Junior*>(student)) yearLevel = 3;
            else if (dynamic_cast<const Senior*>(student)) yearLevel = 4;

            file << yearLevel << endl
                 << student->name << endl
                 << student->id << endl
                 << student->course << endl
                 << student->mobile << endl;
        }

        file.close();
    }

public:
	StudentMonitoringSystem() : adminU("admin"), adminP("12345"), filename("students.txt") {}
	
    void run() {
    display_intro();
    login();
    load_records();
    int option = 0;
    while (option != 4) {
        cout << "--------------     Main Menu     --------------" << endl
             << "--                                           --" << endl
             << "--       1. Input Student Record             --" << endl
             << "--       2. View All Student Record          --" << endl
             << "--       3. Find Student Record              --" << endl
             << "--       4. Exit Program                     --" << endl
             << "--                                           --" << endl
             << "-----------------------------------------------" << endl << endl;
        cout << "> Enter an option: ";
        cin >> option;
        cout << endl;

        switch (option) {
            case 1:
                input_record();
                save_records();
                break;
            case 2:
                view_records();
                prompt();
                break;
            case 3:
                find_record();
                prompt();
                break;
            case 4:
                cout << "---------     ! Exiting Program !     ---------" << endl;
                break;
            default:
                cout << "----------     ! Invalid Option !     ---------" << endl;
                break;
        }
    }
}

    ~StudentMonitoringSystem() {
        for (size_t i = 0; i < students.size(); ++i) {
            delete students[i];
        }
    }
};

int main() {
    StudentMonitoringSystem sms;
    sms.run();
    return 0;
}
