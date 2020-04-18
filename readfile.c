/***************************************************************************************
Copyright: 2020 cs402 sp-lab1
File name: readfile.c
Description: For this lab,implement an employee database program in C.
             Your program will store employee information in an array of employee structs,
             sorted by employee ID value. Your program will read in employee data from an 
             input file when it starts-up.Your program should print out a menu of transaction
             options, read in the user's selection, perform the chosen operation on the employee
             database, and repeat until told to quit. The options your program must support are 
             the following (Do not change the numbering of these menu options in your program 
             (i.e. menu option 2 must be look up by ID, option 5 must be quit, etc.)):
             1.Print the Database
             2.Lookup employee by ID
             3.Lookup employee by last name
             4.Add an Employee
             5.Quit
Author:YangQi
Version: v3.0
Date: 04/15/2020
History:    <author>    <time>       <version >   <desc>
             YangQi   04/12/2020       v1.0       build this mudual
             YangQi   04/13/2020       v2.0       build functions and header file
             YangQi   04/15/2020       v3.0       add qsort() and binary search method
             YangQi   04/16/2020       v4.0       debug function2 and function3
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

/*check command line*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("you need to enter your filename\n");
        return 0;
    }
    /*define variables and struct*/
    char *filename = argv[1], first_name[MAXNAME], last_name[MAXNAME];
    struct person employee[MAXNAME];
    int choice, e_id, salary, key, select;
    /*check file*/
    int n_emp = 0, list[MAXEMPLOYEE];
    if (open_file(filename) == -1)
    {
        printf("error: the file cannot be opened\n");
        return -1;
    }
    /*read file*/
    FILE *fp = fopen(filename, "r");
    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s %d\n", &employee[n_emp].id, &employee[n_emp].first_name, &employee[n_emp].last_name,
               &employee[n_emp].salary);
        n_emp++;
    }
    fclose(fp);
    qsort(employee, n_emp, sizeof(struct person), IDcompare);//call qsort() method;
    for (int i = 0; i < n_emp; i++)
    {
        list[i] = employee[i].id;
    }

    while (1)
    {
        printf("*********************************\n");
        printf("Employee DB Menu:\n");
        printf("*********************************\n");
        printf("(1) Print the Database\n");
        printf("(2) Lookup by ID\n");
        printf("(3) Lookup by Last Name\n");
        printf("(4) Add an Employee\n");
        printf("(5) Quit\n");
        printf("*********************************\n");
        printf("Enter your choice: ");
        read_int(&choice);
        /*function1:print the database*/
        if (choice == 1)
        {
            printf("----------------------------------------------\n");
            printf("First_name      Last_name     SALARY    ID\n");
            printf("----------------------------------------------\n");

            for (int i = 0; i < n_emp; i++)
            {
                printf("%-10s %-10s %10d %10d \n", employee[i].first_name, employee[i].last_name, employee[i].salary,
                       employee[i].id);
            }
            printf("----------------------------------------------\n");
            printf("Number of employees: %d\n", n_emp);
        }
        /*function2:look up employee by ID*/
        else if (choice == 2)
        {

            printf("enter a 6 digit employee id: ");
            scanf(" %d", &e_id);
            key = binary_search(list, 0, n_emp, e_id);//call binary_search() method;
            if (key == -1)
            {
                printf("employee with id %d is Not found\n", e_id);
            }
            else
                print_by_key(employee, key);
        }
        /*function3:lookup employee by Last name*/
        else if (choice == 3)
        {
            printf("enter employee's lastname:\n");
            read_string(last_name);
            key = search_lastname(employee, n_emp, last_name);//call search_lastname() method;
            if (key == -1)
                printf("employee with last name %s is Not found\n", last_name);
            else
                print_by_key(employee, key);// call print_by_key() method;
        }
         /*function4:add an employee*/
        else if (choice == 4)
        {
            printf("enter employee's firstname:\n");
            read_string(first_name);
            printf("enter employee's lastname:\n");
            read_string(last_name);
            printf("enter employee's salary(between $30,000 and $150,000):\n");
            read_int(&salary);
            printf("do you want to add the following employee to the DB?\n");
            printf("%s %s, salary: %d \n", first_name, last_name, salary);
            printf("enter 1 for yes, 0 for no\n");
            read_int(&select);
            if (select == 1)
            {
                if ((salary >= 30000) && (salary <= 150000))
                {
                    int last_id = employee[n_emp - 1].id;
                    int input_id = last_id + 1;
                    strcpy(employee[n_emp].first_name, first_name);// string copy function;
                    strcpy(employee[n_emp].last_name, last_name);
                    employee[n_emp].salary = salary;
                    employee[n_emp].id = input_id;
                    list[n_emp] = employee[n_emp].id;
                    n_emp++;
                }
                else
                {
                    printf("salary is not right,please enter another one.\n");
                }
            }
            else
            {
                printf("don't add this person to DB.\n");
            }
        }
        /*function5:quit*/
        else if (choice == 5)
        {
            printf("goodbye!\n");
            break;
        }
        else
        {
            printf("Hey, %d is not between 1 and 5, try again...\n");
            continue;
        }
    }
}

