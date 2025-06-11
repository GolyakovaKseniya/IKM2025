#include "Header.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    string Expression;
    TreeNode* ExpressionTree;
    double Result;
    while (true)
    {
        cout << "Выберите действие:\n";
        cout << "1. Вычислить выражение\n";
        cout << "2. Выйти\n";
        cout << "Ваш выбор: ";
        int Choice;
        try
        {
            Choice = GetValidIntegerInput();

            switch (Choice)
            {
            case 1:
                cout << "Введите выражение в обратной польской записи :\n";
                getline(cin, Expression);
                try
                {
                    ExpressionTree = buildExpressionTree(Expression); //Строим дерево выражения
                    Result = CalculatingеTheExpression(Expression); //Вычисляем выражение
                    OutputResult(Result);
                    cout << "Дерево выражения:" << endl;
                    PrintExpressionTree(ExpressionTree); //Выводим дерево в боковом виде
                    cout << endl;
                    DeleteExpressionTree(ExpressionTree); //Освобождаем память дерева

                }
                catch (const ExpressionError& Error)
                {
                    cout << Error.Message() << endl; //Выводим сообщение об ошибке

                }
                cout << endl;
                break;

            case 2:
                cout << "Выход из программы." << endl;
                return 0;

            default:
                cout << "Ошибка: неверный выбор." << endl;
                continue;
            }
        }
        catch (const ExpressionError& Error)
        {
            cout << Error.Message() << endl; //Выводим сообщение об ошибке
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
