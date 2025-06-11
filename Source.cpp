#include "Header.h"
ExpressionError::ExpressionError(const string& Message) : Messages(Message) {}
const string& ExpressionError:: Message() const
{
    return Messages;
}
TreeNode::TreeNode(const string& Node) : Value(Node), Left(nullptr), Right(nullptr) {} //Конструктор

StackNode::StackNode(int Capacity) : Capacity(Capacity), TopIndex(-1) //Конструктор
{
    Data = new TreeNode * [Capacity]; //Выделение памяти для стека
}
StackNode::~StackNode() //Деструктор
{
    delete[] Data; //Освобождение памяти
}

void StackNode::Push(TreeNode* Node) //Добавление в дерево
{
    if (TopIndex >= Capacity - 1)
    {
        throw ExpressionError("Ошибка: стек узлов переполнен.");
    }
    Data[++TopIndex] = Node;
}

TreeNode* StackNode::Pop() //Удаление корня
{
    if (TopIndex < 0)
    {
        throw ExpressionError("Ошибка: стек узлов пуст.");
    }
    return Data[TopIndex--];
}

bool StackNode::IsEmpty() const //Проверка на пустоту
{
    return TopIndex < 0;
}
Stack::Stack(int Capacity) : Capacity(Capacity), TopIndex(-1) //Конструктор
{
    Data = new double[Capacity]; //Выделение памяти для стека
}

Stack::~Stack() //Деструктор
{
    delete[] Data; //Освобождение памяти
}

void Stack::Push(double Value) //Добавление в стек
{
    if (TopIndex >= Capacity - 1)
    {
        throw ExpressionError("Ошибка: стек переполнен.");
    }
    Data[++TopIndex] = Value;
}

double Stack::Pop() //Удаление верхнего элемента стека
{
    if (TopIndex < 0)
    {
        throw ExpressionError("Ошибка: стек пуст.");
    }
    return Data[TopIndex--];
}

double Stack::Top() const //Возвращение верхнего элемента стека
{
    if (TopIndex < 0)
    {
        throw ExpressionError("Ошибка: стек пуст.");
    }
    return Data[TopIndex];
}

bool Stack::IsEmpty() const //Проверка на пустоту
{
    return TopIndex < 0;
}

int Stack::Size() const //Возвращение размера стека
{
    return TopIndex + 1;
}

//Функция для проверки, является ли элемент числом
bool IsNumber(const string& Token)
{
    if (Token.empty())
    {
        return false;
    }

    //Проверяем, ЧТО первая цифра не '0'
    if (Token[0] == '0' && Token.length() > 1)
    {
        return false;
    }

    //Проверяем, состоит ли элемент только из цифр или точки
    bool HasDecimalPoint = false;
    for (char Char : Token)
    {
        if (!isdigit(Char))
        {
            if (Char == '.' && !HasDecimalPoint) //В элементе должна быть только 1 точка
            {
                HasDecimalPoint = true;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

//Функция для проверки, является ли элемент оператором
bool IsOperator(const string& Token)
{
    return Token.size() == 1 && (Token == "+" || Token == "-" || Token == "*" || Token == "/");
}

//Функция для выполнения операции
double ApplyOperator(double One, double Two, const string& Operation)
{
    if (Operation == "+") return One + Two;
    else if (Operation == "-") return One - Two;
    else if (Operation == "*") return One * Two;
    else if (Operation == "/")
    {
        if (Two == 0)
        {
            throw ExpressionError("Ошибка: деление на ноль.");
        }
        return  One / Two;
    }
    throw ExpressionError("Ошибка: неизвестный оператор " + Operation);
}

//Функция для вычисления выражения в постфиксной записи
double CalculatingеTheExpression(const string& Expression)
{
    Stack SStack(100); //Стек на 100 элементов
    string Token;
    int OperatorCount = 0; //Количество операторов
    char PrevChar = ' '; //Предыдущий элемент
    stringstream Element(Expression);
    double Two, One, Result;

    while (Element >> Token)
    {
        // Проверяем наличие пробелов
        if (PrevChar != ' ' && Element.peek() != ' ')
        {
            throw ExpressionError("Ошибка: выражение должно быть разделено пробелами.");
        }
        PrevChar = ' ';
        if (IsNumber(Token))
        {
            SStack.Push(stod(Token)); //Преобразование строки в число и добавляние в стек
        }
        else if (IsOperator(Token))
        {
            //Проверка количества операндов в стеке
            if (SStack.IsEmpty())
            {
                throw ExpressionError("Ошибка: недостаточно операндов для операции.");
            }
            Two = SStack.Pop(); //Переменная Two - верхний элемент
            if (SStack.IsEmpty())
            {
                throw ExpressionError("Ошибка: недостаточно операндов для операции.");

            }
            One = SStack.Pop(); //Переменная One - следующий элемент
            Result = ApplyOperator(One, Two, Token); //Выполняем действие
            SStack.Push(Result);
            OperatorCount++;
        }
        else
        {
            throw ExpressionError("Ошибка: неизвестный токен " + Token);
        }
    }
    if (SStack.IsEmpty())
    {
        throw ExpressionError("Ошибка: выражение некорректно.");
    }
    if (SStack.Size() != 1)
    {
        throw ExpressionError("Ошибка: неверное количество операндов и операторов");
    }
    if (OperatorCount < SStack.Size())
    {
        throw ExpressionError("Ошибка: избыточное количество операторов по сравнению с операндами.");
    }
    return SStack.Top();
}
//Функция для форматированного вывода
void OutputResult(double Result)
{
    cout << "Результат: " << fixed << setprecision(3) << Result << endl; // Вывод с 6 знаками после запятой
}
//Функция для построения дерева выражения
TreeNode* buildExpressionTree(const string& Expression)
{
    StackNode Stack(100); //Создаем стек для узлов
    stringstream Element(Expression);
    string Token;

    while (Element >> Token)
    {
        if (IsNumber(Token))
        {
            Stack.Push(new TreeNode(Token)); //Создаем узел числа
        }
        else if (IsOperator(Token))
        {
            if (Stack.IsEmpty())
            {
                throw ExpressionError("Ошибка: недостаточно операндов для операции.");
            }
            TreeNode* RightNode = Stack.Pop(); //Берем правый операнд
            if (Stack.IsEmpty())
            {
                throw ExpressionError("Ошибка: недостаточно операндов для операции.");
            }
            TreeNode* LeftNode = Stack.Pop(); //Берем левый операнд
            TreeNode* OperatorNode = new TreeNode(Token); //Создаем узел операции

            //Устанавливаем узлы
            OperatorNode->Left = LeftNode;
            OperatorNode->Right = RightNode;

            Stack.Push(OperatorNode); //Добавляем оператор в стек
        }
        else
        {
            throw ExpressionError("Ошибка: неизвестный токен " + Token);
        }
    }

    if (Stack.IsEmpty())
    {
        throw ExpressionError("Ошибка: выражение некорректно.");
    }

    return Stack.Pop();
}
//Функция для бокового вывода дерева
void PrintExpressionTree(TreeNode* Root, int Level, bool Flag, const string& Expression)
{
    if (Root)
    {
        PrintExpressionTree(Root->Right, Level + 3, true, Expression + (Flag ? "    " : "|  "));
        cout << Expression;
        cout << (Flag ? "--- " : "--- ");
        cout << Root->Value << endl;
        PrintExpressionTree(Root->Left, Level + 3, false, Expression + (Flag ? "|   " : "    "));
    }
}

//Функция для освобождения памяти дерева
void DeleteExpressionTree(TreeNode* Root)
{
    if (Root)
    {
        DeleteExpressionTree(Root->Left);
        DeleteExpressionTree(Root->Right);
        delete Root;
    }
}
int GetValidIntegerInput() //Проверка на ввод
{

    while (true)
    {
        string Number;
        getline(cin, Number);
        istringstream Element(Number);
        int Data;
        char Char;
        if (Element >> Data && !(Element >> Char))
        {
            return Data;
        }
        else
        {
            cout << "Ошибка, введите целое число ";
        }
    }
}