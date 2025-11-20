#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Константы
const int MONTHS_PER_ROW = 4;
const int TOTAL_MONTHS = 12;
const int DAYS_IN_WEEK = 7;
const int MAX_WEEKS = 6;

// Проверка на високосный год
bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// Количество дней в месяце
int getDaysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

// Название месяца
string getMonthName(int month) {
    string names[] = {"January", "February", "March", "April", "May", "June",
                     "July", "August", "September", "October", "November", "December"};
    return names[month - 1];
}

// День недели 1 января 
int getFirstDayOfYear(int year) {
    int day = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    return day;
}

int main() {
    int year;
    cout << "Enter year: ";
    cin >> year;
    
    cout << "\n" << setw(40) << "CALENDAR FOR " << year << "\n\n";
    
    int firstDay = getFirstDayOfYear(year);
    
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 4; ++column) {
            int month = row * 4 + column + 1;
            cout << setw(20) << getMonthName(month) << "  ";
        }
        cout << "\n";
        
        for (int column = 0; column < 4; ++column) {
            cout << " Su Mo Tu We Th Fr Sa  ";
        }
        cout << "\n";
        
        int startDay[4];
        int daysInMonth[4];
        for (int column = 0; column < 4; ++column) {
            int month = row * 4 + column + 1;
            daysInMonth[column] = getDaysInMonth(month, year);
            
            if (column == 0) {
                startDay[column] = firstDay;
            } else {
                startDay[column] = (startDay[column-1] + daysInMonth[column-1]) % 7;
            }
        }
        
        for (int week = 0; week < 6; ++week) {
            for (int column = 0; column < 4; ++column) {
                int dayNumber = week * 7 - startDay[column] + 1;
                
                for (int dayOfWeek = 0; dayOfWeek < 7; ++dayOfWeek) {
                    int currentDay = dayNumber + dayOfWeek;
                    
                    if (currentDay > 0 && currentDay <= daysInMonth[column]) {
                        cout << setw(3) << currentDay;
                    } else {
                        cout << "   ";
                    }
                }
                cout << "  ";
            }
            cout << "\n";
        }
        cout << "\n";
        
        int lastMonthInRow = row * 4 + 4;
        firstDay = (firstDay + getDaysInMonth(lastMonthInRow, year)) % 7;
        for (int monthInRow = row * 4 + 1; monthInRow < lastMonthInRow; ++monthInRow) {
            firstDay = (firstDay + getDaysInMonth(monthInRow, year)) % 7;
        }
    }
    
    return 0;
}