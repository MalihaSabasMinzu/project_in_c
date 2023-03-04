#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct product
{
    char name[30];
    int ID;
    float cgpa;
} pro;

void read_from_file(pro students[], int *i)
{
    FILE *data;
    data = fopen("data.txt", "r");
    if (fgetc(data) == EOF)
    {
        return;
    }
    fclose(data);
    data = fopen("data.txt", "r");
    if (data == NULL)
    {
        printf("Can't Open the file. Try again.");
        return;
    }
    do
    {
        char ch = ' ';
        int j = 0;
        while (ch != '-' && ch != -1)
        {
            ch = fgetc(data);
            if (ch != '-' && ch != '\n' && ch != -1)
            {
                students[*i].name[j] = ch;
            }
            j++;
        }
        students[*i].name[j - 1] = '\0';
        if (ch == -1)
        {
            break;
        }

        fscanf(data, "%d-%f", &students[*i].ID, &students[*i].cgpa);
        (*i)++;
    } while (fgetc(data) != -1);
    fclose(data);
}
void display_main()
{
    printf("\nPress 1 to Add a new Student."
           "\nPress 2 to Display All students sorted by ID."
           "\nPress 3 to Display Students sorted by CGPA."
           "\nPress 4 to Delete a Student Information."
           "\nPress 5 to Update a students Information."
           "\nPress 6 to Search a students Info by ID."
           "\nPress 7 to Exit the program."
           "\nPlease enter a number (1-7) : ");
}

void add_student(pro students[], int *i)
{
    printf("\n\n----Add a New Student----\n\n");
    fflush(stdin);
    printf("Please Enter the Student name (1-30 characters): ");
    gets(students[*i].name);
    printf("\nPlease Enter the Student ID (1-10 numbers): ");
    scanf("%d", &students[*i].ID);
    printf("\nPlease Enter the Student's CGPA (1 int & 2 float): ");
    scanf("%f", &students[*i].cgpa);

    FILE *data;
    data = fopen("data.txt", "a");
    if (data == NULL)
    {
        printf("\nSomething went wrong. Can't open the file.\n");
        return;
    }
    fprintf(data, "%s-%d-%1.2f\n", students[*i].name, students[*i].ID, students[*i].cgpa);
    fclose(data);
    printf("\nNew Student Added Successfully.\n");
    (*i)++;
}

void quicksort(pro students[], int first, int last, int check)
{
    int left, right, pivot;
    pro temp;
    if (first < last)
    {
        pivot = left = first;
        right = last;
        while (left < right)
        {
            if (check)
            {
                while (students[pivot].cgpa <= students[left].cgpa && left < right)
                    left++;
                while (students[pivot].cgpa > students[right].cgpa)
                    right--;
            }
            else
            {
                while (students[left].ID <= students[pivot].ID && left < right)
                    left++;
                while (students[right].ID > students[pivot].ID)
                    right--;
            }

            if (left < right)
            {
                temp = students[left];
                students[left] = students[right];
                students[right] = temp;
            }
        }
        temp = students[pivot];
        students[pivot] = students[right];
        students[right] = temp;
        quicksort(students, first, right - 1, check);
        quicksort(students, right + 1, last, check);
    }
}

void display_by_Id(pro students[], int *total)
{
    printf("\n\nDisplaying Students sorted by ID.\n\n");
    printf("%3s \t%-30s \t %-15s %-10s\n", "No", "Name", "ID", "CGPA");
    quicksort(students, 0, *total - 1, 0);
    for (int i = 0; i < *total; i++)
    {
        printf("%3d.\t%-30s \t%-15d %-10.2f\n", i + 1, students[i].name, students[i].ID, students[i].cgpa);
    }
    printf("\n\n");
}

void display_by_cgpa(pro students[], int *total)
{
    printf("\n\nDisplaying Students sorted by CGPA.\n\n");
    printf("%3s \t%-30s \t %-15s %-10s\n", "No", "Name", "ID", "CGPA");
    quicksort(students, 0, *total - 1, 1);
    for (int i = 0; i < *total; i++)
    {
        printf("%3d.\t%-30s \t%-15d %-10.2f\n", i + 1, students[i].name, students[i].ID, students[i].cgpa);
    }
    printf("\n\n");
}

void delete(pro students[], int *size)
{
    int num, i = 0;
    printf("\n\nEnter the ID you want to delete : ");
    scanf("%d", &num);
    while (num != students[i].ID && i < *size)
    {
        i++;
    }
    if (i == *size)
    {
        printf("\nID not Found.\n\n");
        return;
    }
    printf("\nThis Student is Deleted:\n%-30s \t%-15d %-10.2f\n", students[i].name, students[i].ID, students[i].cgpa);

    while (i < *size - 1)
    {
        students[i] = students[i + 1];
        i++;
    }

    (*size)--;
    FILE *data;
    data = fopen("data.txt", "w");
    if (data == NULL)
    {
        printf("\nSomething went wrong. Can't open the file.\n");
        return;
    }
    for (int j = 0; j < *size; j++)
    {
        fprintf(data, "%s-%d-%1.2f\n", students[j].name, students[j].ID, students[j].cgpa);
    }

    fclose(data);
    printf("\nStudent Deleted Successfully.\n");
}
void update(pro students[], int *size)
{
    int num, i = 0;
    printf("\n\nEnter the ID you want to update : ");
    scanf("%d", &num);
    while (num != students[i].ID && i < *size)
    {
        i++;
    }
    if (i == *size)
    {
        printf("\nID not Found.\n\n");
        return;
    }
    printf("Previous name is : %-30s\nNew name will be: ", students[i].name);
    fflush(stdin);
    gets(students[i].name);
    printf("Previous ID is : %-10d\nNew ID will be: ", students[i].ID);
    scanf("%d", &students[i].ID);
    printf("Previous CGPA is : %-1.2f\nNew CGPA will be: ", students[i].cgpa);
    scanf("%f", &students[i].cgpa);

    FILE *data;
    data = fopen("data.txt", "w");
    if (data == NULL)
    {
        printf("\nSomething went wrong. Can't open the file.\n");
        return;
    }
    for (int j = 0; j < *size; j++)
    {
        fprintf(data, "%s-%d-%1.2f\n", students[j].name, students[j].ID, students[j].cgpa);
    }

    fclose(data);
    printf("\nStudent Updated Successfully.\n");
}
void search(pro students[], int *size)
{
    int num, i = 0;
    printf("\n\nEnter the ID you want to search : ");
    scanf("%d", &num);
    while (num != students[i].ID && i < *size)
    {
        i++;
    }
    if (i == *size)
    {
        printf("\nID not Found.\n\n");
        return;
    }
    printf("Name is : %-30s\n", students[i].name);
    printf("ID is : %-10d\n", students[i].ID);
    printf("CGPA is : %-1.2f\n", students[i].cgpa);
}

void input(pro students[], int *stu_count)
{
    while (1)
    {
        display_main();
        switch (getch())
        {
        case '1':
            printf("1\n");
            add_student(students, stu_count);
            break;
        case '2':
            printf("2\n");
            display_by_Id(students, stu_count);
            break;
        case '3':
            printf("3\n");
            display_by_cgpa(students, stu_count);
            break;
        case '4':
            printf("4\n");
            delete (students, stu_count);
            break;
        case '5':
            printf("5\n");
            update(students, stu_count);
            break;
        case '6':
            printf("6\n");
            search(students, stu_count);
            break;
        case '7':
            printf("exit\n");
            exit(0);
            break;
        default:
            printf("\n\nPlease Enter a valid Number.\n\n"
                   " \nPlease enter a number (1-7) : ");
            break;
        }
    }
}

int main()
{
    int size = 100;
    int stu_count = 0;
    pro students[size];
    printf("\n\n--------------------------------------------------------");
    printf("\n\tWellcome to student management System.\n");
    printf("--------------------------------------------------------\n\n\n");
    read_from_file(students, &stu_count);
    input(students, &stu_count);

    return 0;
}