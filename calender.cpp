#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class CalendarPrinter {
private:
    static const vector<string> MONTH_NAMES;
    static const vector<string> WEEK_NAMES;
    
public:
    static void printYearCalendar(int year) {
        cout << "\n" << string(80, '=') << endl;
        cout << "                           " << year << "������" << endl;
        cout << string(80, '=') << endl;
        
        // ÿ�д�ӡ4���£���3��
        for (int row = 0; row < 3; row++) {
            vector<int> monthIndices = {
                row * 4, 
                row * 4 + 1, 
                row * 4 + 2, 
                row * 4 + 3
            };
            
            printMonthTitles(monthIndices);
            printWeekHeaders(monthIndices);
            printMonthContents(year, monthIndices);
            
            // �·�֮��ļ��
            if (row < 2) {
                cout << "\n" << string(80, '-') << "\n" << endl;
            }
        }
    }
    
private:
    /**
     * ��ӡ�·ݱ�����
     */
    static void printMonthTitles(const vector<int>& monthIndices) {
        for (int monthIndex : monthIndices) {
            string title = MONTH_NAMES[monthIndex];
            cout << centerString(title, 20);
        }
        cout << endl;
    }
    
    /**
     * ��ӡ���ڱ�����
     */
    static void printWeekHeaders(const vector<int>& monthIndices) {
        for (size_t i = 0; i < monthIndices.size(); i++) {
            for (const string& dayName : WEEK_NAMES) {
                cout << dayName << " ";
            }
            cout << "  "; // �·�֮��ļ��
        }
        cout << endl;
    }
    
    /**
     * ��ӡ�·���������
     */
    static void printMonthContents(int year, const vector<int>& monthIndices) {
        vector<pair<int, int>> monthData; // [firstDay, totalDays]
        
        for (int monthIndex : monthIndices) {
            int firstDay = getFirstDayOfWeek(year, monthIndex);
            int totalDays = getDaysInMonth(year, monthIndex);
            monthData.push_back({firstDay, totalDays});
        }
        
        // �����Ҫ6������ʾһ���µ���������
        for (int weekRow = 0; weekRow < 6; weekRow++) {
            for (size_t i = 0; i < monthIndices.size(); i++) {
                printWeekRow(year, monthIndices[i], weekRow, 
                           monthData[i].first, monthData[i].second);
                cout << "  "; // �·�֮��ļ��
            }
            cout << endl;
        }
    }
    
    /**
     * ��ӡһ���µ�ĳһ������
     */
    static void printWeekRow(int year, int month, int weekRow, 
                           int firstDay, int totalDays) {
        int startDay = weekRow * 7 - firstDay + 1;
        
        for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
            int currentDay = startDay + dayOfWeek;
            
            if (currentDay <= 0 || currentDay > totalDays) {
                // ���ڱ��·�Χ�ڵ����ڴ�ӡ�ո�
                cout << "  ";
            } else {
                // �������ڱ�ǣ���ĩ��
                if (isWeekend(year, month, currentDay)) {
                    // ��֧��ANSI��ɫ���ն�����ʾ��ɫ
                    // cout << "\033[31m";
                }
                
                // ��ӡ���ڣ�����2�ַ����
                cout << setw(2) << currentDay;
                
                if (isWeekend(year, month, currentDay)) {
                    // cout << "\033[0m"; // ������ɫ
                }
            }
            
            // ����֮��Ŀո�
            if (dayOfWeek < 6) {
                cout << " ";
            }
        }
    }
    
    /**
     * ��ȡ�·ݵĵ�һ�������ڼ���0=����, 1=��һ, ..., 6=������
     */
    static int getFirstDayOfWeek(int year, int month) {
        tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month;
        timeinfo.tm_mday = 1;
        mktime(&timeinfo);
        return timeinfo.tm_wday; // ����=0, ��һ=1, ..., ����=6
    }
    
    /**
     * ��ȡ�·ݵ�������
     */
    static int getDaysInMonth(int year, int month) {
        tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month + 1; // �¸��µĵ�0����Ǳ��µ����һ��
        timeinfo.tm_mday = 0;
        mktime(&timeinfo);
        return timeinfo.tm_mday;
    }
    
    /**
     * �ж��Ƿ�Ϊ��ĩ�����������գ�
     */
    static bool isWeekend(int year, int month, int day) {
        tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month;
        timeinfo.tm_mday = day;
        mktime(&timeinfo);
        int dayOfWeek = timeinfo.tm_wday;
        return dayOfWeek == 0 || dayOfWeek == 6; // ����=0, ����=6
    }
    
    /**
     * �ַ���������ʾ
     */
    static string centerString(const string& text, int width) {
        if (text.length() >= width) {
            return text;
        }
        
        int padding = width - text.length();
        int leftPadding = padding / 2;
        int rightPadding = padding - leftPadding;
        
        return string(leftPadding, ' ') + text + string(rightPadding, ' ');
    }
};

// ��̬��Ա��ʼ��
const vector<string> CalendarPrinter::MONTH_NAMES = {
    "һ��", "����", "����", "����", "����", "����",
    "����", "����", "����", "ʮ��", "ʮһ��", "ʮ����"
};

const vector<string> CalendarPrinter::WEEK_NAMES = {
    "��", "һ", "��", "��", "��", "��", "��"
};

int main() {
    int year;
    
    cout << "���������: ";
    cin >> year;
    
    // ��֤���뷶Χ
    if (year < 1900 || year > 2100) {
        cout << "��ݱ�����1900��2100֮�䣡" << endl;
        return 1;
    }
    
    CalendarPrinter::printYearCalendar(year);
    
    return 0;
}
