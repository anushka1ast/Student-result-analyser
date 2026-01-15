#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Student {
public:
    int roll;
    string name;
    vector<int> marks;
    int total;
    float percentage;
    char grade;

    void calculateResult() {
        total = 0;
        for (int m : marks)
            total += m;

        percentage = (float)total / marks.size();

        if (percentage >= 90)
            grade = 'A';
        else if (percentage >= 75)
            grade = 'B';
        else if (percentage >= 60)
            grade = 'C';
        else
            grade = 'F';
    }
};

vector<Student> students;
int subjects;

// Add student
void addStudent() {
    Student s;

    cout << "\nEnter roll number: ";
    cin >> s.roll;

    cin.ignore();
    cout << "Enter name: ";
    getline(cin, s.name);

    s.marks.resize(subjects);
    for (int i = 0; i < subjects; i++) {
        cout << "Marks of subject " << i + 1 << ": ";
        cin >> s.marks[i];
    }

    s.calculateResult();
    students.push_back(s);

    cout << "✅ Student added successfully!\n";
}

// Display all results
void displayResults() {
    if (students.empty()) {
        cout << "⚠ No student data available.\n";
        return;
    }

    cout << "\n------ STUDENT RESULTS ------\n";
    for (auto s : students) {
        cout << "Roll: " << s.roll
             << " | Name: " << s.name
             << " | Total: " << s.total
             << " | Percentage: " << s.percentage
             << "% | Grade: " << s.grade << endl;
    }
}

// Class analysis
void classAnalysis() {
    if (students.empty()) {
        cout << "⚠ No data available.\n";
        return;
    }

    float avg = 0;
    int pass = 0, fail = 0;

    for (auto s : students) {
        avg += s.percentage;
        if (s.grade != 'F')
            pass++;
        else
            fail++;
    }

    cout << "\nClass Average Percentage: " << avg / students.size() << endl;
    cout << "Pass Students: " << pass << endl;
    cout << "Fail Students: " << fail << endl;
}

// Show topper
void showTopper() {
    if (students.empty()) {
        cout << "⚠ No data available.\n";
        return;
    }

    sort(students.begin(), students.end(),
         [](Student a, Student b) {
             return a.percentage > b.percentage;
         });

    cout << "\n🏆 Topper: " << students[0].name
         << " (" << students[0].percentage << "%)\n";
}

// 🔍 Search student by roll number
void searchStudent() {
    if (students.empty()) {
        cout << "⚠ No student data available.\n";
        return;
    }

    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    bool found = false;
    for (auto s : students) {
        if (s.roll == roll) {
            cout << "\n✅ Student Found!\n";
            cout << "Roll: " << s.roll << endl;
            cout << "Name: " << s.name << endl;
            cout << "Total: " << s.total << endl;
            cout << "Percentage: " << s.percentage << "%" << endl;
            cout << "Grade: " << s.grade << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "❌ Student not found.\n";
    }
}

// Save results to file
void saveToFile() {
    if (students.empty()) {
        cout << "⚠ No data to save.\n";
        return;
    }

    ofstream file("results.txt");

    file << "----- STUDENT RESULTS -----\n";
    for (auto s : students) {
        file << "Roll: " << s.roll
             << " | Name: " << s.name
             << " | Total: " << s.total
             << " | Percentage: " << s.percentage
             << "% | Grade: " << s.grade << "\n";
    }

    file.close();
    cout << "✅ Results saved to results.txt successfully!\n";
}

int main() {
    int choice;

    cout << "Enter number of subjects: ";
    cin >> subjects;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display Results\n";
        cout << "3. Class Analysis\n";
        cout << "4. Show Topper\n";
        cout << "5. Search Student by Roll\n";
        cout << "6. Save Results to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayResults();
                break;
            case 3:
                classAnalysis();
                break;
            case 4:
                showTopper();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                cout << "👋 Exiting program. Bye!\n";
                break;
            default:
                cout << "❌ Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
