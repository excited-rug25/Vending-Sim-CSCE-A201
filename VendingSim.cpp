#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// A. function prototypes for admin reports and customer purchasing
void adminMenu(float prices[5][2], int itemsSold[5][2], int totalSales, int stock[5][2],
    string products[5][3], int optionCols, int categoryRows, int productCols,
    int longestCategory, int longestOption);

void salesReport(float prices[5][2], int itemsSold[5][2], string products[5][3],
    int longestCategory, int longestOption);

void inventoryReport(int stock[5][2], string products[5][3],
    int longestCategory, int longestOption);

void machineReport(float prices[5][2], int itemsSold[5][2], int totalSales, int stock[5][2],
    string products[5][3], int optionCols, int categoryRows, int productCols,
    int longestCategory, int longestOption);

int customerMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2],
    string products[5][3], int longestOption, int optionCols, int categoryRows);

bool chipsMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total);

bool candyMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total);

bool drinksMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total);

bool gumMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total);

bool cookiesMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total);
// A end


// B. main program setup: constants, arrays, and file stream
int main()
{
    const int optionCols = 2, categoryRows = 5, productCols = 3;

    ifstream inputFile;
    string products[categoryRows][productCols];
    float prices[categoryRows][optionCols];
    int stock[categoryRows][optionCols];
    // B end


    // C. load vending machine prices and stock amounts from file
    inputFile.open("VendingStockPrices.txt");

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            inputFile >> prices[i][j];
        }
    }

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            inputFile >> stock[i][j];
        }
    }

    inputFile.close();
    // C end


    // D. load category names and product option names from file
    inputFile.open("VendingProducts.txt");

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < productCols; j++)
        {
            getline(inputFile, products[i][j]);
        }
    }

    inputFile.close();
    // D end


    // E. calculate spacing widths for formatted report output
    int longestCategory = 0, longestOption = 0;

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < productCols; j++)
        {
            if (j == 0)
            {
                if (products[i][j].length() > longestCategory)
                {
                    longestCategory = products[i][j].length();
                }
            }
            else
            {
                if (products[i][j].length() > longestOption)
                {
                    longestOption = products[i][j].length();
                }
            }
        }
    }

    longestCategory++;
    longestOption++;
    // E end


    // F. initialize menu control variables and sales tracking arrays
    int input, totalSales = 0, itemsSold[categoryRows][optionCols];
    bool running = true;

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            itemsSold[i][j] = 0;
        }
    }
    // F end


    // G. welcome screen
    cout << "==========================================" << endl;
    cout << "      Welcome to Vending Machine Sim      " << endl;
    cout << "==========================================" << endl << endl;
    // G end


    // H. main control loop
    while (running)
    {
        cout << "1. Admin Panel" << endl;
        cout << "2. Customer Menu" << endl;
        cout << "3. Shut Down" << endl;
        cin >> input;

        while (input < 1 || input > 3)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Your choice must be between 1 and 3" << endl;
            cin >> input;
        }

        switch (input)
        {
        case 1:
            adminMenu(prices, itemsSold, totalSales, stock, products,
                optionCols, categoryRows, productCols, longestCategory, longestOption);
            break;
        case 2:
            totalSales += customerMenu(prices, itemsSold, stock, products,
                longestOption, optionCols, categoryRows);
            break;
        case 3:
            running = false;
            break;
        default:
            break;
        }

        cout << endl;
    }

    return 0;
}
// H end


// I. admin menu controller
void adminMenu(float prices[5][2], int itemsSold[5][2], int totalSales, int stock[5][2],
    string products[5][3], int optionCols, int categoryRows, int productCols,
    int longestCategory, int longestOption)
{
    int input;
    bool running = true;

    while (running)
    {
        cout << endl;
        cout << "Vending Machine Simulator Admin Panel" << endl;
        cout << "1. Sales Summary" << endl;
        cout << "2. Inventory Summary" << endl;
        cout << "3. Export Machine Report" << endl;
        cout << "4. Exit" << endl;
        cin >> input;

        while (input < 1 || input > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Your choice must be between 1 and 4" << endl;
            cin >> input;
        }

        switch (input)
        {
        case 1:
            salesReport(prices, itemsSold, products, longestCategory, longestOption);
            break;
        case 2:
            inventoryReport(stock, products, longestCategory, longestOption);
            break;
        case 3:
            machineReport(prices, itemsSold, totalSales, stock, products,
                optionCols, categoryRows, productCols, longestCategory, longestOption);
            break;
        case 4:
            running = false;
            break;
        default:
            break;
        }
    }
}
// I end


// J. admin output: sales summary
void salesReport(float prices[5][2], int itemsSold[5][2], string products[5][3],
    int longestCategory, int longestOption)
{
    float totalProfit = 0, lineProfit;

    cout << endl << "Sales Summary" << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            lineProfit = prices[i][j] * itemsSold[i][j];
            totalProfit += lineProfit;

            cout << left << setw(longestCategory) << products[i][0] << " "
                << setw(longestOption) << products[i][j + 1]
                << "\tSold: " << setw(3) << itemsSold[i][j]
                << "\t$" << fixed << setprecision(2) << lineProfit << endl;
        }
        cout << endl;
    }

    cout << "Total Profit: $" << fixed << setprecision(2) << totalProfit << endl;
    cout << endl << "Press Enter to continue.";
    cin.ignore();
    cin.get();
    cin.clear();
}
// J end


// K. admin output: inventory summary
void inventoryReport(int stock[5][2], string products[5][3],
    int longestCategory, int longestOption)
{
    cout << endl << "Inventory Summary" << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << left << setw(longestCategory) << products[i][0] << " "
                << setw(longestOption) << products[i][j + 1]
                << "\t" << stock[i][j] << endl;
        }
        cout << endl;
    }

    cout << "Press Enter to continue.";
    cin.ignore();
    cin.get();
    cin.clear();
}
// K end


// L. admin output: export machine report to file and display it
void machineReport(float prices[5][2], int itemsSold[5][2], int totalSales, int stock[5][2],
    string products[5][3], int optionCols, int categoryRows, int productCols,
    int longestCategory, int longestOption)
{
    ofstream outputFile("MachineReport.txt");

    outputFile << "\t\tVending Machine Simulator Report" << endl << endl;
    outputFile << "Total number of items sold: " << totalSales << endl << endl;
    outputFile << "Sales by item:" << endl << endl;

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            outputFile << left << setw(longestCategory) << products[i][0] << " "
                << setw(longestOption) << products[i][j + 1]
                << "\tSold: " << setw(3) << itemsSold[i][j]
                << "\t$" << fixed << setprecision(2) << prices[i][j] * itemsSold[i][j] << endl;
        }
        outputFile << endl;
    }

    outputFile << endl << "Remaining stock:" << endl << endl;

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            outputFile << left << setw(longestCategory) << products[i][0] << " "
                << setw(longestOption) << products[i][j + 1]
                << "\t" << stock[i][j] << endl;
        }
        outputFile << endl;
    }

    outputFile.close();

    cout << endl << "\t\tVending Machine Simulator Report" << endl << endl;
    cout << "Total number of items sold: " << totalSales << endl << endl;
    cout << "Sales by item:" << endl << endl;

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            cout << left << setw(longestCategory) << products[i][0] << " "
                << setw(longestOption) << products[i][j + 1]
                << "\tSold: " << setw(3) << itemsSold[i][j]
                << "\t$" << fixed << setprecision(2) << prices[i][j] * itemsSold[i][j] << endl;
        }
        cout << endl;
    }

    cout << endl << "Remaining stock:" << endl << endl;

    for (int i = 0; i < categoryRows; i++)
    {
        for (int j = 0; j < optionCols; j++)
        {
            cout << left << setw(longestCategory) << products[i][0] << " "
                << setw(longestOption) << products[i][j + 1]
                << "\t" << stock[i][j] << endl;
        }
        cout << endl;
    }

    cout << "Press Enter to continue.";
    cin.ignore();
    cin.get();
    cin.clear();
}
// L end


// M. customer menu controller
int customerMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2],
    string products[5][3], int longestOption, int optionCols, int categoryRows)
{
    int choice, sales = 0;
    float total = 0;
    bool shopping = true;
    bool purchased = false;

    while (shopping)
    {
        cout << endl;
        cout << "Customer Menu" << endl;
        cout << "Choose a category below, or press 0 to exit." << endl << endl;

        for (int i = 0; i < categoryRows; i++)
        {
            cout << i + 1 << ". " << products[i][0] << endl;
        }

        cin >> choice;

        while (choice < 0 || choice > categoryRows)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Your choice must be between 0 and " << categoryRows << endl;
            cin >> choice;
        }

        choice--;

        switch (choice)
        {
        case 0:
            purchased = chipsMenu(prices, itemsSold, stock, choice, products, longestOption, &total);
            if (purchased) sales++;
            break;
        case 1:
            purchased = candyMenu(prices, itemsSold, stock, choice, products, longestOption, &total);
            if (purchased) sales++;
            break;
        case 2:
            purchased = drinksMenu(prices, itemsSold, stock, choice, products, longestOption, &total);
            if (purchased) sales++;
            break;
        case 3:
            purchased = gumMenu(prices, itemsSold, stock, choice, products, longestOption, &total);
            if (purchased) sales++;
            break;
        case 4:
            purchased = cookiesMenu(prices, itemsSold, stock, choice, products, longestOption, &total);
            if (purchased) sales++;
            break;
        case -1:
            shopping = false;
            break;
        default:
            break;
        }
    }

    cout << endl << "Session complete." << endl;
    cout << "Items purchased: " << sales << endl;
    cout << "Amount due: $" << fixed << setprecision(2) << total << endl << endl;

    return sales;
}
// M end


// N. chips option menu
bool chipsMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total)
{
    int input;

    cout << endl;
    cout << "1. " << left << setw(longestOption) << products[choice][1]
        << " $" << fixed << setprecision(2) << prices[choice][0] << endl;
    cout << "2. " << left << setw(longestOption) << products[choice][2]
        << " $" << fixed << setprecision(2) << prices[choice][1] << endl;
    cout << "Choose an option" << endl;

    cin >> input;

    while (input < 1 || input > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Your choice must be 1 or 2" << endl;
        cin >> input;
    }

    input--;

    if (stock[choice][input] > 0)
    {
        itemsSold[choice][input]++;
        stock[choice][input]--;
        *total += prices[choice][input];
        cout << products[choice][input + 1] << " dispensed." << endl;
        return true;
    }
    else
    {
        cout << "Sorry, that selection is out of stock." << endl;
        return false;
    }
}


// O. candy option menu
bool candyMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total)
{
    int input;

    cout << endl;
    cout << "1. " << left << setw(longestOption) << products[choice][1]
        << " $" << fixed << setprecision(2) << prices[choice][0] << endl;
    cout << "2. " << left << setw(longestOption) << products[choice][2]
        << " $" << fixed << setprecision(2) << prices[choice][1] << endl;
    cout << "Choose an option" << endl;

    cin >> input;

    while (input < 1 || input > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Your choice must be 1 or 2" << endl;
        cin >> input;
    }

    input--;

    if (stock[choice][input] > 0)
    {
        itemsSold[choice][input]++;
        stock[choice][input]--;
        *total += prices[choice][input];
        cout << products[choice][input + 1] << " dispensed." << endl;
        return true;
    }
    else
    {
        cout << "Sorry, that selection is out of stock." << endl;
        return false;
    }
}


// P. drinks option menu
bool drinksMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total)
{
    int input;

    cout << endl;
    cout << "1. " << left << setw(longestOption) << products[choice][1]
        << " $" << fixed << setprecision(2) << prices[choice][0] << endl;
    cout << "2. " << left << setw(longestOption) << products[choice][2]
        << " $" << fixed << setprecision(2) << prices[choice][1] << endl;
    cout << "Choose an option" << endl;

    cin >> input;

    while (input < 1 || input > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Your choice must be 1 or 2" << endl;
        cin >> input;
    }

    input--;

    if (stock[choice][input] > 0)
    {
        itemsSold[choice][input]++;
        stock[choice][input]--;
        *total += prices[choice][input];
        cout << products[choice][input + 1] << " dispensed." << endl;
        return true;
    }
    else
    {
        cout << "Sorry, that selection is out of stock." << endl;
        return false;
    }
}


// Q. gum option menu
bool gumMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total)
{
    int input;

    cout << endl;
    cout << "1. " << left << setw(longestOption) << products[choice][1]
        << " $" << fixed << setprecision(2) << prices[choice][0] << endl;
    cout << "2. " << left << setw(longestOption) << products[choice][2]
        << " $" << fixed << setprecision(2) << prices[choice][1] << endl;
    cout << "Choose an option" << endl;

    cin >> input;

    while (input < 1 || input > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Your choice must be 1 or 2" << endl;
        cin >> input;
    }

    input--;

    if (stock[choice][input] > 0)
    {
        itemsSold[choice][input]++;
        stock[choice][input]--;
        *total += prices[choice][input];
        cout << products[choice][input + 1] << " dispensed." << endl;
        return true;
    }
    else
    {
        cout << "Sorry, that selection is out of stock." << endl;
        return false;
    }
}


// R. cookies option menu
bool cookiesMenu(float prices[5][2], int itemsSold[5][2], int stock[5][2], int choice,
    string products[5][3], int longestOption, float* total)
{
    int input;

    cout << endl;
    cout << "1. " << left << setw(longestOption) << products[choice][1]
        << " $" << fixed << setprecision(2) << prices[choice][0] << endl;
    cout << "2. " << left << setw(longestOption) << products[choice][2]
        << " $" << fixed << setprecision(2) << prices[choice][1] << endl;
    cout << "Choose an option" << endl;

    cin >> input;

    while (input < 1 || input > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Your choice must be 1 or 2" << endl;
        cin >> input;
    }

    input--;

    if (stock[choice][input] > 0)
    {
        itemsSold[choice][input]++;
        stock[choice][input]--;
        *total += prices[choice][input];
        cout << products[choice][input + 1] << " dispensed." << endl;
        return true;
    }
    else
    {
        cout << "Sorry, that selection is out of stock." << endl;
        return false;
    }
}
// R end