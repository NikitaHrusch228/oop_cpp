#include "sortFunctions.h"
#include <cstdlib>
#include "index.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "sparse_matrix.h"
#include "histogram.h"

using namespace std;

string FirstNames[10] {"Andrey", "Alexey", "Ivan", "Vasiliy", "Igor", "Egor", "Oleg", "Vladimir", "Alexander", "Michael"};
string MiddleNames[10] {"Ivanov", "Frolov", "Ivlev", "Roslovtsev", "Privalenko", "Korotkov", "Novikov", "Romanov", "Demidov", "Svetov"};
string LastNames[10] {"Andreevich", "Alexeevich", "Ivanovich", "Vasilievich", "Igorievich", "Egorovich", "Olegovich", "Vladimirovich", "Alexandrovich", "Michaelovich"};
const string alphabet = "abcdefghijklmnopqrstuvwxyz";

template <class T>
void showTimeSearchIndex(IndexDictionary<T> *ind_dict, T index)
{
    cout << "Search in indexed data" << endl;
    auto begin = chrono::steady_clock::now();
    cout << "Found value:" << ind_dict->get(index) << endl;
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Time consumed: " << elapsed_ms.count() << " ms" << endl;
    return;
}
template <class T>
void showTimeSearchSequence(ArraySequence<Person> *seq, T index, T (Person::*getParam)())
{
    cout << "Search in unsorted sequence" << endl;
    auto begin = chrono::steady_clock::now();
    int i = 0;
    for (i; i < seq->getSize(); i++)
    {
        if ((seq->get(i).*getParam)() == index) break;
    }
    cout << "Found value:" << seq->get(i) << endl;
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Time consumed: " << elapsed_ms.count() << " ms" << endl;
    return;
}

string randomFN()
{
    int i = rand() % 10;
    return FirstNames[i];
}
string randomMN()
{
    int i = rand() % 10;
    return MiddleNames[i];
}
string randomLN()
{
    int i = rand() % 10;
    return LastNames[i];
}
int randomBY()
{
    return 1920 + (rand() % 100);
}

string getRC()
{
    char c = 65 + rand() % 26;
    return "" + c;
}

string getRS()
{
    int length = 3 + rand() % 8;
    string result = "";
    for (int i = 0; i < length; i++)
    {
        result += alphabet[rand() % 26];
    }
    return result;
}

Person enterPerson()
{
    string fn = "";
    string mn = "";
    string ln = "";
    int by = 0;
    cout << "Enter the FIRST NAME of the person" <<endl;
    cin >> fn;
    cout << endl;
    cout << "Enter the MIDDLE NAME of the person" <<endl;
    cin >> mn;
    cout << endl;
    cout << "Enter the LAST NAME of the person" <<endl;
    cin >> ln;
    cout << endl;
    cout << "Enter the BIRTH YEAR of the person" <<endl;
    cin >> by;
    cout << endl;
    return Person(fn, mn, ln, by);
}
void interface_index()
{
    IndexDictionary<string> *ind_dict;
    IndexDictionary<int> *ind_dict_INT;
    ArraySequence<Person> *seq = new ArraySequence<Person>();
    int choose = 0;
    int howManyPersons = 0;
    Person newPerson;
    string (Person::*getParam)() = NULL;
    int (Person::*getParamINT)() = NULL;
    int index_INT = 0;
    string index = "";

    cout << "DATA INDEXING" << endl;
    while(true)
    {
        cout << "Enter 1 to add some random persons to the array" << endl;
        cout << "Enter 2 to add a custom person to the array" << endl;
        cout << "Enter 3 to index data from the array" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose)
        {
            case 1:
                cout << "Enter how many persons to generate" << endl;
                cin >> howManyPersons;
                for (int i = 0; i < howManyPersons; i++)
                {
                    newPerson = Person(getRS(), getRS(), getRS(), randomBY());
                    seq->append(newPerson);
                    cout << newPerson << endl;
                }
                cout << endl << howManyPersons << " persons have been generated" << endl << endl;
                break;
            case 2:
                seq->append(enterPerson());
                break;
            case 3:
                cout << "You need to choose a parameter to index data" << endl;
                cout << "1: INDEX = FIRST NAME" << endl;
                cout << "2: INDEX = MIDDLE NAME" << endl;
                cout << "3: INDEX = LAST NAME" << endl;
                cout << "4: INDEX = BIRTH YEAR" << endl;
                cout << "5: INDEX = FULL NAME" << endl;
                cout << "6: INDEX = FIO" << endl;
                cin >> choose;
                cout << endl;
                switch(choose)
                {
                    case 1:
                        getParam = Person::getFirstName;
                        break;
                    case 2:
                        getParam = Person::getMiddleName;
                        break;
                    case 3:
                        getParam = Person::getLastName;
                        break;
                    case 4:
                        getParamINT = Person::getBirthYear;
                        break;
                    case 5:
                        getParam = Person::getFullName;
                        break;
                    case 6:
                        getParam = Person::getFIO;
                        break;
                    default:
                        getParam = Person::getFirstName;
                        break;
                }

                if(getParam != NULL)
                {
                    ind_dict = new IndexDictionary<string>(*seq, getParam);
                } else ind_dict_INT = new IndexDictionary<int>(*seq, getParamINT);
                cout << "Indexed data:" << endl;
                if(getParam != NULL)
                {
                    ind_dict->print();
                } else ind_dict_INT->print();

                if(getParam != NULL)
                {
                    cout << "An amount of indexed persons: " << ind_dict->getCount() << endl;
                } else cout << "An amount of indexed persons: " << ind_dict_INT->getCount() << endl;

                cout << "To compare search speed enter an index" << endl;
                if(getParam != NULL)
                {
                    cin >> index;
                } else cin >> index_INT;
                cout << endl;
                if(getParam != NULL)
                {
                    if (ind_dict->contains(index))
                    {
                        showTimeSearchIndex(ind_dict, index);
                        showTimeSearchSequence(seq, index, getParam);
                    } else cout << "WRONG INDEX!" << endl;
                } else if(ind_dict_INT->contains(index_INT))
                {
                    showTimeSearchIndex(ind_dict_INT, index_INT);
                    showTimeSearchSequence(seq, index_INT, getParamINT);
                } else cout << "WRONG INDEX!" << endl;
                cout << endl;

                break;
            default:
                delete seq;
                delete ind_dict;
                return;
        }
    }
}

void interface_sparse_matrix()
{
    int choose = 0;
    int x = 0;
    int y = 0;
    int len = 0;
    SparseMatrix<int> *matrix = new SparseMatrix<int>(0,0);


    cout << "SPARCE MATRIXES" << endl;
    cout << "You need to create a matrix" << endl;
    cout << "Enter a number of rows" << endl;
    cin >> choose;
    matrix->setRows(choose);
    cout << endl;
    cout << "Enter a number of columns" << endl;
    cin >> choose;
    matrix->setColumns(choose);
    cout << endl;
    cout << "Enter 1 to generate a random matrix of a given size" << endl;
    cout << "Note: you can choose an amount of non-zero elements" << endl;
    cout << "Enter 2 to fill in the matrix manually" << endl;
    cin >> choose;
    cout << endl;
    switch(choose)
    {
        case 1:
            cout << "Enter an amount of non-zero elements" << endl;
            cin >> len;
            cout << endl;
            if (len > matrix->getRows() * matrix->getColumns())
                len = matrix->getRows() * matrix->getColumns();
            for (int i = 0; i < len; i++)
            {
                do
                {
                    x = rand() % (matrix->getRows());
                    y = rand() % (matrix->getColumns());
                } while (matrix->isNotZero(x,y));
                matrix->set(x, y, 1 + (rand() % 9));
            }
            break;
        case 2:
            while(true)
            {
                cout << "Enter a row" << endl;
                cin >> x;
                cout << endl;
                cout << "Enter a column" << endl;
                cin >> y;
                cout << endl;
                cout << "Enter a value" << endl;
                cin >> choose;
                cout << endl;
                matrix->set(x, y, choose);
                cout << "Enter 1 to add another element to the matrix" << endl;
                cout << "Enter a different number to finish matrix creating" << endl;
                cin >> choose;
                cout << endl;
                if (choose != 1) break;
            }
            break;
        default:
            delete matrix;
            return;
    }
    if(matrix->get(0,0) == 0) matrix->setToZero(0,0);
    cout << endl;
    cout << "The matrix:" << endl;
    matrix->printAsMatrix();
    cout << "Enter something to quit" << endl;
    cin >> choose;
    return;
}

void interface_histogram()
{
    ArraySequence<Person> *seq = new ArraySequence<Person>();
    int choose = 0;
    int howManyPersons = 0;
    Person newPerson;
    int (Person::*getParam)() = NULL;
    Histogram *hist;

    cout << "HISTOGRAM" << endl;
    while(true) {
        cout << "Enter 1 to add some random persons to the array" << endl;
        cout << "Enter 2 to add a custom person to the array" << endl;
        cout << "Enter 3 to build a histogram" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose) {
            case 1:
                cout << "Enter how many persons to generate" << endl;
                cin >> howManyPersons;
                for (int i = 0; i < howManyPersons; i++) {
                    newPerson = Person(getRS(), getRS(), getRS(), randomBY());
                    seq->append(newPerson);
                    cout << newPerson << endl;
                }
                cout << endl << howManyPersons << " persons have been generated" << endl << endl;
                break;
            case 2:
                seq->append(enterPerson());
                break;
            case 3:
                cout << "BIRTH YEAR is a parameter for the histogram" << endl;
                getParam = Person::getBirthYear;
                cout << "Enter an amount of subsets" << endl;
                cin >> choose;
                cout << endl;
                hist = new Histogram(*seq, getParam, choose);
                cout << "The histogram:" << endl;
                hist->print();
                system("pause");
                break;
            default:
                return;
        }
    }
}

void interface()
{
    int choose = 0;

    while(true)
    {
        cout << "Choose a task:" << endl;
        cout << "Enter 1 to test data indexing" << endl;
        cout << "Enter 2 to test sparse matrixes" << endl;
        cout << "Enter 3 to test histogram" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose) {
            case 1:
                interface_index();
                break;
            case 2:
                interface_sparse_matrix();
                break;
            case 3:
                interface_histogram();
                break;
            default:
                return;
        }
    }
}

int main(int argc, const char *argv[])
{
    srand(time(0));
    interface();
	return 0;
}