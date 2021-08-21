#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>


using namespace std;

//#define DEBUG   (1)

static string InformatMonth;
static string InformatDay;
static string BS_year;
static string BS_month;
static string BS_day;
static bool CorrectMonthSet = false;
static bool CorrectDaySet = false;
static bool YearSet = false;
static int NumberCounter;

bool IsNum(const char &c)
{
    if (c >= '0' && c <= '9')
    {
    #if DEBUG 
        cout << "IS NUM: " << c << endl;
    #endif
        return true;
    }
    else
    {
    #if DEBUG 
        cout << "IS NOT NUM: " << c << endl;
    #endif
        return false;
    }
}

bool CheckNum(const char &c, bool &num_sign, bool &num_valid_flag, bool &num_set)
{
    bool res = true;
    if (num_sign == false)
    {
        if (c == '+' || c == '-')
        {
            num_sign = true;
            return res;
        }
        else if (IsNum(c))
        {
			if (num_set == false)
			{
				NumberCounter++;
			}
            num_set = true;
            num_sign = true;
            return res;
        }
        else
        {
            res = false;
            return res;
        }
    }
    else if (IsNum(c))
    {
		if (num_set == false)
		{
			NumberCounter++;
		}
        num_set = true;
        num_sign = true;
        return res;
    }
    else if (c == '-' && num_set == true)
    {
		if (NumberCounter >= 3)
		{
			res = false;
			num_set = false;
			num_sign = false;
			NumberCounter = 0;
		}
		else
		{
			num_valid_flag = true;
			num_set = false;
			num_sign = false;
		}
    }
    else
    {
        res = false;
    }
    return res;
}

void AddInMonth(const char &ch)
{
    CorrectMonthSet = true;
    #if DEBUG
    cout << "CHM: " << ch << endl;
    #endif
    BS_month += ch;
}

void AddInDay(const char &ch)
{
    CorrectDaySet = true;
    #if DEBUG
    cout << "CHD: " << ch << endl;
    #endif
    BS_day += ch;
}

void AddInYear(const char &ch)
{
    YearSet = true;
    #if DEBUG
    cout << "CHY: " << ch << endl;
    #endif
    BS_year += ch;
}

void EraseDayMonthBuffers(void)
{
    BS_month.erase();
    BS_day.erase();
    BS_year.erase();
    InformatDay.erase();
    InformatMonth.erase();
}

void ResetFlags(void)
{
    CorrectDaySet = false;
    CorrectMonthSet = false;
    YearSet = false;
}

bool CheckDateFormat(string &str)
{
    bool res = true;
    bool num_sign = false, num_set = false;
    bool year_valid = false, month_valid = false, day_valid = false, char_valid = false;
    bool m_set_one_none_zero, d_set_one_none_zero = false, y_set_one_none_zero = false;
    
    for (const auto &ch : str)
    {
        if (res == false)
        {
            break;
        }
        if (year_valid == false)
        {
            res = CheckNum(ch, num_sign, year_valid, num_set);
            if (year_valid == false)
            {
                if (ch != '0' && ch != '+' && ch != '-')
                {
                    y_set_one_none_zero = true;
                    AddInYear(ch);
                }
                else if (y_set_one_none_zero == true)
                {
                    AddInYear(ch);
                }
            }
        }
        else if (month_valid == false)
        {
            res = CheckNum(ch, num_sign, month_valid, num_set);
            if (month_valid == false)
            {
                InformatMonth += ch;
                if (m_set_one_none_zero == false && ch != '0' && ch != '+')
                {
                    m_set_one_none_zero = true;
                    AddInMonth(ch);
                }
                else if (m_set_one_none_zero == true)
                {
                    AddInMonth(ch);
                }
            }
        }
        else if (day_valid == false)
        {
            res = CheckNum(ch, num_sign, day_valid, num_set);
            if (day_valid == false)
            {
                InformatDay += ch;
                if (d_set_one_none_zero == false && ch != '0' && ch != '+')
                {
                    d_set_one_none_zero = true;
                    AddInDay(ch);
                }
                else if (d_set_one_none_zero == true)
                {
                    AddInDay(ch);
                }
            }
        }
        else 
        {
            res = false;
        }
    }
#if DEBUG
    cout << "month: " << BS_month << "day: " << BS_day << endl;
#endif    
    if (YearSet == false)
    {
        BS_year = "0";
    }
    
    if (day_valid != true && year_valid != true && month_valid != true)
    {
        res = false;
    }
    
    if (res == false || NumberCounter != 3U)
    {
		res = false;
        cout << "Wrong date format: " << str << endl;
        EraseDayMonthBuffers();
        ResetFlags();
    }
    else if (CorrectMonthSet != true)
    {
        cout << "Month value is invalid: " << InformatMonth << endl;
        EraseDayMonthBuffers();
        ResetFlags();
        res = false;
    }
    else if (CorrectDaySet != true)
    {
        cout << "Day value is invalid: " << InformatDay << endl;
        EraseDayMonthBuffers();
        ResetFlags();
        res = false;
    }
	NumberCounter = 0;
    
    return res;
}

#if DEBUG
bool CheckDay(const string &day)
{
    bool num_sign = false, res = true;
    int digit_num = 0;
    char prev_digit;
    for (const auto &c : day)
    {
        if (digit_num == 0)
        {   
            if (IsNum(c))
            {
                digit_num++,
                num_sign = true;
                prev_digit = c;
            }
            else if (c == '+')
            {
                num_sign = true;
            }
            else
            {
                res = false;
                break;
            }
        }
        else if (digit_num == 1)
        {
            if (IsNum(c))
            {
                digit_num++;
                if (prev_digit == '3')
                {   
                    if (c > '1')
                    {
                        res = false;
                        break;
                    }
                }
                else if (prev_digit <= '2')
                {
                    continue;
                }
                else
                {
                    res = false;
                    break;
                }
            }
        }
        else
        {
            res = false;
            break;
        }
    }
    
    if (res == false)
    {
        cout << "Day value is invalid: " << day << endl;
    }
    
    
    return res;
}

bool CheckMonth(const string &month)
{
    bool num_sign = false, res = true;
    int digit_num = 0;
    char prev_digit;
    for (const auto &c : month)
    {
        if (digit_num == 0)
        {   
            if (IsNum(c))
            {
                digit_num++,
                num_sign = true;
                prev_digit = c;
            }
            else if (c == '+')
            {
                num_sign = true;
            }
            else
            {
                res = false;
                break;
            }
        }
        else if (digit_num == 1)
        {
            if (IsNum(c))
            {
                digit_num++;
                if (prev_digit != '1' || c > '2')
                {
                    res = false;
                    break;
                }
            }
        }
        else
        {
            res = false;
            break;
        }
    }
    
    if (res == false)
    {
        cout << "Month value is invalid: " << month << endl;
    }
    
    
    return res;
}
#endif

bool CheckMonthAndDay(void)
{
    bool res; 
	int month = stoi(BS_month);
   // cout << "Number month: " << month << endl;
	if (month < 13 && month > 0)
	{
		res = true;
		int day = stoi(BS_day);
		if (day > 31 || day < 1)
		{
			res = false;
            cout << "Day value is invalid: " << BS_day << endl;
		}
	}
	else
	{
		res = false;
        cout << "Month value is invalid: " << BS_month << endl;
	}
	
    return res;
}

class DataBase
{
    public:
    void Add(void)
    {
	#if DEBUG
        cout << "IN FUNC " << endl;
    #endif
        while (cin.peek() == ' ')
        {
            cin.ignore(1);
        }
        string date;
        getline(cin, date, ' ');
        //cin >> date;
    #if DEBUG
        cout << "LINE: " << date << endl;
    #endif
        bool res = CheckDateFormat(date);
        if (res == true)
        {
            res = CheckMonthAndDay();
        }
        if (res == true)
        {
            string event;
            cin >> event;
			
            string res_date = BS_year + '-' + BS_month + '-' + BS_day;
			parse_date[res_date] = {BS_year, BS_month, BS_day};
			
            if(data_base[res_date].count(event) == 0)
            {
                data_base[res_date].insert(event);
            }
        }
        else
        {
            string allStr;
            getline(cin, allStr);
        }
        EraseDayMonthBuffers();
        ResetFlags();
    }

    
    void Del(void)
    {
        while (cin.peek() == ' ')
        {
            cin.ignore(1);
        }
    #if DEBUG
        cout << "IN FUNC " << endl;
    #endif
        string str, date;
        bool with_event = false;
        getline(cin, str);
        stringstream stream(str);
        for (auto &c : str)
        {
            if (c == ' ')
                with_event = true;
        }
        if (with_event == true)
        {
            getline(stream, date, ' ');
            #if DEBUG
            cout << "Is with event" << str << endl;
            #endif
        }
        else
        {
            #if DEBUG
            cout << "Is without event " << str <<endl;
            #endif
            date = str;
        }
        
        bool res = CheckDateFormat(date);
        if (res == true)
        {
            res = CheckMonthAndDay();
        }
        if (res == true)
        {
            string res_date = BS_year + '-' + BS_month + '-' + BS_day;
            if (with_event == true)
            {
                string event;
                getline(stream, event);
                if(data_base[res_date].count(event) != 0)
                {
                    data_base[res_date].erase(event);
					if (data_base[res_date].size() == 0)
					{
						parse_date.erase(res_date);
					}
					
                    cout << "Deleted successfully" << endl;
                }
                else
                {
                    cout << "Event not found" << endl;
                }
            }
            else
            {
                if(data_base[res_date].size() == 0)
                {
                    cout << "Deleted 0 events" << endl;
                }
                else
                {
                    cout << "Deleted " << data_base[res_date].size() << " events" << endl;
                    data_base[res_date].clear();
                }
            }
        }
        EraseDayMonthBuffers();
        ResetFlags();
    }
    
    void Find(void)
    {
        while (cin.peek() == ' ')
        {
            cin.ignore(1);
        }
    #if DEBUG
        cout << "IN FUNC " << endl;
    #endif
        string date;
        getline(cin, date);
        //cin >> date;
    #if DEBUG
        cout << "LINE: " << date << endl;
    #endif
        bool res = CheckDateFormat(date);
        if (res == true)
        {
            res = CheckMonthAndDay();
        }
        if (res == true)
        {
            string res_date = BS_year + '-' + BS_month + '-' + BS_day;
            
            if(data_base[res_date].size() != 0)
            {
                for (const auto &i : data_base[res_date])
                {
                    cout << i << endl;
                }
            }
        }
        else
        {
            string allStr;
            getline(cin, allStr);
        }
        EraseDayMonthBuffers();
        ResetFlags();
    }
    
    
    void Print(void)
    {
        stringstream stream;
        bool y_print = false, m_print = false, d_print = false;
        for (const auto &date : data_base)
        {
            stringstream print_date;
			print_date << setw(4) << setfill('0') << parse_date[date.first].year << '-';
			print_date << setw(2) << setfill('0') << parse_date[date.first].month << '-';
			print_date << setw(2) << setfill('0') << parse_date[date.first].day << ' ';
			
            for (const auto &event : date.second)
            {
                cout << print_date.str() << event << endl;
            }
        }
    }
    
    private:  
    map<string, set<string>> data_base;

	struct dateSt
	{
		string year;
		string month;
		string day;
	};
	
	map<string, dateSt> parse_date;
};


int main()
{
    DataBase db;
    while (true)
    {
        string cmd;
        cin >> cmd;
        #if DEBUG
        cout << "CMD: " << cmd << endl;
        #endif
        if (cmd == "Add")
        {
            db.Add();
        }
        else if (cmd == "Find")
        {
            db.Find();
        }
        else if (cmd == "Del")
        {
            db.Del();
        }
        else if (cmd == "Print")
        {
            db.Print();
        }
        else
        {
            cout << "Unknown command: " << cmd << endl;
			string str;
			getline(cin, str);
        }
    }
    return 0;
}
