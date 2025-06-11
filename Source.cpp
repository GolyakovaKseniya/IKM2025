#include "Header.h"
ExpressionError::ExpressionError(const string& Message) : Messages(Message) {}
const string& ExpressionError:: Message() const
{
    return Messages;
}
TreeNode::TreeNode(const string& Node) : Value(Node), Left(nullptr), Right(nullptr) {} //�����������

StackNode::StackNode(int Capacity) : Capacity(Capacity), TopIndex(-1) //�����������
{
    Data = new TreeNode * [Capacity]; //��������� ������ ��� �����
}
StackNode::~StackNode() //����������
{
    delete[] Data; //������������ ������
}

void StackNode::Push(TreeNode* Node) //���������� � ������
{
    if (TopIndex >= Capacity - 1)
    {
        throw ExpressionError("������: ���� ����� ����������.");
    }
    Data[++TopIndex] = Node;
}

TreeNode* StackNode::Pop() //�������� �����
{
    if (TopIndex < 0)
    {
        throw ExpressionError("������: ���� ����� ����.");
    }
    return Data[TopIndex--];
}

bool StackNode::IsEmpty() const //�������� �� �������
{
    return TopIndex < 0;
}
Stack::Stack(int Capacity) : Capacity(Capacity), TopIndex(-1) //�����������
{
    Data = new double[Capacity]; //��������� ������ ��� �����
}

Stack::~Stack() //����������
{
    delete[] Data; //������������ ������
}

void Stack::Push(double Value) //���������� � ����
{
    if (TopIndex >= Capacity - 1)
    {
        throw ExpressionError("������: ���� ����������.");
    }
    Data[++TopIndex] = Value;
}

double Stack::Pop() //�������� �������� �������� �����
{
    if (TopIndex < 0)
    {
        throw ExpressionError("������: ���� ����.");
    }
    return Data[TopIndex--];
}

double Stack::Top() const //����������� �������� �������� �����
{
    if (TopIndex < 0)
    {
        throw ExpressionError("������: ���� ����.");
    }
    return Data[TopIndex];
}

bool Stack::IsEmpty() const //�������� �� �������
{
    return TopIndex < 0;
}

int Stack::Size() const //����������� ������� �����
{
    return TopIndex + 1;
}

//������� ��� ��������, �������� �� ������� ������
bool IsNumber(const string& Token)
{
    if (Token.empty())
    {
        return false;
    }

    //���������, ��� ������ ����� �� '0'
    if (Token[0] == '0' && Token.length() > 1)
    {
        return false;
    }

    //���������, ������� �� ������� ������ �� ���� ��� �����
    bool HasDecimalPoint = false;
    for (char Char : Token)
    {
        if (!isdigit(Char))
        {
            if (Char == '.' && !HasDecimalPoint) //� �������� ������ ���� ������ 1 �����
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

//������� ��� ��������, �������� �� ������� ����������
bool IsOperator(const string& Token)
{
    return Token.size() == 1 && (Token == "+" || Token == "-" || Token == "*" || Token == "/");
}

//������� ��� ���������� ��������
double ApplyOperator(double One, double Two, const string& Operation)
{
    if (Operation == "+") return One + Two;
    else if (Operation == "-") return One - Two;
    else if (Operation == "*") return One * Two;
    else if (Operation == "/")
    {
        if (Two == 0)
        {
            throw ExpressionError("������: ������� �� ����.");
        }
        return  One / Two;
    }
    throw ExpressionError("������: ����������� �������� " + Operation);
}

//������� ��� ���������� ��������� � ����������� ������
double Calculating�TheExpression(const string& Expression)
{
    Stack SStack(100); //���� �� 100 ���������
    string Token;
    int OperatorCount = 0; //���������� ����������
    char PrevChar = ' '; //���������� �������
    stringstream Element(Expression);
    double Two, One, Result;

    while (Element >> Token)
    {
        // ��������� ������� ��������
        if (PrevChar != ' ' && Element.peek() != ' ')
        {
            throw ExpressionError("������: ��������� ������ ���� ��������� ���������.");
        }
        PrevChar = ' ';
        if (IsNumber(Token))
        {
            SStack.Push(stod(Token)); //�������������� ������ � ����� � ���������� � ����
        }
        else if (IsOperator(Token))
        {
            //�������� ���������� ��������� � �����
            if (SStack.IsEmpty())
            {
                throw ExpressionError("������: ������������ ��������� ��� ��������.");
            }
            Two = SStack.Pop(); //���������� Two - ������� �������
            if (SStack.IsEmpty())
            {
                throw ExpressionError("������: ������������ ��������� ��� ��������.");

            }
            One = SStack.Pop(); //���������� One - ��������� �������
            Result = ApplyOperator(One, Two, Token); //��������� ��������
            SStack.Push(Result);
            OperatorCount++;
        }
        else
        {
            throw ExpressionError("������: ����������� ����� " + Token);
        }
    }
    if (SStack.IsEmpty())
    {
        throw ExpressionError("������: ��������� �����������.");
    }
    if (SStack.Size() != 1)
    {
        throw ExpressionError("������: �������� ���������� ��������� � ����������");
    }
    if (OperatorCount < SStack.Size())
    {
        throw ExpressionError("������: ���������� ���������� ���������� �� ��������� � ����������.");
    }
    return SStack.Top();
}
//������� ��� ���������������� ������
void OutputResult(double Result)
{
    cout << "���������: " << fixed << setprecision(3) << Result << endl; // ����� � 6 ������� ����� �������
}
//������� ��� ���������� ������ ���������
TreeNode* buildExpressionTree(const string& Expression)
{
    StackNode Stack(100); //������� ���� ��� �����
    stringstream Element(Expression);
    string Token;

    while (Element >> Token)
    {
        if (IsNumber(Token))
        {
            Stack.Push(new TreeNode(Token)); //������� ���� �����
        }
        else if (IsOperator(Token))
        {
            if (Stack.IsEmpty())
            {
                throw ExpressionError("������: ������������ ��������� ��� ��������.");
            }
            TreeNode* RightNode = Stack.Pop(); //����� ������ �������
            if (Stack.IsEmpty())
            {
                throw ExpressionError("������: ������������ ��������� ��� ��������.");
            }
            TreeNode* LeftNode = Stack.Pop(); //����� ����� �������
            TreeNode* OperatorNode = new TreeNode(Token); //������� ���� ��������

            //������������� ����
            OperatorNode->Left = LeftNode;
            OperatorNode->Right = RightNode;

            Stack.Push(OperatorNode); //��������� �������� � ����
        }
        else
        {
            throw ExpressionError("������: ����������� ����� " + Token);
        }
    }

    if (Stack.IsEmpty())
    {
        throw ExpressionError("������: ��������� �����������.");
    }

    return Stack.Pop();
}
//������� ��� �������� ������ ������
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

//������� ��� ������������ ������ ������
void DeleteExpressionTree(TreeNode* Root)
{
    if (Root)
    {
        DeleteExpressionTree(Root->Left);
        DeleteExpressionTree(Root->Right);
        delete Root;
    }
}
int GetValidIntegerInput() //�������� �� ����
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
            cout << "������, ������� ����� ����� ";
        }
    }
}