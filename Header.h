#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cctype> 
#include <stdexcept> 
#include <limits>
#include <iomanip>
using namespace std;

//Пользовательское исключение
class ExpressionError
{
public:
    explicit ExpressionError(const string& Message);
    const string& Message() const;
private:
    string Messages;
};
//Структура для узлов дерева
struct TreeNode
{
    string Value; //Операция или значение
    TreeNode* Left;   //Левый потомок
    TreeNode* Right;  //Правый потомок

    TreeNode(const string& Node);
};
//Стек для узлов дерева
class StackNode
{

public:
    StackNode(int Capacity); //Конструктор
    ~StackNode(); //Деструктор
    void Push(TreeNode* Node); //Добавление в дерево
    TreeNode* Pop(); //Удаление корня
    bool IsEmpty() const;//Проверка на пустоту
private:
    TreeNode** Data; //Массив для хранения указателей на узлы стека
    int Capacity; //Размер стека
    int TopIndex; //Индекс верхнего элемента стека
};
// Класс для реализации стека
class Stack
{
public:
    Stack(int Capacity); //Конструктор
    ~Stack(); //Деструктор
    void Push(double Value); //Добавление в стек
    double Pop(); //Удаление верхнего элемента стека
    double Top() const; //Возвращение верхнего элемента стека
    bool IsEmpty() const;//Проверка на пустоту
    int Size() const; //Возвращение размера стека
private:
    double* Data; //Массив для хранения элементов стека
    int Capacity; //Размер стека
    int TopIndex; //Индекс верхнего элемента стека
};
//Функция для проверки, является ли элемент числом
bool IsNumber(const string& Token);
//Функция для проверки, является ли элемент оператором
bool IsOperator(const string& Token);
//Функция для выполнения операции
double ApplyOperator(double One, double Two, const string& Operation);
//Функция для вычисления выражения в постфиксной записи
double CalculatingеTheExpression(const string& Expression);
//Функция для форматированного вывода
void OutputResult(double Result);
//Функция для построения дерева выражения
TreeNode* buildExpressionTree(const string& Expression);
//Функция для бокового вывода дерева
void PrintExpressionTree(TreeNode* Root, int Level = 0, bool Flag = false, const string& Expression = "");
//Функция для освобождения памяти дерева
void DeleteExpressionTree(TreeNode* Root);
int GetValidIntegerInput(); //Проверка на ввод
