#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//***************************************************************
// CLASSES WITH CSV SERIALIZATION
//****************************************************************
class Book {
    string bno;
    string bname;
    string aname;

public:
    void create_book() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "Enter The book no: ";
        getline(cin >> ws, bno); 
        cout << "Enter The Name of The Book: ";
        getline(cin, bname);
        cout << "Enter The Author's Name: ";
        getline(cin, aname);

        // Sanitize input to prevent CSV breakage
        replace(bname.begin(), bname.end(), ',', ' ');
        replace(aname.begin(), aname.end(), ',', ' ');

        cout << "\n\nBook Created Successfully...";
    }

    void show_book() const {
        cout << "\nBook no. : " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nAuthor Name: " << aname << endl;
    }

    void modify_book() {
        cout << "\nBook no. : " << bno;
        cout << "\nModify Book Name: ";
        getline(cin >> ws, bname);
        cout << "Modify Author's Name: ";
        getline(cin, aname);

        replace(bname.begin(), bname.end(), ',', ' ');
        replace(aname.begin(), aname.end(), ',', ' ');
    }

    string retbno() const { return bno; }
    string retbname() const { return bname; } // Added for sorting

    void report() const {
        cout << setw(15) << left << bno << setw(30) << left << bname << setw(30) << left << aname << endl;
    }

    string to_csv() const {
        return bno + "," + bname + "," + aname;
    }

    void from_csv(const string& line) {
        stringstream ss(line);
        getline(ss, bno, ',');
        getline(ss, bname, ',');
        getline(ss, aname, ',');
    }
};

class Student {
    string admno;
    string name;
    string stbno;
    int token;

public:
    void create_student() {
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "Enter The admission no: ";
        getline(cin >> ws, admno);
        cout << "Enter The Name of The Student: ";
        getline(cin, name);
        
        replace(name.begin(), name.end(), ',', ' ');

        token = 0;
        stbno = "NULL"; 
        cout << "\n\nStudent Record Created...";
    }

    void show_student() const {
        cout << "\nAdmission no. : " << admno;
        cout << "\nStudent Name : " << name;
        cout << "\nNo of Book issued : " << token;
        if (token == 1) cout << "\nBook No " << stbno << endl;
    }

    void modify_student() {
        cout << "\nAdmission no. : " << admno;
        cout << "\nModify Student Name: ";
        getline(cin >> ws, name);
        replace(name.begin(), name.end(), ',', ' ');
    }

    string retadmno() const { return admno; }
    string retname() const { return name; } // Added for sorting
    string retstbno() const { return stbno; }
    int rettoken() const { return token; }
    
    void addtoken() { token = 1; }
    void resettoken() { token = 0; }
    void getstbno(string t) { stbno = t; }

    void report() const {
        cout << setw(15) << left << admno << setw(25) << left << name << setw(15) << left << token << endl;
    }

    string to_csv() const {
        return admno + "," + name + "," + to_string(token) + "," + stbno;
    }

    void from_csv(const string& line) {
        stringstream ss(line);
        string token_str;
        
        getline(ss, admno, ',');
        getline(ss, name, ',');
        getline(ss, token_str, ',');
        getline(ss, stbno, ',');
        
        token = token_str.empty() ? 0 : stoi(token_str);
    }
};

//***************************************************************
// GLOBAL IN-MEMORY HASH TABLES (O(1) Lookups)
//****************************************************************
unordered_map<string, Book> books;
unordered_map<string, Student> students;

//***************************************************************
// FILE I/O - CSV PARSING
//****************************************************************
void load_data() {
    string line;
    
    fstream fp("book.csv", ios::in);
    if (fp.is_open()) {
        while (getline(fp, line)) {
            if (!line.empty()) {
                Book b;
                b.from_csv(line);
                books[b.retbno()] = b; 
            }
        }
        fp.close();
    }

    fstream fp2("student.csv", ios::in);
    if (fp2.is_open()) {
        while (getline(fp2, line)) {
            if (!line.empty()) {
                Student s;
                s.from_csv(line);
                students[s.retadmno()] = s; 
            }
        }
        fp2.close();
    }
}

void save_books() {
    fstream fp("book.csv", ios::out | ios::trunc);
    for (const auto& pair : books) {
        fp << pair.second.to_csv() << "\n";
    }
    fp.close();
}

void save_students() {
    fstream fp("student.csv", ios::out | ios::trunc);
    for (const auto& pair : students) {
        fp << pair.second.to_csv() << "\n";
    }
    fp.close();
}

//***************************************************************
// ADMINISTRATOR CRUD OPERATIONS
//****************************************************************
void write_book() {
    Book b;
    b.create_book();
    books[b.retbno()] = b; 
    save_books();
}

void write_student() {
    Student s;
    s.create_student();
    students[s.retadmno()] = s; 
    save_students();
}

void display_sps(string n) {
    cout << "\nSTUDENT DETAILS\n";
    if (students.find(n) != students.end()) { 
        students[n].show_student();
    } else {
        cout << "\n\nStudent does not exist";
    }
}

void display_spb(string n) {
    cout << "\nBOOK DETAILS\n";
    if (books.find(n) != books.end()) { 
        books[n].show_book();
    } else {
        cout << "\n\nBook does not exist";
    }
}

void modify_student() {
    string n;
    cout << "\n\n\tMODIFY STUDENT RECORD... ";
    cout << "\n\n\tEnter The admission no. of The student: ";
    getline(cin >> ws, n);

    if (students.find(n) != students.end()) {
        students[n].show_student();
        cout << "\nEnter The New Details of student" << endl;
        students[n].modify_student();
        save_students();
        cout << "\n\n\t Record Updated";
    } else {
        cout << "\n\n Record Not Found ";
    }
}

void modify_book() {
    string n;
    cout << "\n\n\tMODIFY BOOK RECORD.... ";
    cout << "\n\n\tEnter The book no: ";
    getline(cin >> ws, n);

    if (books.find(n) != books.end()) {
        books[n].show_book();
        cout << "\nEnter The New Details of book" << endl;
        books[n].modify_book();
        save_books();
        cout << "\n\n\t Record Updated";
    } else {
        cout << "\n\n Record Not Found ";
    }
}

void delete_student() {
    string n;
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete: ";
    getline(cin >> ws, n);

    if (students.erase(n)) { 
        save_students();
        cout << "\n\n\tRecord Deleted ..";
    } else {
        cout << "\n\nRecord not found";
    }
}

void delete_book() {
    string n;
    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The Book no. You Want To Delete: ";
    getline(cin >> ws, n);

    if (books.erase(n)) {
        save_books();
        cout << "\n\n\tRecord Deleted ..";
    } else {
        cout << "\n\nRecord not found";
    }
}

void display_alls() {
    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "==================================================================\n";
    cout << setw(15) << left << "Admission No." << setw(25) << left << "Name" << setw(15) << left << "Book Issued\n";
    cout << "==================================================================\n";
    
    // Convert map to vector for sorting
    vector<Student> temp_students;
    for (const auto& pair : students) {
        temp_students.push_back(pair.second);
    }

    // Sort alphabetically by Student Name
    sort(temp_students.begin(), temp_students.end(), [](const Student& a, const Student& b) {
        return a.retname() < b.retname();
    });

    // Display
    for (const Student& s : temp_students) {
        s.report();
    }
}

void display_allb() {
    cout << "\n\n\t\tBOOK LIST\n\n";
    cout << "================================================================================\n";
    cout << setw(15) << left << "Book Number" << setw(30) << left << "Book Name" << setw(30) << left << "Author\n";
    cout << "================================================================================\n";
    
    // Convert map to vector for sorting
    vector<Book> temp_books;
    for (const auto& pair : books) {
        temp_books.push_back(pair.second);
    }

    // Sort alphabetically by Book Name
    sort(temp_books.begin(), temp_books.end(), [](const Book& a, const Book& b) {
        return a.retbname() < b.retbname(); 
    });

    // Display
    for (const Book& b : temp_books) {
        b.report();
    }
}

//***************************************************************
// TRANSACTIONS
//****************************************************************
void book_issue() {
    string sn, bn;
    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The student's admission no: ";
    getline(cin >> ws, sn);

    if (students.find(sn) != students.end()) {
        if (students[sn].rettoken() == 0) {
            cout << "\n\n\tEnter the book no: ";
            getline(cin >> ws, bn);

            if (books.find(bn) != books.end()) {
                books[bn].show_book();
                students[sn].addtoken();
                students[sn].getstbno(bn);
                save_students(); 
                cout << "\n\n\t Book issued successfully\n\nPlease Note: Submit within 15 days.";
            } else {
                cout << "\nBook no does not exist";
            }
        } else {
            cout << "\nYou have not returned the last book";
        }
    } else {
        cout << "\nStudent record not exist...";
    }
}

void book_deposit() {
    string sn;
    int day, fine;
    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The student's admission no: ";
    getline(cin >> ws, sn);

    if (students.find(sn) != students.end()) {
        if (students[sn].rettoken() == 1) {
            string borrowed_book = students[sn].retstbno();
            
            if (books.find(borrowed_book) != books.end()) {
                books[borrowed_book].show_book();
                cout << "\n\nBook deposited in no. of days: ";
                cin >> day;
                if (day > 15) {
                    fine = (day - 15) * 1;
                    cout << "\n\nFine has to deposited Rs. " << fine;
                }
                students[sn].resettoken();
                students[sn].getstbno("NULL");
                save_students();
                cout << "\n\n\t Book deposited successfully";
            }
        } else {
            cout << "\nNo book is issued..please check!!";
        }
    } else {
        cout << "\nStudent record not exist...";
    }
}

//***************************************************************
// MENUS
//****************************************************************
void admin_menu() {
    string ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout << "\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\t5.DELETE STUDENT RECORD";
    cout << "\n\t6.CREATE BOOK ";
    cout << "\n\t7.DISPLAY ALL BOOKS ";
    cout << "\n\t8.DISPLAY SPECIFIC BOOK ";
    cout << "\n\t9.MODIFY BOOK ";
    cout << "\n\t10.DELETE BOOK ";
    cout << "\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11): ";
    getline(cin >> ws, ch2);

    if (ch2 == "1") write_student();
    else if (ch2 == "2") display_alls();
    else if (ch2 == "3") {
        string num;
        cout << "\n\n\tPlease Enter The Admission No: ";
        getline(cin >> ws, num);
        display_sps(num);
    }
    else if (ch2 == "4") modify_student();
    else if (ch2 == "5") delete_student();
    else if (ch2 == "6") write_book();
    else if (ch2 == "7") display_allb();
    else if (ch2 == "8") {
        string num;
        cout << "\n\n\tPlease Enter The book No: ";
        getline(cin >> ws, num);
        display_spb(num);
    }
    else if (ch2 == "9") modify_book();
    else if (ch2 == "10") delete_book();
    else if (ch2 == "11") return;
    else cout << "\aInvalid choice.";

    admin_menu(); 
}

int main() {
    load_data(); 

    string ch;
    do {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. BOOK ISSUE";
        cout << "\n\t2. BOOK DEPOSIT";
        cout << "\n\t3. ADMINISTRATOR MENU";
        cout << "\n\t4. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-4): ";
        getline(cin >> ws, ch);

        if (ch == "1") book_issue();
        else if (ch == "2") book_deposit();
        else if (ch == "3") admin_menu();
        else if (ch == "4") cout << "\nExiting Library System...\n";
        else cout << "\aInvalid Selection";
        
    } while (ch != "4");
    
    return 0;
}