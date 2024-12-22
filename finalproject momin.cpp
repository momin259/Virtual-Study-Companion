#include <iostream> // Include input-output stream library
#include <string>   // Include string handling library
#include <map>      // Include map for key-value storage
#include <iomanip>  // Include iomanip for formatting output
using namespace std; // Use standard namespace

// Base Class: User
class User {
protected:
    string name;   // Protected attribute: User's name
    int age;       // Protected attribute: User's age
    string email;  // Protected attribute: User's email

public:
    virtual void login() { // Virtual function for polymorphic behavior
        cout << "Enter your name: "; // Prompt for user's name
        cin >> name; 
        cout << "Enter your age: "; // Prompt for user's age
        cin >> age; 
        cout << "Enter your email: "; // Prompt for user's email
        cin >> email; 
        cout << "Login successful for " << name << "!\n"; // Confirm login
    }

    void logout() { // Function to logout the user
        cout << "User " << name << " logged out successfully.\n";
    }

    void updateProfile() { // Function to update user's profile
        cout << "Update Profile:\n";
        cout << "Enter new name: "; // Prompt for new name
        cin >> name;
        cout << "Enter new age: "; // Prompt for new age
        cin >> age;
        cout << "Enter new email: "; // Prompt for new email
        cin >> email;
        cout << "Profile updated successfully.\n"; // Confirm profile update
    }

    friend class QuizMaster; // Friend class declaration for QuizMaster
};

// Derived Class: ScheduleManager (inherits from User)
class ScheduleManager : public User {
private:
    string studyPlan[10]; // Array to store up to 10 study topics
    int scheduleCount = 0; // Counter for number of schedules

public:
    void createSchedule() { // Function to create a new schedule
        if (scheduleCount < 10) { // Check if schedule array is not full
            cout << "Enter topic for schedule: ";
            cin.ignore(); // Clear the input buffer
            getline(cin, studyPlan[scheduleCount]); // Store schedule
            scheduleCount++; // Increment schedule counter
            cout << "Schedule added successfully.\n"; // Confirm addition
        } else {
            cout << "Schedule is full.\n"; // Notify if full
        }
    }

    void viewSchedule() { // Function to view all schedules
        if (scheduleCount == 0) { // Check if there are no schedules
            cout << "No schedules available.\n"; // Notify no schedules
            return; // Exit function
        }
        cout << "Your Schedule:\n";
        for (int i = 0; i < scheduleCount; i++) { // Loop through schedules
            cout << i + 1 << ". " << studyPlan[i] << endl; // Display each schedule
        }
    }

    void modifySchedule() { // Function to modify an existing schedule
        viewSchedule(); // Display current schedules
        if (scheduleCount == 0) return; // Exit if no schedules

        int index;
        cout << "Enter the schedule number to modify: "; // Prompt for schedule number
        cin >> index; 
        if (index <= 0 || index > scheduleCount) { // Validate input
            cout << "Invalid schedule number.\n"; // Notify invalid input
            return; // Exit function
        }
        cout << "Enter the new topic: "; // Prompt for new topic
        cin.ignore(); // Clear the input buffer
        getline(cin, studyPlan[index - 1]); // Update the topic
        cout << "Schedule updated successfully.\n"; // Confirm modification
    }
};

// Derived Class: ProgressTracker (inherits from User)
class ProgressTracker : public User {
private:
    string completedTopics[10]; // Array to store completed topics
    int totalTopics = 10;       // Total number of topics
    int completedCount = 0;     // Counter for completed topics

public:
    void logProgress() { // Function to log a completed topic
        if (completedCount >= totalTopics) { // Check if all topics are completed
            cout << "All topics completed!\n"; // Notify completion
            return; // Exit function
        }
        cout << "Enter the completed topic: "; // Prompt for completed topic
        cin.ignore(); // Clear the input buffer
        getline(cin, completedTopics[completedCount]); // Store completed topic
        completedCount++; // Increment completed counter
        cout << "Progress updated successfully.\n"; // Confirm update
    }

    void viewProgress() { // Function to view progress
        cout << "Progress: " << completedCount << "/" << totalTopics << " topics completed.\n"; // Display progress
        cout << "Completion Percentage: " << (completedCount * 100.0 / totalTopics) << "%\n"; // Display percentage
    }

    void generateReport() { // Function to generate progress report
        cout << "Study Progress Report:\n";
        for (int i = 0; i < completedCount; i++) { // Loop through completed topics
            cout << i + 1 << ". " << completedTopics[i] << endl; // Display each completed topic
        }
        cout << "Total Progress: " << completedCount << "/" << totalTopics << " topics.\n"; // Display total progress
    }
};

// Friend Class: QuizMaster
class QuizMaster {
private:
    map<string, string> questionBank; // Map to store questions and answers
    string currentTopic; // Current topic for the quiz

public:
    void addQuestion() { // Function to add a new question
        string question, answer;
        cout << "Enter the topic for the question: "; // Prompt for topic
        cin.ignore(); // Clear the input buffer
        getline(cin, currentTopic); 
        cout << "Enter the question: "; // Prompt for question
        getline(cin, question);
        cout << "Enter the answer: "; // Prompt for answer
        getline(cin, answer);
        questionBank[question] = answer; // Add question and answer to map
        cout << "Question added successfully.\n"; // Confirm addition
    }

    void createQuiz() { // Function to create a quiz
        if (questionBank.empty()) { // Check if question bank is empty
            cout << "No questions available for quiz.\n"; // Notify empty bank
            return; // Exit function
        }
        cout << "Quiz for Topic: " << currentTopic << "\n";
        for (const auto& q : questionBank) { // Loop through questions
            cout << "Q: " << q.first << "\nYour Answer: ";
            string userAnswer;
            getline(cin, userAnswer); // Get user's answer
            cout << "Correct Answer: " << q.second << "\n\n"; // Display correct answer
        }
    }
};

// Composition Example: VSCS Class
class VSCS {
private:
    User* user;                // Pointer to base class User
    ScheduleManager scheduleManager; // Composition: ScheduleManager
    ProgressTracker progressTracker; // Composition: ProgressTracker
    QuizMaster quizMaster;          // Composition: QuizMaster

public:
    VSCS() : user(nullptr) {} // Constructor initializing user to null

    void menu() { // Main menu function
        int choice;
        do {
            cout << "\n---- Virtual Study Companion System ----\n";
            cout << "1. Login\n";
            cout << "2. Create Schedule\n";
            cout << "3. View Schedule\n";
            cout << "4. Modify Schedule\n";
            cout << "5. Log Progress\n";
            cout << "6. View Progress\n";
            cout << "7. Generate Report\n";
            cout << "8. Add Quiz Question\n";
            cout << "9. Take Quiz\n";
            cout << "10. Logout\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) { // Handle menu options
                case 1:
                    user = &scheduleManager; // Assign user to ScheduleManager
                    user->login(); // Call login function
                    break;
                case 2:
                    scheduleManager.createSchedule(); // Create a schedule
                    break;
                case 3:
                    scheduleManager.viewSchedule(); // View schedules
                    break;
                case 4:
                    scheduleManager.modifySchedule(); // Modify a schedule
                    break;
                case 5:
                    progressTracker.logProgress(); // Log progress
                    break;
                case 6:
                    progressTracker.viewProgress(); // View progress
                    break;
                case 7:
                    progressTracker.generateReport(); // Generate report
                    break;
                case 8:
                    quizMaster.addQuestion(); // Add quiz question
                    break;
                case 9:
                    quizMaster.createQuiz(); // Take quiz
                    break;
                case 10:
                    user->logout(); // Logout user
                    user = nullptr; // Reset user pointer
                    break;
                case 0:
                    cout << "Exiting system. Goodbye!\n"; // Exit system
                    break;
                default:
                    cout << "Invalid choice. Try again.\n"; // Invalid input
            }
        } while (choice != 0); // Repeat menu until exit
    }
};

// Main Function
int main() {
    VSCS vscs; // Create VSCS object
    vscs.menu(); // Call menu to start the program
    return 0; // Exit program
}