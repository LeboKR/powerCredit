
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;
const int index = 1000;

string AccountUserInfo[index][8];
double cost;
int totalUsers = 0;

string fullnames[index];
string feedbacks[index];
int ID_numbers[index];
int member_no = 0;
float c_score;

float calculateCreditScoreRecursive(float latePayRate, float utilization, float cHistory, float loans, string newCred, int inquiry, int acc, int step = 1)
{
    float score = 0;
    if (step == 1)
    {
        float score1;
        if (latePayRate == 0)
            score1 = 100;
        else if (latePayRate <= 0.05)
            score1 = 85;
        else if (latePayRate <= 0.10)
            score1 = 75;
        else
            score1 = 65;
        return (score1 / 100) * 192.5 + calculateCreditScoreRecursive(latePayRate, utilization, cHistory, loans, newCred, inquiry, acc, step + 1);
    }
    else if (step == 2)
    {
        float score2;
        if (utilization < 10)
            score2 = 100;
        else if (utilization < 30)
            score2 = 85;
        else if (utilization < 50)
            score2 = 75;
        else
            score2 = 0;
        return (score2 / 100) * 165 + calculateCreditScoreRecursive(latePayRate, utilization, cHistory, loans, newCred, inquiry, acc, step + 3);
    }
    else if (step == 3)
    {
        float score3;
        if (cHistory >= 9)
            score3 = 100;
        else if (cHistory >= 6)
            score3 = 80;
        else if (cHistory >= 2)
            score3 = 69;
        else
            score3 = 0;
        return (score3 / 100) * 82.5 + calculateCreditScoreRecursive(latePayRate, utilization, cHistory, loans, newCred, inquiry, acc, step + 4);
    }
    else if (step == 4)
    {
        float score4;
        if (loans < 1)
            score4 = 0;
        else if (loans == 1)
            score4 = 25;
        else if (loans == 2)
            score4 = 35;
        else
            score4 = 100;
        return (score4 / 100) * 55 + calculateCreditScoreRecursive(latePayRate, utilization, cHistory, loans, newCred, inquiry, acc, step + 5);
    }
    else if (step == 5)
    {
        float score5;
        if (newCred == "yes" || newCred == "Yes")
        {
            if (inquiry == 1 || acc == 1)
                score5 = 75;
            else if (inquiry > 1 || acc > 1)
                score5 = 49;
            else
                score5 = 100;
        }
        else
        {
            score5 = 100;
        }
        return (score5 / 100) * 55;
    }
    else
    {
        return 0;
    }
}

float credScore()
{
    float latePay, totalPay, latePayRate;
    float noc, balance, limit, totalBalance = 0, totalLimit = 0, utilization;
    float duration, cHistory = 0;
    float loan1, loan2, loan3, loan4, loans;
    string newCred;
    int inquiry = 0, acc = 0;
    double c_score;

    cout << "\n--- Credit Score Calculator ---\n"<< endl;

    cout << "Payment History\nEnter the number of late payments: "<< endl;
    cin >> latePay;
    cout << "Enter total payments made: "<< endl;
    cin >> totalPay;
    if (totalPay > 0)
        latePayRate = latePay / totalPay;
    else
        latePayRate = 0;

    cout << "\nCredit Utilization\nHow many credit cards do you have? "<< endl;
    cin >> noc;

    for (int i = 1; i <= noc; i++)
    {
        cout << "Balance of card " << i << ": "<< endl;
        cin >> balance;
        totalBalance += balance;
        cout << "Limit of card " << i << ": "<< endl;
        cin >> limit;
        totalLimit += limit;
    }

    if (totalLimit > 0)
        utilization = (totalBalance / totalLimit) * 100;
    else
        utilization = 0;
    cout << fixed << setprecision(2) << "Utilization: " << utilization << "%\n"<< endl;

    for (int i = 1; i <= noc; i++)
    {
        cout << "Age of card " << i << " in years: "<< endl;
        cin >> duration;
        cHistory += (duration * 12);
    }

    if (noc > 0)
        cHistory = (cHistory / noc) / 12;
    else
        cHistory = 0;
    cout << "Average account age: ~" << cHistory << " years\n"<< endl;

    cout << "\nCredit Mix (0 = No, 1 = Yes)\n"<< endl;
    cout << "Do you have credit cards? "<< endl;
    cin >> loan1;
    cout << "Do you have a car loan? "<< endl;
    cin >> loan2;
    cout << "Do you have a mortgage? "<< endl;
    cin >> loan3;
    cout << "Do you have student/personal loan? "<< endl;
    cin >> loan4;

    loans = loan1 + loan2 + loan3 + loan4;

    cout << "\nDo you have new credit? (Yes/No): "<< endl;
    cin >> newCred;

    if (newCred == "yes" || newCred == "Yes")
    {
        cout << "Number of hard inquiries: "<< endl;
        cin >> inquiry;
        cout << "Number of new accounts: "<< endl;
        cin >> acc;
    }

    float points = calculateCreditScoreRecursive(latePayRate, utilization, cHistory, loans, newCred, inquiry, acc);
    c_score = points + 300;

    cout << "\nYour credit score is: " << c_score << endl;
    return c_score;
}

bool ID_AlreadyInUse(string id)
{
    for (int i = 0; i < totalUsers; i++)
    {
        string id;
        if (AccountUserInfo[i][0] == id)
            return true;
    }
    return false;
}

void checkAffordability(float budget, float systemCost)
{
    if (budget >= systemCost)
        cout << "You can afford the system directly.\n"<< endl;
    else
        cout << "Your budget is insufficient. Financial support needed.\n"<< endl;
}

void suggestSupportOption(float c_score)
{
   bool is_real= false;
    if (c_score && !is_real)
    {
        cout << "Support Option: "<< endl;
    if (c_score >= 450)
        cout << "You are eligible for a loan.\n"<< endl;
    else
        cout << "Suggest applying for government support.\n"<< endl;
    }
    else
    {
        cout << "Refer to credit score option first";
    }

}

void learnMoreAboutUs()
{
    cout << "\n..........ABOUT US..........\n"
         << "We are BSc Mathematical and Computer Science students at Sol Plaatje University.\n"
         << "This system helps members choose power sources (solar/hydro/wind) based on credit scores and budgets.\n"
         << "If ineligible, it recommends government-supported default power.\n"
         << "It also provides loan suggestions if required.\n";
}

void registerUser()
{
    string name, surname, province, race, id, password, user_email;

    cout << "\nCreate New Account"<< endl;
    cout << "Enter Name: "<< endl;
    cin >> name;
    cout << "Enter Surname: "<< endl;
    cin >> surname;
    cout << "Enter email address : " << endl;
    cin >> user_email;

    do
    {
        cout << "Enter Province: "<< endl;
        cin >> province;
    } while (!(province == "Gauteng" || province == "Limpopo" || province == "Mpumalanga" ||
               province == "KwazuluNatal" || province == "FreeState" || province == "EasternCape" ||
               province == "NorthernCape" || province == "WesternCape" || province == "NorthWest"));

    do
    {
        cout << "Enter Race (Arab, Asian, Black, Coloured, White): "<< endl;
        cin >> race;
    } while (!(race == "Black" || race == "Coloured" || race == "Asian" || race == "Arab" || race == "White"));

    do
    {
        cout << "Enter 13-digit ID number: "<< endl;
        cin >> id;
    } while (id.length() != 13 || ID_AlreadyInUse(id));

    cout << "Create a Password: "<< endl;
    cin >> password;

    AccountUserInfo[totalUsers][0] = id;
    AccountUserInfo[totalUsers][1] = password;
    AccountUserInfo[totalUsers][2] = name;
    AccountUserInfo[totalUsers][3] = surname;
    AccountUserInfo[totalUsers][4] = province;
    AccountUserInfo[totalUsers][5] = race;

    totalUsers++;
    cout << "Account created successfully!\n"<< endl;
    system ("cls");
}

void storeFeedback(string fullname, int ID_number, string feedback)
{
    if (member_no < index)
    {
        fullnames[member_no] = fullname;
        feedbacks[member_no] = feedback;
        ID_numbers[member_no] = ID_number;
        member_no++;
        cout << "Feedback submitted successfully."<< endl;
    }
    else
    {
        cout << "Feedback limit reached.\n"<< endl;
    }
}

void submitFeedback(int ID_number)
{
    for (int i = 0; i < member_no; i++)
    {
        if (ID_numbers[i] == ID_number)
        {
            cout << "Feedback submitted: " << feedbacks[i] << endl;
            return;
        }
    }
    cout << "No feedback found for this ID.\n"<< endl;
}

void searchFeedback(int ID_number)
{
    for (int i = 0; i < member_no; i++)
    {
        if (ID_numbers[i] == ID_number)
        {
            system ("cls");

            cout << "Member Name: " << fullnames[i] << endl;
            cout << "Feedback: " << feedbacks[i] << endl;
            return;
        }
    }
    cout << "No feedback found under ID " << ID_number << endl;
    return;
}

void feedbackOptions(int index)
{
    int feedbackOption;
    int id;
    string feedback = AccountUserInfo[index][1];
    string fullName = AccountUserInfo[index][2] + " " + AccountUserInfo[index][3];

    cout << "\n--- Feedback Options ---\n";
    cout << "1. Submit feedback\n2. View submitted feedback\n3. Back to Main Menu\nChoose: "<< endl;
    cin >> feedbackOption;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (feedbackOption)
    {
        system ("cls");
    case 1:
        cout << "Enter feedback: "<< endl;
        getline(cin, feedback);
        storeFeedback(fullName, id, feedback);
        break;
    case 2:
        submitFeedback(id);
        break;
    case 3:
        break;
    case 4:
        cout << "Returning to main menu."<< endl;
        break;
    default:
        cout << "Invalid feedback option."<< endl;
    }
}

void powerSourceOptions(float c_score)
{

    int power_choice;
    float kW;
    bool valid = false;

    cout << "\nWhich Power Source do you prefer : \n#Note, they're all eco-friendly :) \n1. Wind\n2. Solar\n3. Hydro" <<endl;

    cin >> power_choice;

    cout << "\nHow much electricity do you consume in a month (kW)?" << endl;

    cin >> kW;

    do
    {


     switch (power_choice)
     {
     case 1:
        {
           valid = true;
           AccountUserInfo[index][7]={"Wind"};
           cost = kW*0.7;
           cout << "\nYour bill is : R" << cost << endl;

        }
        break;
     case 2:
        {
            valid =true;
            AccountUserInfo[index][7]={"Solar"};
            cost = kW*0.9;
            cout << "\nYour bill is : R" << cost << endl;

        }
        break;
     case 3:
        {
            valid = true;
            AccountUserInfo[index][7]={"Hydro"};
            cost = kW*1.2;
            cout << "\nYour bill is : R" << cost << endl;

        }
        break;
     default:
        {
            cout << "\nInvalid input, please choose a provided option."<< endl;
        }


     }
    }while (power_choice && !valid);

    cout << "\nWill you be able to afford it? (yes/no)" << endl;
    string agree;
    cin >> agree;

    if (agree == "yes")
    {
        system ("cls");
        cout << "\nSystem confirmed, soon to be installed" << endl;
    }
    else if (agree == "no")
    {
        string loan_choice;
        cout << "\nWould like to apply for a loan? (yes/no)" << endl;
        do
        {

        cin >> loan_choice;
        valid =false;

        if (loan_choice== "yes")
        {
            if (c_score && !valid)
            {
                cout << "Your credit score is : " << c_score << endl;
            }

            cout << "\nTo apply for loan we need your CREDIT SCORE.\n" << endl;
            credScore();
            AccountUserInfo[index][7] == "Loan";
            if (c_score >= 580)
            {
                cout << "You qualify for a loan" << endl;
            }
            else
            {
                cout << "Credit score is too low, loan ineligible." << endl;
            }
            return;



        }

        else if (loan_choice== "no")
        {
           cout << "You can only get the system if you have enough budget or by applying for a loan" << endl;
        }
        else
        {
            cout << "Invalid input, please type yes or no." << endl;
        }
        }
        while (loan_choice!= "no" || loan_choice != "yes");

    }


}

void memberOptions(int index)
{
    int option;
    do
    {
        cout << "\n--- Account Menu ---\n";
        cout << "1. View My Info\n2. Credit Score\n3. Power Source(s)\n4. Feedback\n5. About Us\n6. Logout\nChoose option: "<< endl;
        cin >> option;

        if (option == 1)
        {
            cout << "\n--- Profile Details ---\n"<< endl;
            cout << "ID: " << AccountUserInfo[index][0] << endl;
            cout << "Name: " << AccountUserInfo[index][2] << " " << AccountUserInfo[index][3] << endl;
            cout << "Province: " << AccountUserInfo[index][4] << endl;
            cout << "Race: " << AccountUserInfo[index][5] << endl;
            cout << "Service: " << AccountUserInfo[index][7] << " and Cost is : R"<< cost << " per month" << endl;
        }
        else if (option == 2)
        {
            float c_score = credScore();
        }
        else if (option == 3)
        {
           powerSourceOptions(c_score);
        }
        else if (option == 4)
        {
            feedbackOptions(index);
        }
        else if (option == 5)
        {
            learnMoreAboutUs();
        }
        else if (option == 6)
        {
            cout << "Logging out...\n"<< endl;
            return;
        }
        else
        {
            cout << "Invalid choice.\n"<< endl;
        }

    } while (true);
}

bool loginUser()
{
    string inputID, inputPassword;

    if (totalUsers == 0)
    {
        cout << "No accounts found. Please sign up first.\n"<< endl;
        return false;
    }

    cout << "\n    Login   \nEnter ID: "<< endl;
    cin >> inputID;
    cout << "Enter Password: "<< endl;
    cin >> inputPassword;

    if (inputID == "DIZZ_NUTZ"&&inputPassword == "No_password")
    {
       cout << "\n    Admin access granted.\nSystem Overview\n1. User Info\n2. Number of users\n3. Search Feedback\n4. Exit\n ";
       bool valid=false;
       int admin_choice;
       cin >> admin_choice;
       do
       {
          if(admin_choice==1)
          {
            cout << "Enter the user ID\n";
            cin >> inputID;
            cout << "\n--- Profile Details ---\n"<< endl;
            cout << "ID: " << AccountUserInfo[index][0] << endl;
            cout << "Name: " << AccountUserInfo[index][2] << " " << AccountUserInfo[index][3] << endl;
            cout << "Province: " << AccountUserInfo[index][4] << endl;
            cout << "Race: " << AccountUserInfo[index][5] << endl;
            cout << "Service: " << AccountUserInfo[index][7] << " and Cost is : R"<< cost << " per month" << endl;
              break;
          }
          else if (admin_choice== 2)
          {
              //function to cout number of users
              cout << "The total amount of users is : "<< totalUsers << endl;
              valid =true;
          }
          else if (admin_choice==4)
          {
              system ("cls");
              cout << "Admin access exited.";
              return 0;
          }
          else if (admin_choice == 3)
          {
               int searchID;
               cout << "Enter ID to search feedback: "<< endl;
               cin >> searchID;
               searchFeedback(searchID);
               valid = true;
               break;

          }
          else
          {
              cout << "Invalid input, choose a valid option";
              valid=true;
          }
       }while(admin_choice && !valid);
    }

    for (int i = 0; i < totalUsers; i++)
    {
        if (AccountUserInfo[i][0] == inputID && AccountUserInfo[i][1] == inputPassword)
        {
            cout << "Login successful!\n";
            memberOptions(i);
            return true;
        }
    }
    cout << "Login failed. Check your details or create a new account\n";
    return false;
}

int main()
{
    bool valid = false;
    int choice;
    cout << "___ Welcome to Power Credit  System ___\n";

    do
    {
        cout << "\n1. Sign up\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser();
            break;

        case 2:
            loginUser();
            break;


        case 3:

            system ("cls");
            cout << "Goodbye!\n";
            valid =true;
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    while (choice && !valid);

    return 0;
}
