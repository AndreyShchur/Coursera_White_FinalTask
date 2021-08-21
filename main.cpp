#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>


using namespace std;

//#define DEBUG   (1)

struct dateSt
{
    int year;
    int month;
    int day;
    
};

bool operator<(const dateSt &l, const dateSt &r)
{
    if (l.year < r.year)
    {
        return true;
    }
    else if (l.year == r.year)
    {
        if (l.month < r.month)
        {
            return true;
        }
        else if (l.month == r.month)
        {
            if (l.day < r.day)
            {
                return true;
            }
        }
    }
    return false;
}


class DataBase
{
    public:
    void Add(stringstream &str)
    {
        int year, month, day;
        char split1, split2, space;
        if ((str >> year >> split1 >> month >> split2 >> day) &&
            (true == CheckSplits(split1, split2))             &&
            (str.peek() == ' '))
        {
            year = abs(year);
            if (true == CheckMonth(month))
            {
                if (true == CheckDay(day))
                {
                    string event;
                    str >> event;
                    data_base[{year, month, day}].insert(event);
                }
            }
            
        }
        else
        {
            cout << "Wrong date format: " << GetDate(str) << endl;
        }
    }

    
    void Del(stringstream &str)
    {
        int year, month, day;
        char split1, split2, space;
        if ((str >> year >> split1 >> month >> split2 >> day) &&
            (true == CheckSplits(split1, split2))             &&
            (str.peek() == ' ' || str.peek() == '\n' || str.peek() == EOF))
        {
            year = abs(year);
            if (true == CheckMonth(month))
            {
                if (true == CheckDay(day))
                {
                    if (str.peek() != EOF)
                    {
                        string event;
                        str >> event;
                        bool event_not_deleted = true;
                        for (const auto &db : data_base)
                        {
                            if ((db.first.year == year)   &&
                                (db.first.month == month) &&
                                (db.first.day == day))
                            {
                                if (db.second.count(event) != 0)
                                {
                                    data_base[{year,month,day}].erase(event);
                                    cout << "Deleted successfully" << endl;
                                    event_not_deleted = false;
                                    break;
                                }
                            }
                        }
                        if (event_not_deleted)
                        {
                            cout << "Event not found" << endl;
                        }
                    }
                    else
                    {
                        bool date_is_not_del = true;
                        for (const auto &db : data_base)
                        {
                            if ((db.first.year == year)   &&
                                (db.first.month == month) &&
                                (db.first.day == day))
                            {
                                int event_ctr = db.second.size();
                                data_base.erase({year,month,day});
                                cout << "Deleted " << event_ctr << " events" << endl;
                                date_is_not_del = false;
                                break;
                            }
                        }
                        if (date_is_not_del)
                        {
                            cout << "Deleted 0 events" << endl;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Wrong date format: " << GetDate(str) << endl;
        }
    }
    
    void Find(stringstream &str)
    {
        int year, month, day;
        char split1, split2, space;
        if ((str >> year >> split1 >> month >> split2 >> day) &&
            (true == CheckSplits(split1, split2))             &&
            (str.peek() == ' ' || str.peek() == '\n' || str.peek() == EOF))
        {
            year = abs(year);
            if (true == CheckMonth(month))
            {
                if (true == CheckDay(day))
                {
                    for (const auto &db : data_base)
                    {
                        if ((db.first.year == year)   &&
                            (db.first.month == month) &&
                            (db.first.day == day))
                        {
                            for (const auto &e : db.second)
                            {
                                cout << e << endl;
                            }
                            break;
                        }
                    }
                }
            }
            
        }
        else
        {
            cout << "Wrong date format: " << GetDate(str) << endl;
        }
    }
    
    
    void Print(void)
    {
        for (const auto &db : data_base)
        {
            stringstream print_date;
            print_date << setw(4) << setfill('0') << db.first.year << '-';
			print_date << setw(2) << setfill('0') << db.first.month << '-';
			print_date << setw(2) << setfill('0') << db.first.day << ' ';
			
            for (const auto &event : db.second)
            {
                cout << print_date.str() << event << endl;
            }
        }
    }
    
    private:  
    map<dateSt, set<string>> data_base;
	map<string, dateSt> parse_date;
    
    string GetDate(stringstream &stream)
    {
        string date;
        bool dataSet = false;
        string line = stream.str();
        int space_iter = 0;
        for (const auto  &c : line)
        {
            if (c == ' ' && space_iter == 0)
            {
                space_iter++;
            }
            else if (c != ' ' && space_iter != 0)
            {
                date += c;
                dataSet = true;
            }
            else if ((c == ' ' || c == EOF || c == '\n') && dataSet == true)
            {
                return date;
            }
        }
        
        return date;
    }
    
    
    bool CheckMonth(int &month)
    {
        if (month > 0 && month < 13)
        {
            return true;
        }
        else
        {
            cout << "Month value is invalid: " << month << endl;
            return false;
        }
    }
    
    bool CheckDay(int &day)
    {
        if (day > 0 && day < 32)
        {
            return true;
        }
        else
        {
            cout << "Day value is invalid: " << day << endl;
            return false;
        }
    }
    
    bool CheckSplits(char &split1, char &split2)
    {
        if (split1 == '-' && split2 == '-')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};


int main()
{
    DataBase db;
    for (string str ; getline(cin, str);)
    {
        if (str == "") 
        {
            continue;
        }
        
        string cmd;
        stringstream stream(str);
        stream >> cmd;
        if (cmd == "Add")
        {
            db.Add(stream);
        }
        else if (cmd == "Find")
        {
            db.Find(stream);
        }
        else if (cmd == "Del")
        {
            db.Del(stream);
        }
        else if (cmd == "Print")
        {
            db.Print();
        }
        else
        {
            cout << "Unknown command: " << cmd << endl;
        }
    }
    return 0;
}
