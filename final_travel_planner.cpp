// Importing required libraries
#include<iostream>
#include<string>
#include<stdlib.h>
#include <fstream>
#include<string.h>

using namespace std;

static int total_cost_of_trip = 0;
char iten_name[100];
ofstream outputFile(iten_name);

// Creating Abstract Class (Base Class)
class Location{
protected:
    string city_name;
    string country_name;

public:
    Location(string city, string country):city_name(city), country_name(country){}

    virtual void display()=0;
    virtual int getPrice(){return 0;}
};

//Creating City Class (inherited from Location)
class City:public Location{
public:
    // Constructor
   City():Location("", ""){
       city_name= "City";
   }

    // Getting City Information from User
    void city_info(){
        cin.ignore();
        cout<<"Enter City : ";
        getline(cin , city_name); 
        cout<<"Enter Country : ";
        cin>>country_name;
    }

    // Displaying City Information
    void display(){
        cout<<"City: "<<city_name<<endl;
        cout<<"Country: "<< country_name<<endl;
    }

    // Saving City Information into Text File
    void city_save(char iten_name[100]){
        ofstream outputFile(iten_name,ios::app);
        outputFile<<"City: "<<city_name<<endl;
        outputFile<<"Country: "<< country_name<<endl;
    }
};

// Creating Hotel Class (inherited from Location)
class Hotel:public Location{
protected:
    string hotel_name;
    int hotel_price_per_day;
    int stay_duration;

public:
    // Defining Constructor
    Hotel():Location("", ""){
        hotel_name="Default Hotel";
        hotel_price_per_day=0;
        stay_duration=1; 
    }

    // Getting Hotel Information from User
    void hotel_info(){
        cin.ignore();
        cout<<"Enter Hotel Name : ";
        getline(cin, hotel_name); 
        cout<<"Enter Hotel Price per Day : ";
        cin>>hotel_price_per_day;
        cout<<"Enter Number of Days of Stay : ";
        cin>>stay_duration;
    }

    // Displaying Hotel Information
    void showdetails(){
        cout<<"Hotel : "<<hotel_name<<endl;
        cout<<"Stay Duration: "<< stay_duration<<" days"<< endl;
    }

    void display()override{
        cout<<"City: "<<city_name<<endl;  
        cout<<"Country: "<< country_name<<endl;
    }

    // Returning Total Hotel Expense 
    int getPrice()override{
        return hotel_price_per_day*stay_duration;
    }

    // Saving Hotel Information to Text File
    void save_hotel(char iten_name[100]){
        ofstream outputFile(iten_name,ios::app);
        outputFile<<"Hotel : "<<hotel_name<<endl;
        outputFile<<"Stay Duration: "<< stay_duration<<" days"<< endl;
    }
};

// Creating Activity Class (Location Inherited)
class Activity:public Location{
protected:
    string act_name;
    int activity_price;

public:

    // Defining Constructor
    Activity():Location("", ""){
        act_name="Default Activity";
        activity_price = 0;
    }

    // Getting Activity Information from User
    void act_info(){
        cin.ignore();
        cout<<"Enter Activity Name : ";
        getline(cin, act_name); 
        cout<<"Enter Activity Price : ";
        cin>>activity_price;
    }

    // Showing Activity Information 
    void showdata(){
        cout<<"Activity : " <<act_name<<endl;
        //display();
        //cout<<"Activity Price per Day:"<<activity_price<<endl;
    }

    void display()override{
        cout<<"City:"<<city_name<<endl;
        cout<< "Country: "<<country_name<<endl;
    }

    // Returning Activity Price
    int getPrice()override{
        return activity_price; 
    }

    // Saving Activity Information to Text File
    void save_act(char iten_name[100]){
        ofstream outputFile(iten_name,ios::app);
        outputFile<<"Activity : " <<act_name<<endl;
    }
};

// Creating Date Class
class Date {
protected:
    int day;
    int month;
    int year;

public:

    // Getting Date Information from User
    void fdate(){
        cout<<"Date : "<<endl;
        cout<<"Day: ";
        cin>>day;
        cout<<"Month: ";
        cin>>month;
        cout<<"Year: ";
        cin>>year;
    }

    // Showing Date Information
    void showdata(Date const d1, Date const d2){
        cout<<"From: "<<d1.day<<"/"<<d1.month<<"/"<<d1.year;
        cout<<" To: "<<d2.day<<"/"<<d2.month<<"/"<<d2.year<<endl;
        
    }

    // Saving Date information to Text File
    void savedata(Date const d1, Date const d2 ,char iten_name[100])
    {
        ofstream outputFile(iten_name , ios::app);
        outputFile<<"From: "<<d1.day<<"/"<<d1.month<<"/"<<d1.year;
        outputFile<<" To: "<<d2.day<<"/"<<d2.month<<"/"<<d2.year<<endl;
    }

    // Adding friend function to count number of Days
    friend int noofdays(Date const d1, Date const d2);
};
    

// Defining Function to count number of Days
int noofdays(Date const d1, Date const d2){
        int x = 0;
        if (d2.year>d1.year){
            x+=(d2.year-d1.year)*365;
        }
        if (d2.month>d1.month){
            x+=(d2.month-d1.month)*30;
        }
        if (d1.month>d2.month){
            x-=(d1.month-d2.month)*30;
        }
        if (d2.day>d1.day){
            x+=(d2.day-d1.day);
        }
        if (d1.day>d2.day){
            x-=(d1.day-d2.day);
        }
        if (x<0){
            cout<<"Invalid";
            return 0;
        }
        return x;
    }


// Creating Planner class to add up all the Information
class Planner{
public:
    Location* itinerary[1000];
    int current=0;
    int total=0;

    // Operator Overloading to add Location
    Planner& operator+=(Location* location){
        if (current<10){
            itinerary[current++]=location;
        }else{
            cout<<"Cannot add more locations. Maximum limit reached."<< endl;
        }
        return *this;
    }

    // Displaying Itinerary Information
    void displayItinerary(){
        cout<< "Trip Itinerary:"<<endl;
        for(int i=0;i<current;++i){
            itinerary[i]->display();
        }
    }

    // Getting Total cost of the trip
    int getTotalCost(){
        total_cost_of_trip += total;
        return total;
    }

    // Calculating Total Cost of Trip
    void calculateTotalCost(){
        total=0;
        for(int i=0;i<current;++i){
            total+=itinerary[i]->getPrice();
        }
    }
};


// Getting Total Expense of the trip
void bookTrip(Planner& planner){
    planner.calculateTotalCost();

    cout<<"----------------------------------------------"<<endl;
    cout<<"Total itinerary Expense : Rs."<< planner.getTotalCost()<< endl;
}

// Saving Total Expense to Text File
void save_bookTrip(Planner& planner , char iten_name[100]){
    planner.calculateTotalCost();
    ofstream outputFile(iten_name,ios::app);


    outputFile<<"----------------------------------------------"<<endl;
    outputFile<<"Total Itinerary Expense : Rs."<< planner.getTotalCost()<< endl;
}

// Driver Code
int main(){
    City c1[10];
    Hotel h1[10];
    Activity a1[100];
    Date d1[10] , d2[10];
    char iten_name[100];
    int n;

    // Getting Itinerary Name
    cout << "Enter Itinerary Name : ";
    cin.getline(iten_name, 100);

    // Getting Number of Cities 
    cout << "Enter Number of Cities (Max 10): ";
    cin >> n;

    // Getting all the information from User
    for (int i=0;i<n;i++){
        cout << "Location : " << i+1 << endl;
        c1[i].city_info();
        h1[i].hotel_info();
        a1[i].act_info();
        d1[i].fdate();
        d2[i].fdate();
        cout << endl;
    }

    system ("CLS");

    // Adding up all the information
    Planner trip1;
    for(int i=0;i<n;i++){
    trip1+=&h1[i];
    trip1+=&a1[i];
    }

    // Displaying all the information
    cout << "----------------------------------------------" << endl;
    cout << "              Your Itinerary                    " << endl;
    cout << "              "<<iten_name<<"                 " << endl;
    cout << "----------------------------------------------" << endl;
    for(int i=0;i<n;i++){
        cout << "      LOCATION : " << i+1 << "      " << endl;
        d1[i].showdata(d1[i],d2[i]);
        c1[i].display();
        h1[i].showdetails();
        a1[i].showdata();

    }

    
    bookTrip(trip1);
    cout << "Total Number of Days : " << noofdays(d1[0],d2[n-1]) + 1 << endl;
    
    cout << endl;

    // Saving information to text file
    int sa_ex;
    cout << "Press 1 to save Itinerary in Text File , Else 0 to exit" << endl;
    cin >> sa_ex;
    char txt[5] = ".txt";
    char final_txt[100];

    strcat(iten_name , txt);
    strcpy(final_txt , iten_name);

    if (sa_ex == 1){
        ofstream outputFile(final_txt,ios::app); // Writing Data to output file
        outputFile << "----------------------------------------------" << endl;
        outputFile << "              Your Itenary                    " << endl;
        outputFile << "              "<<iten_name<<"                 " << endl;
        outputFile << "----------------------------------------------" << endl;
        for(int i=0;i<n;i++){
            outputFile << "      LOCATION : " << i+1 << "      " << endl;
            d1[i].savedata(d1[i],d2[i],final_txt);
            c1[i].city_save(final_txt);
            h1[i].save_hotel(final_txt);
            a1[i].save_act(final_txt);
        }
        save_bookTrip(trip1 , final_txt);
        outputFile << "Total Number of Days : " << noofdays(d1[0],d2[n-1]) + 1 << endl;
        outputFile << "Thank you for using Travel Planner!" << endl;
        outputFile << "----------------------------------------------" << endl;
        outputFile.close();
        cout << "Your Itenary was saved with name : " << final_txt << endl;
        cout << "Thank you for using Travel Planner!" << endl;
        cout << "----------------------------------------------" << endl;
    } else {
        cout << "Thank you for using Travel Planner!" << endl;
        cout << "----------------------------------------------" << endl; 
    }

    system("pause");
    return 0;
}
