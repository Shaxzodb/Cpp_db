#include <iostream>
#include <string>
#include <sqlite3.h>
#include <fmt/format.h>

using namespace std;
using namespace fmt;
static int callbacks(void *NotUsed, int argc, char **argv, char **azColName)
{

    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for(int i = 0; i < argc; i++) {
        
        // Show column name, value, and newline
        
        cout << azColName[i] << " = " << argv[i] << endl;

    
    }

    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}

int main(int argc, char** argv)
{
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("example.db", &DB);

    if (exit) 
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else 
    {
        std::cout << "Opened Database Successfully!" << std::endl;
       

        try
        {
            // create database

            /**
            * @brief sql buyrug'i
            * @param {string} sql - databasa sql buyrug'i
            */
            string sql =
                """CREATE TABLE COMPANY(    \
                ID INT PRIMARY KEY NOT NULL,\
                NAME TEXT NOT NULL,         \
                AGE INT NOT NULL,           \
                ADDRESS CHAR(50),           \
                SALARY REAL);""";
            exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, NULL);

            if (exit)
            {
                throw 500;
            }
            else 
            {
                std::cout << "Table created successfully!" << std::endl;
                throw 200;
            }
        }
        catch (...)
        {
            //create data
            string data;
            
            cout << "Malumot Kiritasizmi? - (Y/N):" << endl;
            cin >> data;
            if (data == "Y"){
                
                int id, age, salary;
                cout << "ID:";
                cin >> id;
                cout << "AGE:";
                cin >> age;
                cout << "SALARY:";
                cin >> salary;
                string name ,address;
               
                cout << "NAME:";
                getline(cin >> ws, name);

                cout << "ADDRESS:";
                getline(cin>>ws, address);
                /**
                * @brief sql buyrug'i
                * @param {string} sql - databasa sql buyrug'i
                */
                string sql1 =
                format(
                    """INSERT INTO COMPANY       \
                    (ID,NAME,AGE,ADDRESS,SALARY)    \
                    VALUES ({},'{}',{},'{}',{}); """,
                    id,name,age,address,salary
                );

                exit = sqlite3_exec(DB, sql1.c_str(), NULL, NULL, NULL);
                if (exit)
                {
                    std::cerr << "Error creating data " << sqlite3_errmsg(DB) << std::endl;
                    return (-1);
                }
                else
                {
                std::cout << "Data created successfully!" << std::endl;
                }
            }

           
            
            //read data
            /**
            * @brief sql buyrug'i
            * @param {string} sql - databasa sql buyrug'i
            */
            string sql = 
                "SELECT * FROM COMPANY;";
            exit = sqlite3_exec(DB, sql.c_str(), callbacks, NULL, NULL);
            if (exit)
            {
                std::cerr << "Error reading data " << sqlite3_errmsg(DB) << std::endl;
                return (-1);
            }
            else
            {
                std::cout << "Data read successfully!" << std::endl;

            }

        }
       
        
    }
    sqlite3_close(DB);
    return (0);
}