#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class TicketWindow
{
    public:
    struct Customer
    {
        string name;
        string ticketType;
        double ticketPrice;
        string paymentMethod;
        vector<string> refreshments;
        double refreshmentsPrice;
    };

    queue<Customer> customerQueue;
    queue<Customer> tempQueue;
    int silverTickets = 10;
    int goldTickets = 10;
    int platinumTickets = 5;
    int totalTickets = 25;

    void enqueueCustomer()
    {
        if(totalTickets == 0)
        {
            cout << "Sorry, All Sold Out.\n";
            return;
        }
        Customer customer;
        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin,customer.name);
        cout << "Available tickets:" << endl;
        cout << "Silver Tickets: " << silverTickets << endl;
        cout << "Gold Tickets: " << goldTickets << endl;
        cout << "Platinum Tickets: " << platinumTickets << endl;
        cout << "How many tickets do you want to buy? ";
        int numTickets;
        cin >> numTickets;
        if (numTickets <= 0)
        {
            cout << "Invalid number of tickets. Please enter a positive number." << endl;
            return;
        }
        else if(numTickets > totalTickets)
        {
            cout << "Not enough tickets are available.\n";
            return;
        }
        
        int ticketType;
        cout << "Are all tickets of the same type? (1 for yes): ";
        int sameTypeChoice;
        cin >> sameTypeChoice;
        int ST = 0, GT = 0, PT = 0;

        if (sameTypeChoice == 1)
        {
            cout << "Select the ticket type:" << endl;
            cout << "1. Silver Ticket (Rs. 10.00)" << endl;
            cout << "2. Gold Ticket (Rs. 15.00)" << endl;
            cout << "3. Platinum Ticket (Rs. 20.00)" << endl;
            cout << "Enter your choice: ";
            cin >> ticketType;
            if (ticketType == 1)
            {
                if (numTickets > silverTickets)
                {
                    cout << "Not enough Silver Tickets available. Please order according to availibility." << endl;
                    return;
                }
                customer.ticketType = "Silver Ticket";
                customer.ticketPrice = 10.00 * numTickets;
                silverTickets -= numTickets;
                ST = numTickets;
            }
            else if (ticketType == 2)
            {
                if (numTickets > goldTickets)
                {
                    cout << "Not enough Gold Tickets available. Please order according to availibility." << endl;
                    return;
                }
                customer.ticketType = "Gold Ticket";
                customer.ticketPrice = 15.00 * numTickets;
                goldTickets -= numTickets;
                GT = numTickets;
            }
            else
            {
                if (numTickets > platinumTickets)
                {
                    cout << "Not enough Platinum Tickets available. Please order according to availibility." << endl;
                    return;
                }
                customer.ticketType = "Platinum Ticket";
                customer.ticketPrice = 20.00 * numTickets;
                platinumTickets -= numTickets;
                PT = numTickets;
            }
        }
        else
        {
            int a = 1;
            while (a)
            {
                cout << "Enter the total number of Silver Tickets (Rs. 10): ";
                cin >> ST;
                silverTickets -= ST;
                cout << "Enter the total number of Gold Tickets (Rs. 15): ";
                cin >> GT;
                goldTickets -= GT;
                cout << "Enter the total number of Platinum Tickets (Rs. 20): ";
                cin >> PT;
                platinumTickets -= PT;
                if (ST + GT + PT > numTickets)
                    cout << "Please Enter a valid number of tickets of each type as you have specified earlier.\n";
                else
                    a = 0;
            }

            customer.ticketType = "Mixed Tickets";
            customer.ticketPrice = (15.00 * goldTickets) + (20.00 * platinumTickets) + (10.00 * silverTickets);
        }
        
        totalTickets -= numTickets;
        cout << "Select the payment method:" << endl;
        cout << "1. UPI" << endl;
        cout << "2. Cash" << endl;
        cout << "3. Card" << endl;
        cout << "Enter your choice: ";
        int paymentChoice;
        cin >> paymentChoice;
        if (paymentChoice == 1)
        {
            customer.paymentMethod = "UPI";
            cout << "UPI ID: 9461061450@paytm" << endl; // Display UPI ID
        }
        else if (paymentChoice == 2)
            customer.paymentMethod = "Cash";
        else
            customer.paymentMethod = "Card";
        
        if (isWeekend()) 
        {
            double tax = 0.10; // 10% tax on weekends
            customer.ticketPrice += customer.ticketPrice * tax;
            cout << "Weekend Tax Applied. New ticket price: Rs. " << customer.ticketPrice << endl;
        }
        
        else if (isSpecialDiscountDay())
        {
            double discount = 0.15; // 15% discount on special discount days
            customer.ticketPrice -= customer.ticketPrice * discount;
            cout << "Special Discount Applied. New ticket price: Rs. " << customer.ticketPrice << endl;
        }

        // Ask if the customer wants refreshments
        cout << "Do you want to order refreshments? (1 for yes): ";
        int refreshmentsChoice;
        cin >> refreshmentsChoice;

        if (refreshmentsChoice == 1)
            offerRefreshments(customer);
        else
            customer.refreshmentsPrice = 0.0;

        cout << "Total payment amount (Rs. " << customer.ticketPrice + customer.refreshmentsPrice << "): Rs. ";
        double payment;
        cin >> payment;
        while (payment < customer.ticketPrice + customer.refreshmentsPrice)
        {
            cout << "Payment is unacceptable, kindly pay the total amount of Rs. " << customer.ticketPrice + customer.refreshmentsPrice << ": Rs. ";
            cin >> payment;
        }

        customerQueue.push(customer);
        tempQueue.push(customer);
        cout << customer.name << " has been added to the queue with the following tickets:" << endl;
        cout << "Silver Tickets (Rs. 10): " << ST << endl;
        cout << "Gold Tickets (Rs. 15): " << GT << endl;
        cout << "Platinum Tickets (Rs. 20): " << PT << endl;
        cout << "Total Price for Tickets: Rs. " << customer.ticketPrice << endl;
        if (!customer.refreshments.empty())
        {
            cout << "Refreshments Ordered:" << endl;
            for (const string& refreshment : customer.refreshments)
                cout << refreshment << endl;

            cout << "Total Price for Refreshments: Rs. " << customer.refreshmentsPrice << endl;
        }
        cout << "Paid using " << customer.paymentMethod << "." << endl;
    }

    void dequeueCustomer()
    {
        if (!customerQueue.empty())
        {
            Customer customer = customerQueue.front();
            cout << customer.name << " has purchased the following tickets:" << endl;
            cout << customer.ticketType << " tickets (Rs. " << customer.ticketPrice << ")";
            if (!customer.refreshments.empty())
            {
                cout << " and ordered refreshments:" << endl;
                for (const string& refreshment : customer.refreshments)
                    cout << refreshment << endl;
                cout << "Total Price for Refreshments: Rs. " << customer.refreshmentsPrice << endl;
            }
            cout << " and paid using " << customer.paymentMethod << ". Left the queue." << endl;
            saveQueueToFile();
            customerQueue.pop();
        }
        else
            cout << "Queue is empty. No customers to serve." << endl;
    }

    void displayQueue()
    {
        if (!tempQueue.empty())
        {
            cout << "Customers in the queue:" << endl;
            while (!tempQueue.empty())
            {
                Customer customer = tempQueue.front();
                cout << customer.name << " - " << customer.ticketType << " tickets (Rs. " << customer.ticketPrice << ")";
                if (!customer.refreshments.empty())
                {
                    cout << " and ordered refreshments:" << endl;
                    for (const string& refreshment : customer.refreshments)
                        cout << refreshment << endl;

                    cout << "Total Price for Refreshments: Rs. " << customer.refreshmentsPrice << endl;
                }
                cout << " - Paid with " << customer.paymentMethod << endl;
                tempQueue.pop();
            }
        }
        else
            cout << "Queue is empty. No customers in the queue." << endl;
    }
    
    void saveQueueToFile()
    {
        ofstream outFile("customerQueue.txt");
        queue<Customer> TempQueue = tempQueue;
        while (!TempQueue.empty())
        {
            Customer customer = TempQueue.front();
            outFile <<"Name: "<< customer.name << "\n"
                    <<"Ticket type: "<<customer.ticketType << "\n"
                    <<"Ticket price: Rs."<< customer.ticketPrice << "\n"
                    <<"Payment method: "<< customer.paymentMethod << "\n";
            for (const string& refreshment : customer.refreshments)
                outFile << refreshment << "\n";
            outFile <<"refreshmentsPrice: Rs."<< customer.refreshmentsPrice << "\n\n";
            TempQueue.pop();
        }
        outFile.close();
    }

    void loadQueueFromFile()
    {
        ifstream inFile("customerQueue.txt");
        string line;
        while (getline(inFile, line))
        {
            Customer customer;
            customer.name = line;
            getline(inFile, customer.ticketType);
            inFile >> customer.ticketPrice;
            inFile.ignore(); // ignore newline
            getline(inFile, customer.paymentMethod);
            string refreshment;
            while (getline(inFile, refreshment) && refreshment != "")
                customer.refreshments.push_back(refreshment);
            inFile >> customer.refreshmentsPrice;
            inFile.ignore(); // ignore newline
            tempQueue.push(customer);
        }
        inFile.close();
    }

    private:
    bool isWeekend()
    {
        cout << "Is today a weekend? (1 for yes): ";
        int isWeekend;
        cin >> isWeekend;
        return isWeekend == 1;
    }
    
    bool isSpecialDiscountDay()
    {
        cout << "Is today Wednesday (special discount day)? (1 for yes): ";
        int isDiscountDay;
        cin >> isDiscountDay;
        return isDiscountDay == 1;
    }

    void offerRefreshments(Customer& customer)
    {
        vector<string> refreshmentMenu = {"Popcorn (Rs. 5.00)", "Soda (Rs. 3.00)", "Candy (Rs. 2.00)"};
        cout << "Refreshments Menu:" << endl;
        for (int i = 0; i < refreshmentMenu.size(); i++)
            cout << i + 1 << ". " << refreshmentMenu[i] << endl;

        vector<int> quantities(refreshmentMenu.size(), 0); // Initialize quantities with zeros

        int refreshmentChoice;
        while (true)
        {
            cout << "Enter the refreshments you want to order (0 to finish): ";
            cin >> refreshmentChoice;
            if (refreshmentChoice == 0)
                break;
            else if (refreshmentChoice > 0 && refreshmentChoice <= refreshmentMenu.size())
            {
                int quantity;
                cout << "Enter the quantity for " << refreshmentMenu[refreshmentChoice - 1] << ": ";
                cin >> quantity;
                if (quantity < 0)
                    cout << "Invalid quantity. Please enter a positive number." << endl;
                else
                    quantities[refreshmentChoice - 1] += quantity;
            }
            else
                cout << "Invalid choice. Please enter a valid number from the menu." << endl;
        }

        vector<string> chosenRefreshments;
        double refreshmentsPrice = 0.0;

        for (int i = 0; i < refreshmentMenu.size(); i++)
        {
            if (quantities[i] > 0)
            {
                chosenRefreshments.push_back(refreshmentMenu[i] + " x" + to_string(quantities[i]));
                refreshmentsPrice += getPriceFromRefreshmentString(refreshmentMenu[i]) * quantities[i];
            }
        }

        customer.refreshments = chosenRefreshments;
        customer.refreshmentsPrice = refreshmentsPrice;
    }

    double getPriceFromRefreshmentString(const string& refreshmentString)
    {
        if (refreshmentString.find("Popcorn") != string::npos)
            return 5.00;
        else if (refreshmentString.find("Soda") != string::npos)
            return 3.00;
        else if (refreshmentString.find("Candy") != string::npos)
            return 2.00;
        return 0.0; // Unknown refreshment
    }
};

int main()
{
    TicketWindow ticketWindow;
    int choice;

    do {
        cout << "\n\t\t\t\tAuditorium Ticket Window Menu:\n" << endl;
        cout << "1. Enqueue Customer" << endl;
        cout << "2. Dequeue Customer" << endl;
        cout << "3. Display Data" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ticketWindow.enqueueCustomer();
            break;
        case 2:
            ticketWindow.dequeueCustomer();
            break;
        case 3:
            ticketWindow.displayQueue();
            break;
        case 4:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            return 0;
        }
        
    } while (choice != 4);

    ticketWindow.loadQueueFromFile();
    return 0;
}
