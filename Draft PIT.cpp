#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
using namespace std;

// Base class Student
class Student {
public:
    string name;
    string id;
    string course;
    string mobile;
    string dob; // Date of birth
    string sex; // Sex
    int age;    // Age

    Student(string name = "", string id = "", string mobile = "", string dob = "", int age = 0, string sex = "", string course = "")
        : name(name), id(id), mobile(mobile), dob(dob), age(age), sex(sex), course(course) {}
	
	virtual string getYearLevel() const = 0; // Pure virtual function
    virtual string getProgram() const = 0; // Pure virtual function

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "- Full Name: " << student.name << endl;
        os << "- Student ID: " << student.id << endl;
        os << "- Mobile Number: " << student.mobile << endl;
        os << "- Date of Birth: " << student.dob << endl;
        os << "- Age: " << student.age << endl;
        os << "- Sex: " << student.sex << endl;
        os << "- Course: " << student.course << endl;
        os << "- Year Level: " << student.getYearLevel() << endl;
        os << "- Program: " << student.getProgram() << endl;
        
        return os;
    }

    virtual ~Student() {} // Virtual destructor
};

// Derived classes for each year level
class FirstYear : public Student {
public:
    FirstYear(string name, string id, string mobile, string dob, int age, string sex, string course)
        : Student(name, id, mobile, dob, age, sex, course) {}

    string getYearLevel() const {
        return "1st Year";
    }
    
    string getProgram() const {
        return "Undergraduate";
    }
};

class SecondYear : public Student {
public:
    SecondYear(string name, string id, string mobile, string dob, int age, string sex, string course)
        : Student(name, id, mobile, dob, age, sex, course) {}

    string getYearLevel() const {
        return "2nd Year";
    }
    
    string getProgram() const {
        return "Undergraduate";
    }
};

class ThirdYear : public Student {
public:
    ThirdYear(string name, string id, string mobile, string dob, int age, string sex, string course)
        : Student(name, id, mobile, dob, age, sex, course) {}

    string getYearLevel() const {
        return "3rd Year";
    }
    
    string getProgram() const {
        return "Undergraduate";
    }
};

class FourthYear : public Student {
public:
    FourthYear(string name, string id, string mobile, string dob, int age, string sex, string course)
        : Student(name, id, mobile, dob, age, sex, course) {}

    string getYearLevel() const {
        return "4th Year";
    }
    
    string getProgram() const {
        return "Undergraduate";
    }
};

class FifthYear : public Student {
public:
    FifthYear(string name, string id, string mobile, string dob, int age, string sex, string course)
        : Student(name, id, mobile, dob, age, sex, course) {}

    string getYearLevel() const {
        return "5th Year";
    }
    
    string getProgram() const {
        return "Undergraduate";
    }
};

class Graduate : public Student {
public:
    Graduate(string name, string id, string mobile, string dob, int age, string sex, string course)
        : Student(name, id, mobile, dob, age, sex, course) {}

    string getYearLevel() const {
        return "N/A"; // Graduates don't have a year level
    }
    
    string getProgram() const {
        return "Graduate";
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
             << "-----   [ STUDENT INFORMATION SYSTEM ]   ------" << endl
             << "----------   [ CS121 FINALS PIT ]   -----------" << endl
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
                cout << endl << "---        [ Successfully Logged In ]       ---" << endl << endl;
                break;
            } else {
                cout << endl << "---    [ Invalid Username and Password ]    ---" << endl << endl;
            }
        }
    }

    Student* create_student_record() {
    string name, id, mobile, dob,  sex, course;
    int age, yearLevel;
    int studentProgram;

    cout << "-----------------------------------------------" << endl << endl;
    cout << "- Choose Student Program:" << endl;
    cout << "  [1] Undergraduate" << endl;
    cout << "  [2] Graduate" << endl << endl;
    cout << "> Enter Option: ";
    cin >> studentProgram;
    cout << endl;

    cout << "> Enter Full Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "> Enter Student ID: ";
    getline(cin, id);

    cout << "> Enter Mobile Number: ";
    getline(cin, mobile);

    cout << "> Enter Date of Birth [YYYY-MM-DD]: ";
    getline(cin, dob);
    
    cout << "> Enter Age: ";
    cin >> age;
    cin.ignore();

    cout << "> Enter Sex [M/F]: ";
    getline(cin, sex);

    cout << "> Enter Student Course: ";
    getline(cin, course);

    switch (studentProgram) {
        case 1: {
            cout << endl << "- [1] 1st, [2] 2nd, [3] 3rd, [4] 4th, [5] 5th" << endl;
            cout << "> Enter Year Level: ";
            cin >> yearLevel;
            switch (yearLevel) {
                case 1: return new FirstYear(name, id, mobile, dob, age, sex, course);
                case 2: return new SecondYear(name, id, mobile, dob, age, sex, course);
                case 3: return new ThirdYear(name, id, mobile, dob, age, sex, course);
                case 4: return new FourthYear(name, id, mobile, dob, age, sex, course);
                case 5: return new FifthYear(name, id, mobile, dob, age, sex, course);
                default: throw invalid_argument("---         [ Invalid Year Level ]          ---");
            }
        }
        case 2: return new Graduate(name, id, mobile, dob, age, sex, course);
        default: throw invalid_argument("---        [ Invalid student type ]         ---");
    }
}

    void input_record() {
        try {
            Student* student = create_student_record();
            students.push_back(student);
            cout << endl << "---         [ Student Record Added ]        ---" << endl << endl;
            save_records(); // Save records after adding
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }

	void view_all_records() const {
	cout << "-----------------------------------------------" << endl << endl;
    cout << "- Choose Program Type of Record: " << endl;
    cout << "  [1] Undergraduate Student Records" << endl;
    cout << "  [2] Graduate Student Records" << endl << endl;
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
            cout << "---            [ Invalid Option ]           ---" << endl;
            break;
    }
}

	void view_records(const string& program) const {
		if(program == "Undergraduate") {
	    	cout << "----   [ UNDERGRADUATE STUDENT RECORDS ]   ----" << endl << endl;
		}
		else {
	    	cout << "------   [ GRADUATE STUDENT RECORDS ]   -------" << endl << endl;
		}
	
	    bool found = false;
	    for (size_t i = 0; i < students.size(); ++i) {
	        if (students[i]->getProgram() == program) {
	            cout << "- RECORD NUMBER [" << i + 1 << "]" << endl << endl;
	            cout << *students[i] << endl;
	            found = true;
	        }
	    }
	
	    if (!found) {
	        cout << "--- [ No " << program << " Records Found ] ---" << endl;
	    }
	    cout << "-----------------------------------------------" << endl << endl;
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
            cout << endl << "---       [ Student Record(s) Found ]       ---" << endl << endl;
            for (size_t i = 0; i < found_indices.size(); ++i) {
                int idx = found_indices[i];
                cout << "- RECORD NUMBER [" << idx + 1 << "]" << endl << endl; // Display record number starting from 1
                cout << *students[idx] << endl;
            }

            int chosen_record_number;
            cout << "-----------------------------------------------" << endl << endl;
            cout << "> Enter Record Number to Access: ";
            cin >> chosen_record_number;

            // Convert record number to index
            int chosen_index = chosen_record_number - 1;

            // Ensure the chosen index is valid
            if (find(found_indices.begin(), found_indices.end(), chosen_index) != found_indices.end()) {
                // Prompt user to choose action for the chosen record
                int choice;
                while (true) {
                	cout << endl << "-----------------------------------------------" << endl << endl;
                	cout << "- Choose Action for Selected Record: " << endl
		    			 << "  [1] Update Record" << endl
		    			 << "  [2] Delete Record" << endl
		    			 << "  [3] Done/Proceed" << endl << endl;
				    cout << "> Enter Option: ";
                    cin >> choice;
                    cout << endl;

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
                            cout << "---            [ Invalid Option ]           ---" << endl;
                            continue;
                    }
                    break; // Exit while loop after a valid choice
                }
            } else {
                cout << endl << "---        [ Invalid Record Number ]        ---"<< endl << endl;
            }
        } else {
            cout << endl << "---       [ Student Record Not Found ]      ---" << endl << endl;
        }
    }

    void delete_record(int index) {
        delete students[index];
        students.erase(students.begin() + index);
        cout << endl << "---        [ Student Record Deleted ]       ---" << endl << endl;
        save_records(); // Save records after deletion
    }

    void update_record(int index) {
    Student* student = students[index];
    int record_part;

    while (true) {
    	cout << "-----------------------------------------------" << endl << endl;
    	cout << "- Choose Part to Update: " << endl
		     << "  [1] Name" << endl
		     << "  [2] Student ID" << endl
		     << "  [3] Mobile Number" << endl
		     << "  [4] Date of Birth" << endl
		     << "  [5] Age" << endl
		     << "  [6] Sex" << endl
		     << "  [7] Course" << endl
		     << "  [8] Year Level" << endl
		     << "  [0] Done" << endl << endl;
		cout << "> Enter Option: ";
        cin >> record_part;

        if (record_part == 0) {
            cout << endl;
            return;
        }

        cout << endl;
        switch (record_part) {
            case 1:
                cout << "> Enter Updated Full Name: ";
                cin.ignore();
                getline(cin, student->name);
                cout << endl << "---         [ Student Name Updated ]        ---" << endl << endl;
                break;
            case 2:
                cout << "> Enter Updated Student ID: ";
                cin.ignore();
                getline(cin, student->id);
                cout << endl << "---          [ Student ID Updated ]         ---" << endl << endl;
                break;
            case 3:
            	cout << "> Enter Updated Mobile Number: ";
                cin.ignore();
                getline(cin, student->mobile);
                cout << endl << "---    [ Student Mobile Number Updated ]    ---" << endl << endl;
                break;
            case 4:
            	cout << "> Enter Updated Date of Birth (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, student->dob);
                cout << endl << "---        [ Date of Birth Updated ]        ---" << endl << endl;
                break;
            case 5:
                cout << "> Enter Updated Age: ";
                cin >> student->age;
                cout << endl << "---             [ Age Updated ]             ---" << endl << endl;
                break;
            case 6:
                cout << "> Enter Updated Sex (M/F): ";
                cin.ignore();
                getline(cin, student->sex);
                cout << endl << "---             [ Sex Updated ]             ---" << endl << endl;
                break;
            case 7:
                cout << "> Enter Updated Student Course: ";
                cin.ignore();
                getline(cin, student->course);
                cout << endl << "---        [ Student Course Updated ]       ---" << endl << endl;
                break;
            case 8: {
            	int yearLevel;
                cout << endl << "- [1] 1st, [2] 2nd, [3] 3rd, [4] 4th, [5] 5th: ";
                cout << "> Enter Updated Year Level: ";
                cin >> yearLevel;
                Student* updatedStudent = NULL;
                
                switch (yearLevel) {
                    case 1: updatedStudent = new FirstYear(student->name, student->id, student->mobile, student->dob, student->age, student->sex, student->course); break;
                    case 2: updatedStudent = new SecondYear(student->name, student->id, student->mobile, student->dob, student->age, student->sex, student->course); break;
                    case 3: updatedStudent = new ThirdYear(student->name, student->id, student->mobile, student->dob, student->age, student->sex, student->course); break;
                    case 4: updatedStudent = new FourthYear(student->name, student->id, student->mobile, student->dob, student->age, student->sex, student->course); break;
                    case 5: updatedStudent = new FifthYear(student->name, student->id, student->mobile, student->dob, student->age, student->sex, student->course); break;
                    default: 
                        cout << "---          [ Invalid Year Level ]         ---" << endl << endl;
                        continue;
                }
                
                delete students[index];
                students[index] = updatedStudent;
                cout << endl << "---          [ Year Level Updated ]         ---" << endl << endl;
                break;
			}
            default:
                cout << "---         [ Invalid Part Number ]         ---" << endl << endl;
                break;
        }
        save_records();
    }
}

    void prompt() const {
        cout << "---       [ Press Enter to Continue ]       ---" << endl;
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
        cerr << "-[ Error: Unable to open file(s) for reading ]-" << endl << endl;
        return;
    }

    string line;

    // Load undergraduate records
	while (getline(undergradFile, line)) {
	    istringstream iss(line);
	    string name, id, mobile, dob, ageStr, sex, course, yearLevelStr;
	
	    // Split the line into fields using comma as the delimiter
	    getline(iss, name, ',');
	    getline(iss, id, ',');
	    getline(iss, mobile, ',');
	    getline(iss, dob, ',');
	    getline(iss, ageStr, ',');
	    getline(iss, sex, ',');
	    getline(iss, course, ',');
	    getline(iss, yearLevelStr, ',');

	    // Convert year level and age string to integers
	    int yearLevel, age;
	    stringstream(ageStr) >> age;
	    stringstream(yearLevelStr) >> yearLevel;
	
	    // Add the student to the vector based on the year level
	    switch (yearLevel) {
	        case 1: students.push_back(new FirstYear(name, id, mobile, dob, age, sex, course)); break;
	        case 2: students.push_back(new SecondYear(name, id, mobile, dob, age, sex, course)); break;
	        case 3: students.push_back(new ThirdYear(name, id, mobile, dob, age, sex, course)); break;
	        case 4: students.push_back(new FourthYear(name, id, mobile, dob, age, sex, course)); break;
	        case 5: students.push_back(new FifthYear(name, id, mobile, dob, age, sex, course)); break;
	        default:
	            cerr << "Error: Invalid year level for undergraduate student: " << line << endl;
	            break;
	    }
	}

    // Load graduate records
    while (getline(gradFile, line)) {
        istringstream iss(line);
        string name, id, mobile, dob, ageStr, sex, course;

        // Split the line into fields using comma as the delimiter
        getline(iss, name, ',');
	    getline(iss, id, ',');
	    getline(iss, mobile, ',');
	    getline(iss, dob, ',');
	    getline(iss, ageStr, ',');
	    getline(iss, sex, ',');
	    getline(iss, course, ',');

        // Convert age string to integer
        int age;
        stringstream(ageStr) >> age;

        // Add the graduate student to the vector
        students.push_back(new Graduate(name, id, mobile, dob, age, sex, course));
    }
    undergradFile.close();
    gradFile.close();
}

    void save_records() const {
    ofstream undergradFile(undergradFilename.c_str());
    ofstream gradFile(gradFilename.c_str());

    if (!undergradFile || !gradFile) {
        cerr << "---   [ Could not open file for writing ]   ---" << endl;
        return;
    }

    // Save undergraduate records
    for (size_t i = 0; i < students.size(); ++i) {
        const Student* student = students[i];
        // Check if the student is an undergraduate
        if (const FirstYear* fy = dynamic_cast<const FirstYear*>(student)) {
            undergradFile << student->name << "," << student->id << "," << student->mobile << "," << student->dob;
            undergradFile << "," << student->age << "," << student->sex << "," << student->course;
			undergradFile << "," << fy->getYearLevel() << endl; // Append year level
        } else if (const SecondYear* sy = dynamic_cast<const SecondYear*>(student)) {
        	undergradFile << student->name << "," << student->id << "," << student->mobile << "," << student->dob;
            undergradFile << "," << student->age << "," << student->sex << "," << student->course;
			undergradFile << "," << sy->getYearLevel() << endl; // Append year level
        } else if (const ThirdYear* ty = dynamic_cast<const ThirdYear*>(student)) {
        	undergradFile << student->name << "," << student->id << "," << student->mobile << "," << student->dob;
            undergradFile << "," << student->age << "," << student->sex << "," << student->course;
			undergradFile << "," << ty->getYearLevel() << endl; // Append year level
        } else if (const FourthYear* fy = dynamic_cast<const FourthYear*>(student)) {
        	undergradFile << student->name << "," << student->id << "," << student->mobile << "," << student->dob;
            undergradFile << "," << student->age << "," << student->sex << "," << student->course;
			undergradFile << "," << fy->getYearLevel() << endl; // Append year level
        } else if (const FifthYear* fy = dynamic_cast<const FifthYear*>(student)) {
        	undergradFile << student->name << "," << student->id << "," << student->mobile << "," << student->dob;
            undergradFile << "," << student->age << "," << student->sex << "," << student->course;
			undergradFile << "," << fy->getYearLevel() << endl; // Append year level
        }
    }

    // Save graduate records
    for (size_t i = 0; i < students.size(); ++i) {
        const Student* student = students[i];
        // Check if the student is a graduate
        if (dynamic_cast<const Graduate*>(student)) {
            gradFile << student->name << "," << student->id << "," << student->mobile << "," << student->dob;
            gradFile << "," << student->age << "," << student->sex << "," << student->course << endl;
        }
    }
    undergradFile.close();
    gradFile.close();
}

	void utilities_menu() {
	    int option;
	    cout << "-----------   [ UTILITIES MENU ]   ------------" << endl
	         << "--                                           --" << endl
	         << "--      [1] Check for Duplicate Records      --" << endl
	         << "--      [2] Return to Main Menu              --" << endl
             << "--                                           --" << endl
             << "-----------------------------------------------" << endl << endl;
		cout << "> Enter an option: ";
	    cin >> option;
	    cout << endl;
	
	    switch (option) {
	        case 1:
	            check_duplicate_records();
	            break;
	        case 2:
	            break;
	        default:
	            cout << "---            [ Invalid Option ]           ---" << endl << endl;
	            break;
	    }
	}

	void check_duplicate_records() {
	    cout << "---  [ Checking for Duplicate Records... ]  ---" << endl;
	    bool foundDuplicates = false;
	
	    // Create a vector to store the indices of duplicate records
	    vector<int> duplicateIndices;
	
	    // Iterate over the student records to check for duplicates
	    for (size_t i = 0; i < students.size(); ++i) {
	        for (size_t j = i + 1; j < students.size(); ++j) {
	            // Compare the name and ID of each pair of student records
	            if (students[i]->name == students[j]->name || students[i]->id == students[j]->id) {
	                // If a duplicate is found, add the index of both records to the duplicateIndices vector
	                duplicateIndices.push_back(i);
	                duplicateIndices.push_back(j);
	                foundDuplicates = true;
	            }
	        }
	    }
	
	    // If duplicates are found, prompt the user to choose one and select an action
	    if (foundDuplicates) {
	        cout << endl << "---       [ Duplicate records found ]       ---" << endl << endl;
	        for (size_t i = 0; i < duplicateIndices.size(); ++i) {
	            int idx = duplicateIndices[i];
	            cout << "- DUPLICATE RECORD [" << i + 1 << "]" << endl << endl;
	            cout << *students[idx] << endl;
	        }
	
	        int chosenIndex;
	        cout << "> Enter Record Number to Access: ";
	        cin >> chosenIndex;
	        cout << endl;
	
	        // Validate the chosen index
	        if (chosenIndex >= 1 && chosenIndex <= duplicateIndices.size()) {
	            int chosenRecordIndex = duplicateIndices[chosenIndex - 1];
	
	            int choice;
	            cout << "-----------------------------------------------" << endl << endl;
                cout << "- Choose Action for Selected Record: " << endl
	    			 << "  [1] Update Record" << endl
	    			 << "  [2] Delete Record" << endl
	    			 << "  [3] Done/Proceed" << endl << endl;
				cout << "> Enter Option: ";
	            cin >> choice;
	
	            switch (choice) {
	                case 1:
	                    update_record(chosenRecordIndex);
	                    save_records();
	                    break;
	                case 2:
	                    delete_record(chosenRecordIndex);
	                    save_records();
	                    break;
	                case 3:
	                    // Proceed without performing any action
	                    break;
	                default:
	                    cout << endl << "---            [ Invalid Option ]           ---" << endl << endl;
	                    break;
	            }
	        } else {
	            cout << "---            [ Invalid Index ]            --- " << endl << endl;
	        }
	    } else {
	        cout << endl << "---      [ No Duplicate Records Found ]     ---" << endl << endl;
	    }
	}

public:
    StudentMonitoringSystem() : adminU("admin"), adminP("12345"), undergradFilename("undergraduates.txt"), gradFilename("graduates.txt") {}

    void run() {
	    display_intro();
	    login();
	    load_records();
	    int option = 0;
	    while (option != 5) {
	        cout << "--------------   [ MAIN MENU ]   --------------" << endl
	             << "--                                           --" << endl
	             << "--      [1] Add Student Record               --" << endl
	             << "--      [2] View All Student Record          --" << endl
	             << "--      [3] Find Student Record              --" << endl
	             << "--      [4] Utilities                        --" << endl
	             << "--      [5] Exit Program                     --" << endl
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
	                utilities_menu();
	                prompt();
	                break;
	            case 5:
	                cout << "---           [ Exiting Program ]           ---" << endl;
	                break;
	            default:
	                cout << "---            [ Invalid Option ]           ---" << endl << endl;
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
