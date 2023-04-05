#include <iostream>
using namespace std;

bool isLeapYear(int year){
    if((year%4==0)&&(year%100!=0)||(year%400==0))
        return true;
    return false;
}

void CalcDate(){
    int year, days;
    while(cin>>year>>days){
        int _year=year;
        int _month=1;
        int _day=0;

        int arr[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

        if((days>59)&&(isLeapYear(year))){
            arr[2]+=1;
        }

        while(days>0){
            --days;
            ++_day;
            if(_day>arr[_month]){
                ++_month;
                _day=1;
                if(_month>12){
                    _month=1;
                    ++_year;
                }
            }
        }
        printf("%d-%02d-%02d\n",_year,_month,_day);
    }
}

int main(){
    CalcDate();

    return 0;
}