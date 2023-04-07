#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;
ifstream inFile;  //输入文件
int errorNum = 0; //错误数
//所有字符种类（关键字、标识符、常量、运算符、分隔符、不可识别）
const string token[6] = {"Keyword", "Identifier", "Constant", "Operation", "Delimiter", "Unidentifiable"};
//定义一个输出函数，输出已经分析好的词法分析结果
void output(string str, int id)
{
    cout << "<" << setw(10) << str << setw(5) << "," << setw(15) << token[id] << setw(5) << ">\n";
    if (id == 5)
        errorNum++;
}

//判断字符是否为字母
bool isLetter(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return true;
    else
        return false;
}

//判断字符是否为数字
bool isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

//是否是空格，回车，制表符
bool isUesless(char ch)
{
    if (ch == ' ' || ch == '\0' || ch == '\n' || ch == '\t')
        return true;
    else
        return false;
}

//关键字
const string keywords[16] = {"program", "begin", "end", "if", "else", "while", "do", "return", "int", "float", "double", "char", "bool", "void", "read", "write"};
//运算符
const char operation[] = {'+', '-', '*', '/', '=', '>', '<', '!', '&', '|'};
//{"+", "-", "*", "/", "=", ">", "<", "!", "+=", "-=", "*=", "/=", "==", ">=", "<=", "!=", "&&", "||","++","--  " };
//分隔符
const char delimiter[] = {',', ';', '(', ')', '{', '}', '[', ']'};

//判断是否是关键字
bool isKeyword(string str)
{
    for (int i = 0; i < 16; i++)
    {
        if (keywords[i] == str)
        {
            return true;
        }
    }
    return false;
}

//判断是否是运算符
bool isOperation(char ch)
{

    for (int i = 0; i < 10; i++)
    {
        if (operation[i] == ch)
            return true;
    }
    return false;
}

//判断是否是分隔符
bool isDelimiter(char ch)
{
    for (int i = 0; i < 8; i++)
    {
        if (delimiter[i] == ch)
            return true;
    }
    return false;
}

//首字符为字母的识别
void onLetter(string str)
{
    //检查str中是否有非法字符
    for (int i = 0; i < str.size(); i++)
    {
        if (!isLetter(str[i]) && !isDigit(str[i]))
        {
            output(str, 5);
            return;
        }
    }
    // 如果是 true false
    if (str == "true" || str == "false")
    {
        output(str, 2);
        return;
    }
    //判断是否是关键字
    if (isKeyword(str))
    {
        output(str, 0);
    }
    else
    {
        output(str, 1);
    }
}

//首字符为数字的识别
void onDigit(string str)
{
    int pos = 0;
    while (isDigit(str[pos]))
    {
        pos++;
    }
    if (str[pos] == '.')
    {
        pos++;
        while (isDigit(str[pos]))
        {
            pos++;
        }
        if (pos == str.size())
        {
            output(str, 2);
        }
        else
        {
            output(str, 5);
        }
    }
    else
    {
        if (pos == str.size())
        {
            output(str, 2);
        }
        else
        {
            output(str, 5);
        }
    }
}

//处理word
void solveWord(string str)
{
    // str 的第一个字符是字母,onLetter
    if (isLetter(str[0]))
    {
        onLetter(str);
    }
    // str 的第一个字符是数字,onDigit
    else if (isDigit(str[0]))
    {
        onDigit(str);
    }
    //不是字母也不是数字，不可识别
    else
    {
        output(str, 5);
    }
}

//处理运算符
char solveOpration(char ch)
{
    char str[3];
    switch (ch)
    {
    case '+':
        str[0] = ch;
        ch = inFile.get();
        if (ch == '=' || ch == '+')
        {
            str[1] = ch;
            str[2] = '\0';
            output(str, 3);
            ch = inFile.get();
            return ch;
        }
        else
        {
            str[1] = '\0';
            output(str, 3);
            return ch;
        }
        break;
    case '-':
        str[0] = ch;
        ch = inFile.get();
        if (ch == '=' || ch == '-')
        {
            str[1] = ch;
            str[2] = '\0';
            output(str, 3);
            ch = inFile.get();
            return ch;
        }
        else
        {
            str[1] = '\0';
            output(str, 3);
            return ch;
        }
        break;
    case '*':
    case '/':
    case '=':
    case '<':
    case '>':
    case '!':
        str[0] = ch;
        ch = inFile.get();
        if (ch == '=')
        {
            str[1] = ch;
            str[2] = '\0';
            output(str, 3);
            ch = inFile.get();
            return ch;
        }
        else
        {
            str[1] = '\0';
            output(str, 3);
            return ch;
        }
        break;
    case '&':
        str[0] = ch;
        ch = inFile.get();
        if (ch == '&')
        {
            str[1] = ch;
            str[2] = '\0';
            output(str, 3);
            ch = inFile.get();
            return ch;
        }
        else
        {
            str[1] = '\0';
            output(str, 5);
            return ch;
        }
        break;
    case '|':
        str[0] = ch;
        ch = inFile.get();
        if (ch == '|')
        {
            str[1] = ch;
            str[2] = '\0';
            output(str, 3);
            ch = inFile.get();
            return ch;
        }
        else
        {
            str[1] = '\0';
            output(str, 5);
            return ch;
        }
        break;
    default:
        //好像没必要
        str[0] = ch;
        str[1] = '\0';
        output(str, 5);
        ch = inFile.get();
        return ch;
        break;
    }
}

int main()
{
    string filename;
    cout << "Please enter the path and name of the source file: (default to the test.txt file in the same directory)" << endl;
    //点击回车键，使用默认文件
    getline(cin, filename);
    // 如果filename为空,则默认为test.txt
    if (filename.empty())
    {
        filename = "test.txt";
    }
    //输出文件名
    cout << "The file name is: " << filename << endl;
    // 打开文件
    inFile = ifstream(filename, ios::in);
    // 如果文件打开失败,则报错
    if (!inFile)
    {
        cerr << "Unable to open file! " << filename.c_str() << endl;
        exit(-1);
    }
    // 打印文件中的内容
    cout << endl;
    char all[1000];
    inFile.getline(all, 1000, EOF);
    cout << "测试用例如下：\n"
         << all << endl;

    // 词法分析
    inFile = ifstream("test.txt", ios::in);
    //设置一个字符数组，用来存储读取的字符
    char word[100];
    char ch;
    int p = 0;
    ch = inFile.get();
    cout << "\n词法分析测试结果如下：\n"
         << "<" << setw(10) << "单词本身" << setw(5) << "," << setw(15) << "所属类别" << setw(5) << ">\n";
    while (ch != EOF)
    {
        //没有遇到空格，回车，制表符，运算符，分隔符，就继续读取字符，并存入word数组中处理
        if (!(isUesless(ch) || isOperation(ch) || isDelimiter(ch)))
        {
            word[p++] = ch;
            ch = inFile.get();
        }
        else
        {
            //遇到空格，回车，制表符，运算符，分隔符，就将word数组中的字符输出
            //处理一下word数组，将p置为0
            if (p != 0)
            {
                word[p] = '\0';
                solveWord(word);
                p = 0;
            }
            if (isUesless(ch))
            {
                ch = inFile.get();
            }
            if (isOperation(ch))
            {
                ch = solveOpration(ch);
            }
            if (isDelimiter(ch))
            {
                char str[2];
                str[0] = ch;
                str[1] = '\0';
                output(str, 4);
                ch = inFile.get();
            }
        }
    }
    if (p != 0)
    {
        word[p] = '\0';
        solveWord(word);
        p = 0;
    }
    cout << "\n词法分析成功！\n共\t" << errorNum << "\t个无法识别的单词。" << endl;
    inFile.close();
    return 0;
}