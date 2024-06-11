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

    virtual string getCategory() const = 0; // Pure virtual function
    virtual string getYearLevel() const = 0; // Pure virtual function

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "- Full Name: " << student.name << endl;
        os << "- Student ID: " << student.id << endl;
        os << "- Course: " << student.course << endl;
        os << "- Mobile Number: " << student.mobile << endl;
        os << "- Category: " << student.getCategory() << endl;
        os << "- Year Level: " << student.getYearLevel() << endl;
        return os;
    }

    virtual ~Student() {} // Virtual destructor
};

// Derived classes for each year level
class FirstYear : public Student {
public:
    FirstYear(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getCategory() const {
        return "Undergraduate";
    }

    string getYearLevel() const {
        return "1st Year";
    }
};

class SecondYear : public Student {
public:
    SecondYear(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getCategory() const {
        return "Undergraduate";
    }

    string getYearLevel() const {
        return "2nd Year";
    }
};

class ThirdYear : public Student {
public:
    ThirdYear(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getCategory() const {
        return "Undergraduate";
    }

    string getYearLevel() const {
        return "3rd Year";
    }
};

class FourthYear : public Student {
public:
    FourthYear(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getCategory() const {
        return "Undergraduate";
    }

    string getYearLevel() const {
        return "4th Year";
    }
};

class FifthYear : public Student {
public:
    FifthYear(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getCategory() const {
        return "Undergraduate";
    }

    string getYearLevel() const {
        return "5th Year";
    }
};

class Graduate : public Student {
public:
    Graduate(string name, string id, string course, string mobile)
        : Student(name, id, course, mobile) {}

    string getCategory() const {
        return "Graduate";
    }

    string getYearLevel() const {
        return "N/A"; // Graduates don't have a year level
    }
};

class StudentMonitoringSystem {
private:
    vector<Student*> students;
    string adminU;
    string adminP;
    string undergradFilename; // Declare undergradFilename member variable
    string gradFilename; // Declare gradFilename member variable

    void display_intro() const {
        cout << "-----------------------------------------------" << endl
             << "------     STUDENT MONITORING SYSTEM     ------" << endl
             << "----------     CS121 Midterm PIT     ----------" << endl
             << "-----------------------------------------------" << endl << endl << endl;
    }

    void login() const {
        string username, password;

        cout << "----------------   [ LOGIN ]   ----------------" << endl << endl;

        while (true) {
            cout << "> Enter Username: ";
            cin >> username;

            cout << "> Enter Password: ";
            cin >> password;

            if ((username == adminU) && (password == adminP)) {
                cout << endl << "------     [ Successfully Logged In ]     ------" << endl << endl;
                break;
            } else {
                cout << endl << "--     [ Invalid Username and Password ]     --" << endl << endl;
            }
        }
    }

    Student* create_student_record() {
    string name, id, course, mobile;
    int yearLevel;
    int studentType;

    cout << "-----------------------------------------------" << endl << endl;
    cout << "> Choose Student Type:" << endl;
    cout << "  [1] Undergraduate" << endl;
    cout << "  [2] Graduate" << endl;
    cout << "> Enter Option: ";
    cin >> studentType;

    cout << "> Enter Student Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "> Enter Student ID: ";
    getline(cin, id);

    cout << "> Enter Student Course: ";
    getline(cin, course);

    cout << "> Enter Student Mobile Number: ";
    getline(cin, mobile);

    switch (studentType) {
        case 1: {
            cout << "- [1] 1st, [2] 2nd, [3] 3rd, [4] 4th, [5] 5th: ";
            cout << "> Enter Year Level: ";
            cin >> yearLevel;
            switch (yearLevel) {
                case 1: return new FirstYear(name, id, course, mobile);
                case 2: return new SecondYear(name, id, course, mobile);
                case 3: return new ThirdYear(name, id, course, mobile);
                case 4: return new FourthYear(name, id, course, mobile);
                case 5: return new FifthYear(name, id, course, mobile);
                default: throw invalid_argument("Invalid year level");
            }
        }
        case 2: return new Graduate(name, id, course, mobile);
        default: throw invalid_argument("Invalid student type");
    }
}

    void input_record() {
        try {
            Student* student = create_student_record();
            students.push_back(student);
            cout << endl << "-------     [ Student Record Added ]     ------" << endl << endl;
            save_records(); // Save records after adding
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }

	void view_all_records() const {
    cout << "--------------------------------------------------" << endl;
    cout << "[1] Undergraduate Student Records" << endl;
    cout << "[2] Graduate Student Records" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "> Enter an option: ";
    int option;
    cin >> option;
    cout << endl;

    switch (option) {
        case 1:
            view_records("Undergraduate");
            break;
        case 2:
            view_records("Graduate");
            break;
        default:
            cout << "Invalid option!" << endl;
            break;
    }
}

	void view_records(const string& category) const {
	    cout << "--------------------------------------------------" << endl;
	    cout << "------------     " << category << " Student Records     ------------" << endl;
	    cout << "--------------------------------------------------" << endl;
	
	    bool found = false;
	    for (size_t i = 0; i < students.size(); ++i) {
	        if (students[i]->getCategory() == category) {
	            cout << "- RECORD NUMBER [" << i + 1 << "]" << endl << endl;
	            cout << *students[i] << endl;
	            found = true;
	        }
	    }
	
	    if (!found) {
	        cout << "No " << category << " records found." << endl;
	    }
	
	    cout << "--------------------------------------------------" << endl;
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
            cout << endl << "--------    [ Student Record(s) Found ]    -------" << endl << endl;
            for (size_t i = 0; i < found_indices.size(); ++i) {
                int idx = found_indices[i];
                cout << "- RECORD NUMBER [" << idx + 1 << "]" << endl << endl; // Display record number starting from 1
                cout << *students[idx] << endl;
            }

            int chosen_record_number;
            cout << "> Enter Record Number to Access: ";
            cin >> chosen_record_number;

            // Convert record number to index
            int chosen_index = chosen_record_number - 1;

            // Ensure the chosen index is valid
            if (find(found_indices.begin(), found_indices.end(), chosen_index) != found_indices.end()) {
                // Prompt user to choose action for the chosen record
                int choice;
                while (true) {
                	cout << endl << "-----------------------------------------------" << endl
                 				 << "---  Update Record [1] | Delete Record  [2]  --" << endl
                 				 << "--------------  Done/Proceed [3]  -------------" << endl << endl
                    			 << "> Choose Action for Selected Record: ";
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
                cout << "---------  [ Invalid Record Number ]  ---------"<< endl << endl;
            }
        } else {
            cout << endl << "-----     [ Student Record Not Found ]     ----" << endl << endl;
        }
    }

    void delete_record(int index) {
        delete students[index];
        students.erase(students.begin() + index);
        cout << endl << "------     [ Student Record Deleted ]     -----" << endl << endl;
        save_records(); // Save records after deletion
    }

    void update_record(int index) {
    Student* student = students[index];
    int record_part;

    while (true) {
        cout << endl << "-----------------------------------------------" << endl
             		 << "------  Name [1] | ID [2] | Course [3]  -------" << endl
             		 << "--  Number [4] | Year Level [5] | Done [6]  ---" << endl << endl
             		 << "> Choose Which Part to Update: ";
        cin >> record_part;

        if (record_part == 6) {
            cout << endl;
            return;
        }

        cout << endl;
        switch (record_part) {
            case 1:
                cout << "> Enter New Student Name: ";
                cin.ignore();
                getline(cin, student->name);
                cout << endl << "-------     [ Student Name Updated ]     ------" << endl;
                break;
            case 2:
                cout << "> Enter New Student ID: ";
                cin.ignore();
                getline(cin, student->id);
                cout << endl << "--------     [ Student ID Updated ]     -------" << endl;
                break;
            case 3:
                cout << "> Enter New Student Course: ";
                cin.ignore();
                getline(cin, student->course);
                cout << endl << "------     [ Student Course Updated ]     -----" << endl;
                break;
            case 4:
                cout << "> Enter New Student Mobile Number: ";
                cin.ignore();
                getline(cin, student->mobile);
                cout << endl << "--     [ Student Mobile Number Updated ]     --" << endl;
                break;
            case 5: {
                int yearLevel;
                cout << "- [1] 1st, [2] 2nd, [3] 3rd, [4] 4th, [5] 5th: ";
                cout << "> Enter New Year Level: ";
                cin >> yearLevel;
                Student* updatedStudent = NULL;
                switch (yearLevel) {
                    case 1: updatedStudent = new FirstYear(student->name, student->id, student->course, student->mobile); break;
                    case 2: updatedStudent = new SecondYear(student->name, student->id, student->course, student->mobile); break;
                    case 3: updatedStudent = new ThirdYear(student->name, student->id, student->course, student->mobile); break;
                    case 4: updatedStudent = new FourthYear(student->name, student->id, student->course, student->mobile); break;
                    case 5: updatedStudent = new FifthYear(student->name, student->id, student->course, student->mobile); break;
                    default: 
                        cout << "-------    [ Invalid Year Level ]     --------" << endl;
                        continue;
                }
                delete students[index];
                students[index] = updatedStudent;
                cout << endl << "------     [ Year Level Updated ]     ------" << endl;
                break;
            }
            default:
                cout << "-------    [ Invalid Part Number ]     --------" << endl;
                break;
        }
        save_records();
    }
}


    void prompt() const {
        cout << "-----     [ Press Enter to Continue ]     -----" << endl;
        cin.ignore();
        while (true) {
            if (cin.get() == '\n') {
                break;
            }
        }
    }

    void load_records() {
    ifstream undergradFile(undergradFilename.c_str());
    ifstream gradFile(gradFilename.c_str());

    if (!undergradFile || !gradFile) {
        cerr << "Could not open file for reading!" << endl;
        return;
    }

    // Load undergraduate records
    string name, id, course, mobile;
    int yearLevel;
    while (undergradFile >> name >> id >> course >> mobile >> yearLevel) {
        Student* student = NULL;
        switch (yearLevel) {
            case 1: student = new FirstYear(name, id, course, mobile); break;
            case 2: student = new SecondYear(name, id, course, mobile); break;
            case 3: student = new ThirdYear(name, id, course, mobile); break;
            case 4: student = new FourthYear(name, id, course, mobile); break;
            case 5: student = new FifthYear(name, id, course, mobile); break;
            default: cerr << "Invalid year level for undergraduate student" << endl;
        }
        if (student) {
            students.push_back(student);
        }
    }

    // Load graduate records
    while (gradFile >> name >> id >> course >> mobile) {
        Student* student = new Graduate(name, id, course, mobile);
        students.push_back(student);
    }

    undergradFile.close();
    gradFile.close();
}


    void save_records() const {
    ofstream undergradFile(undergradFilename.c_str());
    ofstream gradFile(gradFilename.c_str());

    if (!undergradFile || !gradFile) {
        cerr << "Could not open file for writing!" << endl;
        return;
    }

    for (size_t i = 0; i < students.size(); ++i) {
        const Student* student = students[i];
        if (const FirstYear* fy = dynamic_cast<const FirstYear*>(student)) {
            undergradFile << fy->name << " " << fy->id << " " << fy->course << " " << fy->mobile << " 1" << endl;
        } else if (const SecondYear* sy = dynamic_cast<const SecondYear*>(student)) {
            undergradFile << sy->name << " " << sy->id << " " << sy->course << " " << sy->mobile << " 2" << endl;
        } else if (const ThirdYear* ty = dynamic_cast<const ThirdYear*>(student)) {
            undergradFile << ty->name << " " << ty->id << " " << ty->course << " " << ty->mobile << " 3" << endl;
        } else if (const FourthYear* fy = dynamic_cast<const FourthYear*>(student)) {
            undergradFile << fy->name << " " << fy->id << " " << fy->course << " " << fy->mobile << " 4" << endl;
        } else if (const FifthYear* fy = dynamic_cast<const FifthYear*>(student)) {
            undergradFile << fy->name << " " << fy->id << " " << fy->course << " " << fy->mobile << " 5" << endl;
        } else if (dynamic_cast<const Graduate*>(student)) {
            gradFile << student->name << " " << student->id << " " << student->course << " " << student->mobile << endl;
        }
    }

    undergradFile.close();
    gradFile.close();
}


public:
    StudentMonitoringSystem() : adminU("admin"), adminP("12345"), undergradFilename("undergraduates.txt"), gradFilename("graduates.txt") {}

    void run() {
        display_intro();
        login();
        load_records();
        int option = 0;
        while (option != 4) {
            cout << "--------------   [ MAIN MENU ]   --------------" << endl
                 << "--                                           --" << endl
                 << "--      [1] Add Student Record               --" << endl
                 << "--      [2] View All Student Record          --" << endl
                 << "--      [3] Find Student Record              --" << endl
                 << "--      [4] Exit Program                     --" << endl
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
                    view_all_records();
                    prompt();
                    break;
                case 3:
                    find_record();
                    prompt();
                    break;
                case 4:
                    cout << "---------     [ Exiting Program ]     ---------" << endl;
                    break;
                default:
                    cout << "----------     [ Invalid Option ]     ---------" << endl;
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
