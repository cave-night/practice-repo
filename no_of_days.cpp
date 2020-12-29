#include<iostream>

using namespace std;

	const int MONTHS=12;
	const int DAYS_IN_NORM_YEAR=365;
	const int DAYS_IN_LEAP_YEAR=366;
	const int MONTH_DAYS[]={31,28,31,30,31,30,31,31,30,31,30,31};

class Date{
	int dd,mm,yy;
	
	public:
	Date(int dd, int mm, int yy){
		this->dd=dd;
		this->mm=mm;
		this->yy=yy;
	}
	
	bool is_valid_date(){
		//limits
		if(this->yy < 0 || this->mm < 1 || this ->mm > 12 || this->dd < 1)
			return false;
		//leap year condition
		if(this->dd == 29 && this->mm == 2 && (this->yy%4==0))
			return true;
		//upeer limit on date
		if(this->dd > MONTH_DAYS[this->mm -1])
			return false;
		return true;
	}
	
	int operator>(const Date &d){
		int f=(yy > d.yy);
		if(f==0){
			f=(mm > d.mm);
			if(f==0)
				f=(dd > d.dd);
		}	
		return f;
	}
	
	void operator=(const Date &d){
		dd=d.dd;
		mm=d.mm;
		yy=d.yy;
	}
	
	int get_dd(){
		return dd;
	}
	int get_mm(){
		return mm;
	}
	int get_yy(){
		return yy;
	}
};

long difference(Date d1, Date d2){
	//make d1 starting date and d2 ending date
	if(d1>d2){
		Date temp=d1;
		d1=d2;
		d2=temp;
	}
	long no_of_days=0;
	
	if(d1.get_yy()==d2.get_yy() && d1.get_mm()==d2.get_mm()){
		no_of_days+=(d2.get_dd()-d1.get_dd());
		return no_of_days;
	}
	
	no_of_days+=(MONTH_DAYS[d1.get_mm()-1]-d1.get_dd() + d2.get_dd());
	
	if(d1.get_yy()==d2.get_yy()){
		for(int i=d1.get_mm();i<d2.get_mm()-1;i++)
			no_of_days+=(MONTH_DAYS[i]);
		if(d1.get_yy()%4==0 && d1.get_mm()<=2 && d2.get_mm()>2)
			no_of_days++;
		return no_of_days;
	}
	
	//adding days from starting year
	for(int i=d1.get_mm();i<MONTHS;i++)
		no_of_days+=(MONTH_DAYS[i]);
	if(d1.get_yy()%4==0 && d1.get_mm()<=2)
		no_of_days++;	
	
	//adding days from ending year
	for(int j=0;j<d2.get_mm()-1;j++)
		no_of_days+=(MONTH_DAYS[j]);
	if(d2.get_yy()%4==0 && d2.get_mm()>2)
		no_of_days++;
	
	//adding whole years in between
	for(int k=d1.get_yy()+1;k<=d2.get_yy()-1;k++){
		if(k%4==0)
			no_of_days+=DAYS_IN_LEAP_YEAR;
		else
			no_of_days+=DAYS_IN_NORM_YEAR;
	}

	return no_of_days;
}

int main(){
	int a,b,c;
	cout<<"Enter date 1 (dd mm yyyy) : ";
	cin>>a>>b>>c;
	Date d1= Date(a,b,c);
	cout<<"Enter date 2 (dd mm yyyy) : ";
	cin>>a>>b>>c;
	Date d2= Date(a,b,c);
	long diff=0;
	try{
		if(!d1.is_valid_date())
			throw("Date 1");
		if(!d2.is_valid_date())
			throw("Date 2");
		diff=difference(d1,d2);
		cout<<"Difference in number of days : "<<diff;
	}
	catch(const char *s){
		cout<<s<<" is invalid";
	}
	return 0;
}
