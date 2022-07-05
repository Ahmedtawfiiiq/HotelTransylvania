#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cstddef>

#define HOTEL_CAPACITY 20

#define MONSTERS_ROOMS 15
#define MONSTERS_NIGHT_PRICE 200
#define MONSTERS_CLEANING_PRICE 30
#define MONSTERS_SPA_PRICE 50

#define HUMANS_ROOMS 5
#define HUMANS_NIGHT_PRICE 500
#define HUMANS_CLEANING_PRICE 70
#define HUMANS_SPA_PRICE 100

using namespace std;

class Guest
{
private:
    bool newQuest=false;

public:
    int service;
    string inputUsername;
    int inputId;
    bool userFound=false;
    static int guestNumber;
    static string usernames[HOTEL_CAPACITY];
    static int iDs[HOTEL_CAPACITY];
    int inputRooms;
    static int reservedRooms[HOTEL_CAPACITY];
    int inputNights;
    static int reservedNights[HOTEL_CAPACITY];
    static int totalCost[HOTEL_CAPACITY];
    bool cleaning;
    bool spa;


    void registration()
    {
        if(guestNumber)
        {
            cout << "1: New quest" << endl;
            cout << "0: Old quest" << endl;
        }
        else
            cout << "1: New quest" << endl;

        cin >> newQuest;

        if(newQuest)
        {
            newUser();
            newReservation();
            guestNumber++;
        }
        else
        {
            oldUser();
            cout << "1:Extend" << endl;
            cout << "2:Additional Services" << endl;
            cout << "3:Cancel Reservation" << endl;
            cin >> service;
            if(service==1)
                extendReservation(inputId);
            else if(service==2)
                additionalServices(inputId);
            else if(service==3)
                cancelReservation(inputId);
        }
    }

    virtual void newUser()=0;
    virtual void oldUser()=0;

    virtual void newReservation()=0;
    virtual void extendReservation(int id)=0;
    virtual void additionalServices(int id)=0;
    virtual void cancelReservation(int id)=0;

};
int Guest::guestNumber = 0;
string Guest::usernames[HOTEL_CAPACITY]= {};
int Guest::iDs[HOTEL_CAPACITY]= {};
int Guest::reservedRooms[HOTEL_CAPACITY]= {};
int Guest::reservedNights[HOTEL_CAPACITY]= {};
int Guest::totalCost[HOTEL_CAPACITY]= {};


class Monster : public Guest
{
private:
    int monsters_Ids[MONSTERS_ROOMS] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    static int monstersAvailableRooms;

public:

    void newUser()
    {
        cout << "Monster user-name: " << endl;
        cin >> inputUsername;
        usernames[guestNumber]=inputUsername;

        cout << "Monster ID: ";
        iDs[guestNumber] = monsters_Ids[guestNumber];
        cout << iDs[guestNumber] << endl;
    }

    void oldUser()
    {
        if(guestNumber != 0)
        {
            cout << "Enter your ID:" << endl;
            while(true)
            {
                cin >> inputId;
                if(inputId >= 1 && inputId <= 15)
                {
                    for(int i = 0 ; i < guestNumber ; i++)
                    {
                        if(inputId == iDs[i])
                        {
                            cout << "Welcome: " << usernames[i] << endl;
                            userFound = true;
                            break;
                        }
                    }
                    if(!userFound)
                    {
                        cout << "No user with this Id" << endl;
                        cout << "Try another Id" << endl;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    cout << "Enter ID between 1 and 20" << endl;
                    continue;
                }
            }
        }
    }

    void newReservation()
    {
        cout << "Rooms to reserve?" << endl;
        while(true)
        {
            cout << "Available rooms: " << monstersAvailableRooms << endl;
            cin >> inputRooms;
            if(monstersAvailableRooms<inputRooms||inputRooms<=0)
                continue;
            else
                break;
        }
        reservedRooms[guestNumber] = inputRooms;

        cout << "Nights to reserve?" << endl;
        cin >> inputNights;
        reservedNights[guestNumber] = inputNights;

        totalCost[guestNumber] = inputRooms*inputNights*MONSTERS_NIGHT_PRICE;

        cout << "Total cost: " << totalCost[guestNumber] << endl;

        monstersAvailableRooms -= inputRooms;
    }

    void extendReservation(int id)
    {
        cout << "Extra nights?" << endl;
        cin >> inputNights;

        reservedNights[id-1] += inputNights;

        totalCost[id-1] += inputNights*MONSTERS_NIGHT_PRICE;
        cout << "Total cost: " << totalCost[id]<< endl;
    }

    void additionalServices(int id)
    {
        cout << "Dry Cleaning(0 or 1)" << endl;
        cin >> cleaning;

        cout << "Spa(0 or 1)" << endl;
        cin >> spa;

        if(cleaning&&spa)
            totalCost[id-1] += MONSTERS_CLEANING_PRICE+MONSTERS_SPA_PRICE;
        else if(cleaning)
            totalCost[id-1] += MONSTERS_CLEANING_PRICE;
        else if(spa)
            totalCost[id-1] += MONSTERS_SPA_PRICE;
    }

    void cancelReservation(int id)
    {
        totalCost[id-1] = 0;
        monstersAvailableRooms += reservedRooms[id-1];
        reservedRooms[id-1] = 0;
        reservedNights[id-1] = 0;
    }
};
int Monster::monstersAvailableRooms = MONSTERS_ROOMS;


class Human : public Guest
{
private:
    int humans_Ids[HUMANS_ROOMS] = {16,17,18,19,20};
    static int humansAvailableRooms;

public:
    void newUser()
    {
        cout << "Human user-name: " << endl;
        cin >> inputUsername;
        usernames[guestNumber]=inputUsername;

        cout << "Human ID: ";
        iDs[guestNumber] = humans_Ids[guestNumber];
        cout << iDs[guestNumber] << endl;
    }

    void oldUser()
    {
        if(guestNumber != 0)
        {
            cout << "Enter your ID:" << endl;
            while(true)
            {
                cin >> inputId;
                if(inputId >= 16 && inputId <= 20)
                {
                    for(int i = 0 ; i < guestNumber ; i++)
                    {
                        if(inputId == iDs[i])
                        {
                            cout << "Welcome: " << usernames[i] << endl;
                            userFound = true;
                            break;
                        }
                    }
                    if(!userFound)
                    {
                        cout << "No user with this Id" << endl;
                        cout << "Try another Id" << endl;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    cout << "Enter ID between 1 and 20" << endl;
                    continue;
                }
            }
        }
        else
        {
            cout << "Hotel is empty(Your have to register!!)" << endl;
            newUser();
        }
    }
    void newReservation()
    {
        cout << "Rooms to reserve?" << endl;
        while(true)
        {
            cout << "Available rooms: " << humansAvailableRooms << endl;
            cin >> inputRooms;
            if(humansAvailableRooms<inputRooms||inputRooms<=0)
                continue;
            else
                break;
        }

        reservedRooms[guestNumber] = inputRooms;

        cout << "Nights to reserve?" << endl;
        cin >> inputNights;
        reservedNights[guestNumber] = inputNights;

        totalCost[guestNumber] = inputRooms*inputNights*HUMANS_NIGHT_PRICE;

        humansAvailableRooms -= inputRooms;
    }

    void extendReservation(int id)
    {
        cout << "Extra nights?" << endl;
        cin >> inputNights;

        reservedNights[id-16] += inputNights;

        totalCost[id-16] += inputNights*HUMANS_NIGHT_PRICE;
        cout << "Total cost: " << totalCost[id-16]<< endl;
    }

    void additionalServices(int id)
    {
        cout << "Dry Cleaning(0 or 1)" << endl;
        cin >> cleaning;

        cout << "Spa(0 or 1)" << endl;
        cin >> spa;

        if(cleaning&&spa)
            totalCost[id-16] += HUMANS_CLEANING_PRICE+HUMANS_SPA_PRICE;
        else if(cleaning)
            totalCost[id-16] += HUMANS_CLEANING_PRICE;
        else if(spa)
            totalCost[id-16] += HUMANS_SPA_PRICE;
    }

    void cancelReservation(int id)
    {
        totalCost[id-16] = 0;
        humansAvailableRooms += reservedRooms[id-16];
        reservedRooms[id-16] = 0;
        reservedNights[id-16] = 0;
    }
};
int Human::humansAvailableRooms = HUMANS_ROOMS;


class Receptionist : public Guest
{
public:

    void guestDetails()
    {
        for(int i = 0 ; i < guestNumber ; i++)
        {
            cout << "----------------------------------------------" << endl;
            cout << "User-name: ";
            cout << usernames[i] << endl;

            cout << "ID: ";
            cout << iDs[i] << endl;

            cout << "Rooms: ";
            cout << reservedRooms[i] << endl;

            cout << "Nights: ";
            cout << reservedNights[i] << endl;

            cout << "Total Cost: ";
            cout << totalCost[i] << endl;
        }
    }
};


int main()
{
    string guestClass;
    int guestsNumber;
    bool validGuestsNumber=false;
    Guest* guest;

    cout << "Guest class(Monster or Human): " << endl;
    while(true)
    {
        cin >> guestClass;
        if(guestClass=="Monster")
        {
            guest = new Monster();
            break;
        }
        else if(guestClass=="Human")
        {
            guest = new Human();
            break;
        }
        else
        {
            cout << "Try again!!" << endl;
            continue;
        }
    }

    cout << "Guests Number:" << endl;
    while(true)
    {
        cin >> guestsNumber;
        if(guestClass=="Monster")
        {
            if(guestsNumber<=15&&guestsNumber>=1)
            {
                validGuestsNumber=true;
                break;
            }
            else
            {
                cout << "Enter a number between 1 and 15" << endl;
                continue;
            }
        }
        else if(guestClass=="Human")
        {
            if(guestsNumber<=5&&guestsNumber>=1)
            {
                validGuestsNumber=true;
                break;
            }
            else
            {
                cout << "Enter a number between 1 and 5" << endl;
                continue;
            }
        }
    }

    for(int i = 0 ; i<guestsNumber ; i++)
        guest->registration();

    Receptionist* receptionist;
    receptionist->guestDetails();
    return 0;
}
