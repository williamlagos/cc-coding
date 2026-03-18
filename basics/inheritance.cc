#include <iostream>
#include <vector>

class Person {
    protected:
        std::string firstName;
        std::string lastName;
        int id;
    public:
        Person(std::string firstName, std::string lastName, int identification)
            : firstName{std::move(firstName)}, lastName{std::move(lastName)}, id{identification} {}
        void printPerson() {
            std::cout << "Name: " << lastName << ", " << firstName << "\nID: " << id << "\n"; 
        }
};

class Student : public Person {
    private:
        std::vector<int> testScores;  
    public:
        /*	
        *   Class Constructor
        *   
        *   Parameters:
        *   firstName - A string denoting the Person's first name.
        *   lastName - A string denoting the Person's last name.
        *   id - An integer denoting the Person's ID number.
        *   scores - An array of integers denoting the Person's test scores.
        */
        // Write your constructor here
        Student(std::string firstName, std::string lastName, int id, std::vector<int> testScores) :
        Person(std::move(firstName), std::move(lastName), id), testScores{std::move(testScores)} {}

        /*	
        *   Function Name: calculate
        *   Return: A character denoting the grade.
        */
        // Write your function here
        char calculate() {
            char s = ' ';
            int sum = 0;
            int numScores = static_cast<int>(testScores.size());
            for (int score : testScores) sum += score;
            int avgScore = sum / numScores;
            if (avgScore >= 90 && avgScore <= 100) s = 'O';
            else if (avgScore >= 80 && avgScore < 90) s = 'E';
            else if (avgScore >= 70 && avgScore < 80) s = 'A';
            else if (avgScore >= 55 && avgScore < 70) s = 'P';
            else if (avgScore >= 40 && avgScore < 55) s = 'D';
            else if (avgScore < 40) s = 'T';
            return s;
        }
};

int main() {
    std::string firstName;
    std::string lastName;
    int id;
    int numScores;
    std::cin >> firstName >> lastName >> id >> numScores;
    std::vector<int> scores;
    for (int i = 0; i < numScores; i++) {
        int tmpScore;
        std::cin >> tmpScore;
        scores.push_back(tmpScore);
    }
    Student s(firstName, lastName, id, scores);
    s.printPerson();
    std::cout << "Grade: " << s.calculate() << "\n";
    return 0;
}