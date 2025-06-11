#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cctype> 
#include <stdexcept> 
#include <limits>
#include <iomanip>
using namespace std;

//���������������� ����������
class ExpressionError
{
public:
    explicit ExpressionError(const string& Message);
    const string& Message() const;
private:
    string Messages;
};
//��������� ��� ����� ������
struct TreeNode
{
    string Value; //�������� ��� ��������
    TreeNode* Left;   //����� �������
    TreeNode* Right;  //������ �������

    TreeNode(const string& Node);
};
//���� ��� ����� ������
class StackNode
{

public:
    StackNode(int Capacity); //�����������
    ~StackNode(); //����������
    void Push(TreeNode* Node); //���������� � ������
    TreeNode* Pop(); //�������� �����
    bool IsEmpty() const;//�������� �� �������
private:
    TreeNode** Data; //������ ��� �������� ���������� �� ���� �����
    int Capacity; //������ �����
    int TopIndex; //������ �������� �������� �����
};
// ����� ��� ���������� �����
class Stack
{
public:
    Stack(int Capacity); //�����������
    ~Stack(); //����������
    void Push(double Value); //���������� � ����
    double Pop(); //�������� �������� �������� �����
    double Top() const; //����������� �������� �������� �����
    bool IsEmpty() const;//�������� �� �������
    int Size() const; //����������� ������� �����
private:
    double* Data; //������ ��� �������� ��������� �����
    int Capacity; //������ �����
    int TopIndex; //������ �������� �������� �����
};
//������� ��� ��������, �������� �� ������� ������
bool IsNumber(const string& Token);
//������� ��� ��������, �������� �� ������� ����������
bool IsOperator(const string& Token);
//������� ��� ���������� ��������
double ApplyOperator(double One, double Two, const string& Operation);
//������� ��� ���������� ��������� � ����������� ������
double Calculating�TheExpression(const string& Expression);
//������� ��� ���������������� ������
void OutputResult(double Result);
//������� ��� ���������� ������ ���������
TreeNode* buildExpressionTree(const string& Expression);
//������� ��� �������� ������ ������
void PrintExpressionTree(TreeNode* Root, int Level = 0, bool Flag = false, const string& Expression = "");
//������� ��� ������������ ������ ������
void DeleteExpressionTree(TreeNode* Root);
int GetValidIntegerInput(); //�������� �� ����
