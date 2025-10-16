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
        cout << "                           " << year << "年日历" << endl;
        cout << string(80, '=') << endl;
        
        // 每行打印4个月，共3行
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
            
            // 月份之间的间隔
            if (row < 2) {
                cout << "\n" << string(80, '-') << "\n" << endl;
            }
        }
    }
    
private:
    /**
     * 打印月份标题行
     */
    static void printMonthTitles(const vector<int>& monthIndices) {
        for (int monthIndex : monthIndices) {
            string title = MONTH_NAMES[monthIndex];
            cout << centerString(title, 20);
        }
        cout << endl;
    }
    
    /**
     * 打印星期标题行
     */
    static void printWeekHeaders(const vector<int>& monthIndices) {
        for (size_t i = 0; i < monthIndices.size(); i++) {
            for (const string& dayName : WEEK_NAMES) {
                cout << dayName << " ";
            }
            cout << "  "; // 月份之间的间隔
        }
        cout << endl;
    }
    
    /**
     * 打印月份日期内容
     */
    static void printMonthContents(int year, const vector<int>& monthIndices) {
        vector<pair<int, int>> monthData; // [firstDay, totalDays]
        
        for (int monthIndex : monthIndices) {
            int firstDay = getFirstDayOfWeek(year, monthIndex);
            int totalDays = getDaysInMonth(year, monthIndex);
            monthData.push_back({firstDay, totalDays});
        }
        
        // 最多需要6行来显示一个月的所有日期
        for (int weekRow = 0; weekRow < 6; weekRow++) {
            for (size_t i = 0; i < monthIndices.size(); i++) {
                printWeekRow(year, monthIndices[i], weekRow, 
                           monthData[i].first, monthData[i].second);
                cout << "  "; // 月份之间的间隔
            }
            cout << endl;
        }
    }
    
    /**
     * 打印一个月的某一行日期
     */
    static void printWeekRow(int year, int month, int weekRow, 
                           int firstDay, int totalDays) {
        int startDay = weekRow * 7 - firstDay + 1;
        
        for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
            int currentDay = startDay + dayOfWeek;
            
            if (currentDay <= 0 || currentDay > totalDays) {
                // 不在本月范围内的日期打印空格
                cout << "  ";
            } else {
                // 特殊日期标记（周末）
                if (isWeekend(year, month, currentDay)) {
                    // 在支持ANSI颜色的终端中显示红色
                    // cout << "\033[31m";
                }
                
                // 打印日期，保持2字符宽度
                cout << setw(2) << currentDay;
                
                if (isWeekend(year, month, currentDay)) {
                    // cout << "\033[0m"; // 重置颜色
                }
            }
            
            // 日期之间的空格
            if (dayOfWeek < 6) {
                cout << " ";
            }
        }
    }
    
    /**
     * 获取月份的第一天是星期几（0=周日, 1=周一, ..., 6=周六）
     */
    static int getFirstDayOfWeek(int year, int month) {
        tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month;
        timeinfo.tm_mday = 1;
        mktime(&timeinfo);
        return timeinfo.tm_wday; // 周日=0, 周一=1, ..., 周六=6
    }
    
    /**
     * 获取月份的总天数
     */
    static int getDaysInMonth(int year, int month) {
        tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month + 1; // 下个月的第0天就是本月的最后一天
        timeinfo.tm_mday = 0;
        mktime(&timeinfo);
        return timeinfo.tm_mday;
    }
    
    /**
     * 判断是否为周末（周六或周日）
     */
    static bool isWeekend(int year, int month, int day) {
        tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month;
        timeinfo.tm_mday = day;
        mktime(&timeinfo);
        int dayOfWeek = timeinfo.tm_wday;
        return dayOfWeek == 0 || dayOfWeek == 6; // 周日=0, 周六=6
    }
    
    /**
     * 字符串居中显示
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

// 静态成员初始化
const vector<string> CalendarPrinter::MONTH_NAMES = {
    "一月", "二月", "三月", "四月", "五月", "六月",
    "七月", "八月", "九月", "十月", "十一月", "十二月"
};

const vector<string> CalendarPrinter::WEEK_NAMES = {
    "日", "一", "二", "三", "四", "五", "六"
};

int main() {
    int year;
    
    cout << "请输入年份: ";
    cin >> year;
    
    // 验证输入范围
    if (year < 1900 || year > 2100) {
        cout << "年份必须在1900到2100之间！" << endl;
        return 1;
    }
    
    CalendarPrinter::printYearCalendar(year);
    
    return 0;
}
