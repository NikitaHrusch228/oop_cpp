#pragma once
#include <string>


class Person
{
private:
    string firstName = "";
    string middleName = "";
    string lastName = "";
    int birthYear = 0;
public:
    Person() = default;
    Person(string fn, string mn, string ln, int by)
    {
        this->firstName = fn;
        this->middleName = mn;
        this->lastName = ln;
        this->birthYear = by;
    }
    ~Person() = default;
    string getFirstName()
    {
        return this->firstName;
    }
    string getMiddleName()
    {
        return this->middleName;
    }
    string getLastName()
    {
        return this->lastName;
    }
    string getFullName()
    {
        return this->firstName + " " + this->middleName + " " + this->lastName;
    }
    string getFIO()
    {
        string result = "";
        result += (this->middleName)[0];
        result += (this->firstName)[0];
        result += (this->lastName)[0];
        return result;
    }
    int getBirthYear()
    {
        return this->birthYear;
    }
    int getAge(int year)
    {
        return year - this->birthYear;
    }
    bool operator==(const Person another)
    {
        if(this->firstName != another.firstName) return false;
        if(this->middleName != another.middleName) return false;
        if(this->lastName != another.lastName) return false;
        if(this->birthYear != another.birthYear) return false;
        return true;
    }
    bool operator!=(const Person another)
    {
        if(this->firstName != another.firstName) return true;
        if(this->middleName != another.middleName) return true;
        if(this->lastName != another.lastName) return true;
        if(this->birthYear != another.birthYear) return true;
        return false;
    }
};
std::ostream& operator<< (std::ostream &out, Person person)
{
    return out << "{" << person.getFullName() << ", " << person.getBirthYear() << "}";
}