#include <iostream>
#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include "comparison.h"
#include <chrono>


int main() {

    int N;
    std::cout << "input number of elements:";
    std::cin >> N;
    int data[N];
    for (int i = 0; i < N; ++i) {
        data[i] = rand() % 1000;
    }
    class Timer
    {
    private:
        // Псевдонимы типов используются для удобного доступа к вложенным типам
        using clock_t = std::chrono::high_resolution_clock;
        using second_t = std::chrono::duration<double, std::ratio<1> >;

        std::chrono::time_point<clock_t> m_beg;

    public:
        Timer() : m_beg(clock_t::now())
        {
        }

        void reset()
        {
            m_beg = clock_t::now();
        }

        double elapsed() const
        {
            return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
        }
    };
    double num;
    std::cout << "1.ArrayShellSort\n2.ListShellSort\n3.ArrayQuickSort\n4.ListQuickSort\n5.ArrayBubbleSort\n6.ListBubbleSort\n";
    std::cin >> num;
    if (num == 1)
    {
        std::cout << "Array ShellSort : \n";
        ArraySequence<int> a(data, N);
        std::cout << "Random : ";
        Timer t1;
        a.ShellSort(cmp3);
        std::cout << "Time elapsed: " << t1.elapsed() << '\n';
        std::cout << "Sorting : ";
        Timer t2;
        a.ShellSort(cmp3);
        std::cout << "Time elapsed: " << t2.elapsed() << '\n';
        std::cout << "Reverse: ";
        Timer t3;
        a.ShellSort(cmp2);
        std::cout << "Time elapsed: " << t3.elapsed() << '\n';
        return 0;
    }else if (num==2)
    {
        std::cout << "Array ShellSort : \n";
        LinkedListSequence<int> a(data, N);
        std::cout << "Random : ";
        Timer t1;
        a.ShellSort(cmp3);
        std::cout << "Time elapsed: " << t1.elapsed() << '\n';
        std::cout << "Sorting : ";
        Timer t2;
        a.ShellSort(cmp3);
        std::cout << "Time elapsed: " << t2.elapsed() << '\n';
        std::cout << "Reverse: ";
        Timer t3;
        a.ShellSort(cmp2);
        std::cout << "Time elapsed: " << t3.elapsed() << '\n';
        return 0;
    }else if (num==3)
    {
        std::cout << "Array QuickSort : ";
        ArraySequence<int> a(data, N);
        std::cout << "Random : ";
        Timer t1;
        a.QuickSort(cmp2, cmp3);
        std::cout << "Time elapsed: " << t1.elapsed() << '\n';
        std::cout << "Sorting : ";
        Timer t2;
        a.QuickSort(cmp2, cmp3);
        std::cout << "Time elapsed: " << t2.elapsed() << '\n';
        std::cout << "Reverse: ";
        Timer t3;
        a.QuickSort(cmp3, cmp2);
        std::cout << "Time elapsed: " << t3.elapsed() << '\n';
        return 0;

    }else if (num==4)
    {
        std::cout << "List QuickSort : ";
        LinkedListSequence<int> a(data, N);
        std::cout << "Random : ";
        Timer t1;
        a.QuickSort(cmp2, cmp3);
        std::cout << "Time elapsed: " << t1.elapsed() << '\n';
        std::cout << "Sorting : ";
        Timer t2;
        a.QuickSort(cmp2, cmp3);
        std::cout << "Time elapsed: " << t2.elapsed() << '\n';
        std::cout << "Reverse: ";
        Timer t3;
        a.QuickSort(cmp3, cmp2);
        std::cout << "Time elapsed: " << t3.elapsed() << '\n';
        return 0;
    }else if (num==5)
    {
        std::cout << "Array BubbleSort : ";
        ArraySequence<int> a(data, N);
        std::cout << "Random : ";
        Timer t1;
        a.BubbleSort(cmp2);
        std::cout << "Time elapsed: " << t1.elapsed() << '\n';
        std::cout << "Sorting : ";
        Timer t2;
        a.BubbleSort(cmp2);
        std::cout << "Time elapsed: " << t2.elapsed() << '\n';
        std::cout << "Reverse: ";
        Timer t3;
        a.BubbleSort(cmp3);
        std::cout << "Time elapsed: " << t3.elapsed() << '\n';
        return 0;

    }else if (num==6)
    {
        std::cout << "List BubbleSort : ";
        LinkedListSequence<int> a(data, N);
        std::cout << "Random : ";
        Timer t1;
        a.BubbleSort(cmp2);
        std::cout << "Time elapsed: " << t1.elapsed() << '\n';
        std::cout << "Sorting : ";
        Timer t2;
        a.BubbleSort(cmp2);
        std::cout << "Time elapsed: " << t2.elapsed() << '\n';
        std::cout << "Reverse: ";
        Timer t3;
        a.BubbleSort(cmp3);
        std::cout << "Time elapsed: " << t3.elapsed() << '\n';
        return 0;
    }

    return 0;
}
//a.Print();