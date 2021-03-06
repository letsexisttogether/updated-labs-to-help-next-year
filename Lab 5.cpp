#include <iostream>
#include <deque>
#include <clocale>
#include <string>
#include <stack>
#include <conio.h>

using namespace std;

int check_int(string Message)
{
    int valueToCheck;
    char test[10];
    bool exit = false;
    while(exit == false)
    {
        exit = false;
        cout << Message;
        scanf_s("%d", &valueToCheck);
        fgets(test, sizeof(test), stdin);

        if (strlen(test) > 1)
        {
            cout << "Введённое Вами значение не является целочисленным\n";
            cin.get();
            fflush(stdin);
        }
        else
            exit = true;
    }
    return valueToCheck;
}
// класс по работе с деками
class Deque_work
{
private:
    // методы 
    void _add(bool back)
    {
        back ? mainDeque.push_back((check_int("Введите добавляемое значение: "))) : mainDeque.push_front((check_int("Введите добавляемое значение: ")));
    }
    void _delete(bool back)
    {
        if (mainDeque.size() != 0)
            back ? mainDeque.pop_back() : mainDeque.pop_front();
        else
        {
            cout << "Двусвязная очередь переполнена";
            cin.get();
        }
    }
    void _print()
    {
        system("cls");
        cout << "Текущее состояние двусвязной очереди: ";
        for (auto i : mainDeque)
            cout << i << " ";
        cout << endl << endl;
    }
    // поля 
    deque<int> mainDeque; 
public:
    //методы 
    void _deque_menu()
    {
        char select;
        do
        {
            cout << "Меню работы с двусвязными очередями\n";
            _print();
            cout << "1. Добавить элемент в конец очереди\n2. Добавить яэлемент в начало очереди\n"
                << "3. Удалить элемент в конце очереди\n4. Удалить элемент в начале очереди\n5. Выход\n";
            select = _getch();
            // вызов функции в зависимости от выбраного варианта
            switch (select)
            {
            case '1': _add(true);     break;
            case '2': _add(false);    break;
            case '3': _delete(true);  break;
            case '4': _delete(false); break;
            }
        } while (select != '5');
    }
   
};
// класс для проверки полиндрома
class Polyndrom
{
private:
    // методы
    bool polyndrom_check()
    {
        /* основная функция проверки строки */
        string polyndromString = enter_string();
        int i = 0, j = polyndromString.length() - 1;
        for (; i < polyndromString.length() / 2 - 1; i++)
            if (polyndromString[i] != polyndromString[j] && i != j--)
                return false;
        return true;
    }
    string enter_string()
    {
        /* функция для ввода строки проверяемой на плоиндромиальность */
        string polyndromString;
        cout << "Введите строку: ";
        cin >> polyndromString;
        return polyndromString;
    }
public:
    // методы
    void getPolyndromCheck()
    {
        system("cls");
        polyndrom_check() ? cout << "Введённая строка явяется полиндромом\n" : cout << "Введенная строка не является полиндромом\n";
        _getch();
    }
};
// класс для польской нотации
class P_Notation
{
private:
    // методы
    void pNotation_convert()
    {

        int i = 0;

        while (i < s_in.length())
        {
            if (s_in[i] == ')')
            {
                /* при условии закрывающейся скобки, происходит добавление в основной стек всех операаций с конца до начала скобки */
                while (!opers.empty() && opers.top() != '(')
                {
                    s_out.push(opers.top()); // добавление новой операции d стек
                    opers.pop(); // удаление знака из стека операций 
                }
                if (!opers.empty())
                    opers.pop(); // удаление оставшегося знака из стека операций
            }
            else if (s_in[i] == '(')
                opers.push(s_in[i]); // начало новой скобки
            else if (isOper(s_in[i]))
            {
                /* в случаи нахождения на знак операции, добавление в основной стек всех операций с более низким приоритетом, чем текущий знак */
                while (!opers.empty() && isOper(opers.top()) && priority(opers.top()) >= priority(s_in[i]))
                {
                    s_out.push(opers.top()); // добавление новой операции d стек
                    opers.pop(); // удаление знака из стека операций 
                }
                opers.push(s_in[i]); // добавление текущего знака
            }
            else if (isNumber(s_in[i]))
                s_out.push(s_in[i]); // добавление числа в основной стек
            i++;
        }
        /* добаление в основной стек всех оставшихся элементов из стека opers */
        while (!opers.empty())
        {
            s_out.push(opers.top());
            opers.pop();
        }
    }
    void select_string()
    {
        /* выбор строки для конвертации */
        char select;
        do
        {
            system("cls");
            cout << "Выберите выражение\n1. (A - B - C) / D - E * F\n2. (A + B) * C - (D + E) / F \n3. A / (B - C) + D * (E - F)\n4. (A *B + C) / D - F / E\n";
            select = _getch();
        } while (select != '1' && select != '2' && select != '3' && select != '4');

        switch (select)
        {
        case '1': s_in = "(A-B-C)/D -E*F";  break;
        case '2': s_in = "(A+B)*C-(D+E)/F"; break;
        case '3': s_in = "A/(B-C)+D*(E-F)"; break;
        case '4': s_in = "(A*B+C)/D-F/E";   break;
        }
    }
    int priority(char c)
    {
        /* определяет приоритет операции */
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
    }
    void clean_and_print_postfix()
    {
        /* вывод строки в постфиксной форме на экран */
        cout << "Строка в постфиксной форме: ";
        string s_helper;
        // цикл создан для удаления всех элементов из стека и переноса их в строку для вывода 
        while (!s_out.empty())
        {
            s_helper += s_out.top();
            s_out.pop();
        }
        // изначально элементы в стек были занесены в неправильном порядке, для польской нотации нужен обратный порядок
        reverse(s_helper.begin(), s_helper.end()); // переворот строки, то есть первый символ становится последним, последний - первым и так далее
        cout << s_helper;
    }
    bool isNumber(char c)
    {
        /* функция для определения символа */
        return c >= 'A' && c <= 'Z';
    }
    bool isOper(char c)
    {
        /* функция для определения операции */
        return (c == '*' || c == '/' || c == '+' || c == '-');
    }
    // поля
    string s_in;
    stack<char> s_out, opers;
public:
    // методы
    void final_notation()
    {
        select_string();
        pNotation_convert();
        clean_and_print_postfix();

        cin.get();
    }
};

int main()
{
   setlocale(LC_ALL, "Russian");
   // инициализация
   Deque_work _deque;
   Polyndrom polyndrom;
   P_Notation postfix;

   char select;
   do
   {
       system("cls");
       cout << "Главное меню\n1. Двусвязная очередь\n2. Полиндром\n3. Польская нотация\n4. Выход\n";
       select = _getch();
       switch (select)
       {
       case '1': 
           _deque._deque_menu(); 
           break;
       case '2':
           polyndrom.getPolyndromCheck();
           break;
       case '3':
           postfix.final_notation();
           break;
       }
   } while (select != '4');

   return 0;
}
