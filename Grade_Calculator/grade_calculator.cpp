// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    double exam_total = 0;
    double exam_count =0;
    double final_exam = 0;
    double hw_total = 0;
    int hw_count = 0;
    double lw_total = 0;
    int lw_count = 0;
    double reading_total = 0;
    int reading_count = 0;
    double engagement_total = 0;
    int engagement_count = 0;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exam_total += score;
            exam_count += 1;
        } else if (category == "final-exam") {
            final_exam += score;
            exam_count += 1;
        } else if (category == "hw") {
            hw_total += score;
            hw_count += 1;
        } else if (category == "lw") {
            if(score > 0) {
                lw_total += 1;
            }
            lw_count += 1;
        } else if (category == "reading") {
            reading_total += score;
            reading_count += 1;
        } else if (category == "engagement") {
            engagement_total += score;
            engagement_count += 1;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = (exam_total + final_exam) / 3;
    if (exam_average < final_exam) {
        exam_average = final_exam;
    }
    double hw_average = hw_total / hw_count;
    double lw_average = lw_total / lw_count;
    lw_average *= 100;
    double reading_average = (reading_total / reading_count) + 15;
    if (reading_average >= 100) {
        reading_average = 100;
    }
    double engagement_average = (engagement_total / engagement_count) + 15;
    if (engagement_average >= 100) {
        engagement_average = 100;
    }

    // TODO(student): compute weighted total of components
    double exam_weight = (exam_average / 100) * 40;
    double hw_weight = (hw_average / 100) * 40;
    double lw_weight = (lw_average / 100) * 10;
    double reading_weight = (reading_average / 100) * 5;
    double engagement_weight = (engagement_average / 100) * 5;
    double weighted_total = 0;

    if(exam_count == 0) {
        exam_average = 0;
    }
    else {
        weighted_total += exam_weight;
    }
    if(hw_count == 0) {
        hw_average = 0;
    }
    else {
        weighted_total += hw_weight;
    }
    if(lw_count == 0) {
        lw_average = 0;
    }
    else {
        weighted_total += lw_weight;
    }
    if(reading_count == 0) {
        reading_average = 15;
        weighted_total += (reading_average/100) * 5;
    }
    else {
        weighted_total += reading_weight;
    }
    if(engagement_count == 0) {
        engagement_average = 15;
        weighted_total += (engagement_average/100) * 5;
    }
    else {
        weighted_total += engagement_weight;
    }

    char final_letter_grade = 'X';
    if (weighted_total >= 90) {
        final_letter_grade = 'A';
    }
    else if (weighted_total >= 80) {
        final_letter_grade = 'B';
    }
    else if (weighted_total >= 70) {
        final_letter_grade = 'C';
    }
    else if (weighted_total >= 60) {
        final_letter_grade = 'D';
    }
    else {
        final_letter_grade = 'F';
    }
    
    print_results(
        exam_average, hw_average, lw_average, reading_average, 
        engagement_average, weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
