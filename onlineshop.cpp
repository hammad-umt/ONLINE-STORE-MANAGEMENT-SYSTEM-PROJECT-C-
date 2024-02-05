#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;
class Item
{
public:
    string name;
    double price;
    Item *next;

    Item(string itemname, double itemprice)
    {
        this->name = itemname;
        this->price = itemprice;
        this->next = NULL;
    }
    Item *finditem(const string &itemname)
    {
        Item *current = this;
        while (current != NULL)
        {
            if (current->name == itemname)
            {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
};
class Category
{
public:
    string name;
    Item *items;
    Category()
    {
        name = "Default Category";
        items = NULL;
    }
    Category(string categoryName)
    {
        this->name = categoryName;
        this->items = NULL;
    }

    void AddItem(string Itemname, double itemPrice)
    {
        Item *newitem = new Item(Itemname, itemPrice);
        newitem->next = items;
        items = newitem;
    }
    Item *finditem(const string &itemname)
    {
        return items->finditem(itemname);
    }

    ~Category()
    {
        while (items != NULL)
        {
            Item *temp = items;
            items = items->next;
            delete temp;
        }
    }
};

class CategoryNode
{
public:
    Category category;
    CategoryNode *left;
    CategoryNode *right;
    CategoryNode(string categoryName)
    {
        this->category = Category(categoryName);
        this->left = NULL;
        this->right = NULL;
    }
    Item *finditem(const string &Itemname)
    {
        return category.finditem(Itemname);
    }
};

class CategoryTree
{
public:
    CategoryNode *root;
    CategoryTree()
    {
        this->root = NULL;
    }

    CategoryNode *insertcategory(CategoryNode *node, const string &categoryName)
    {
        if (node == NULL)
        {
            return new CategoryNode(categoryName);
        }
        if (categoryName < node->category.name)
        {
            node->left = insertcategory(node->left, categoryName);
        }
        else if (categoryName > node->category.name)
        {
            node->right = insertcategory(node->right, categoryName);
        }

        return node;
    }
    CategoryNode *findcategory(CategoryNode *node, const string &categoryName) const
    {
        while (node != NULL)
        {
            if (categoryName == node->category.name)
            {
                return node;
            }
            else if (categoryName < node->category.name)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        return NULL;
    }
    void fillTree()
    {
        root = insertcategory(root, "Mobile");
        root = insertcategory(root, "Laptop");
        root = insertcategory(root, "Course");
    }

    void displaycategoriesinorder(CategoryNode *node) const
    {
        if (node != NULL)
        {
            displaycategoriesinorder(node->left);
            cout << "- " << node->category.name << endl;
            displaycategoriesinorder(node->right);
        }
    }
    Item *finditem(const string &Itemname) const
    {
        if (root != NULL)
        {
            return root->finditem(Itemname);
        }
        return NULL;
    }
};

class CartItem
{
public:
    Category *category;
    Item *item;

    CartItem(Category *category, Item *item) : category(category), item(item) {}
};
class Payment
{
public:
    string method;
    double amount;

    Payment()
    {
        method = "";
        amount = 0.0;
    }
    Payment(const string &paymentMethod, double paymentAmount)
    {
        this->method = paymentMethod;
        this->amount = paymentAmount;
    }
};
class CreditCard
{
public:
    string CardNo;
    string CardHolderName;
    string expiryDate;
    string cvv;
    CreditCard(const string &number, const string &name, const string &expiry, const string &cvv)
    {
        this->CardNo = number;
        this->CardHolderName = name;
        this->expiryDate = expiry;
        this->cvv = cvv;
    }
};
class DebitCard
{
public:
    string CardNo;
    string CardHolderName;
    string expiryDate;
    string cvv;
    DebitCard(const string &number, const string &name, const string &expiry, const string &cvv)
    {
        this->CardNo = number;
        this->CardHolderName = name;
        this->expiryDate = expiry;
        this->cvv = cvv;
    }
};
class Customer
{
public:
    string name;
    string ContactNo;
    string address;
    stack<CartItem> cart;
    Customer(const string &customername, const string &contact, const string &customeraddress)
    {
        name = customername;
        ContactNo = contact;
        address = customeraddress;
    }
    void AddToCart(Category *category, Item *item)
    {
        cart.push(CartItem(category, item));
    }
    void ViewCart() const
    {
        cout << "\n************ Shopping Cart ************\n";
        stack<CartItem> tempcart = cart;
        while (!tempcart.empty())
        {
            CartItem CartItem = tempcart.top();
            tempcart.pop();
            cout << "Category: " << CartItem.category->name << endl;
            cout << "Item: " << CartItem.item->name << " - Rs." << CartItem.item->price << "/-\n";
        }
    }
    void RemoveFromCart()
    {
        if (!cart.empty())
        {
            cout << "Enter the item number to remove from the cart (1-" << cart.size() << "): ";
            int itemNumber;
            cin >> itemNumber;
            if (itemNumber >= 1 && itemNumber <= cart.size())
            {
                stack<CartItem> tempStack;
                while (!cart.empty())
                {
                    if (itemNumber != 1)
                    {
                        tempStack.push(cart.top());
                    }
                    cart.pop();
                    itemNumber--;
                }
                while (!tempStack.empty())
                {
                    cart.push(tempStack.top());
                    tempStack.pop();
                }
                cout << "Item removed from the cart.\n";
            }
            else
            {
                cout << "Invalid item number. Please choose a valid number.\n";
            }
        }
        else
        {
            cout << "Your cart is empty. Add items to the cart before removing.\n";
        }
    }
    Payment MakeCreditCardPayment(double amount, const CreditCard &creditcard)
    {
        cout << "Credit Card Payment Details:\n";
        cout << "Card Number: **** **** **** " << creditcard.CardNo << endl;
        cout << "Cardholder Name: " << creditcard.CardHolderName << endl;
        cout << "Expiry Date: " << creditcard.expiryDate << endl;
        cout << "CVV: ***\n";
        return Payment("Credit Card", amount);
    }
    Payment MakeDebitCardPayment(double amount, const DebitCard &debitcard)
    {
        cout << "Debit Card Payment Details:\n";
        cout << "Card Number: **** **** **** " << debitcard.CardNo << endl;
        cout << "Cardholder Name: " << debitcard.CardHolderName << endl;
        cout << "Expiry Date: " << debitcard.expiryDate << endl;
        cout << "CVV: ***\n";
        return Payment("Debit Card", amount);
    }
    Payment MakeCashPayment(double amount)
    {
        return Payment("Cash", amount);
    }
    void PrintBill(const stack<Payment> &paymentstack) const
    {
        cout << "************ Invoice ************\n";
        cout << "Customer Name: " << name << endl;
        cout << "Contact Number: " << ContactNo << endl;
        cout << "Delivery Address: " << address << endl;
        stack<Payment> paymentcopy = paymentstack;
        while (!paymentcopy.empty())
        {
            Payment payment = paymentcopy.top();
            paymentcopy.pop();
            cout << "Payment Method: " << payment.method << "\nAmount Paid: Rs. " << payment.amount << "/-\n";
        }
    }

    double CalculateTotalAmount() const
    {
        stack<CartItem> tempcart = cart;
        double totalamount = 0.0;
        while (!tempcart.empty())
        {
            totalamount += tempcart.top().item->price;
            tempcart.pop();
        }
        return totalamount;
    }
};
class Shop
{
public:
    CategoryTree categorytree;
    queue<CartItem> checkoutqueue;
    stack<Payment> paymentstack;
    void fillShop()
    {
        categorytree.fillTree();
        CategoryNode *MobileCategoryNode = categorytree.findcategory(categorytree.root, "Mobile");
        if (MobileCategoryNode != NULL)
        {
            MobileCategoryNode->category.AddItem("Samsung Galaxy S21 Ultra", 124500);
            MobileCategoryNode->category.AddItem("Samsung Galaxy S22 Ultra", 170000);
            MobileCategoryNode->category.AddItem("Google Pixel 8 Pro ", 284999);
            MobileCategoryNode->category.AddItem("OnePlus 10T 8GB", 115999);
            MobileCategoryNode->category.AddItem("Apple Iphone 14 Pro Max", 333000);
            MobileCategoryNode->category.AddItem("Apple Iphone 15 Pro Max", 450999);
            MobileCategoryNode->category.AddItem("Oppo Find X", 60000);
            MobileCategoryNode->category.AddItem("Vivo V12", 44000);
        }
        CategoryNode *LaptopCategoryNode = categorytree.findcategory(categorytree.root, "Laptop");
        if (LaptopCategoryNode != NULL)
        {
            LaptopCategoryNode->category.AddItem("HP ProBook i7", 124000);
            LaptopCategoryNode->category.AddItem("Lenovo ThinkPad", 90000);
            LaptopCategoryNode->category.AddItem("DELL NoteBook", 99000);
            LaptopCategoryNode->category.AddItem("Macbook M1", 250000);
            LaptopCategoryNode->category.AddItem("Macbook M2", 300000);
            LaptopCategoryNode->category.AddItem("Macbook M3", 350000);
            LaptopCategoryNode->category.AddItem("Asus Gaming Laptop", 400000);
        }

        CategoryNode *CourseCategoryNode = categorytree.findcategory(categorytree.root, "Course");
        if (CourseCategoryNode != NULL)
        {
            CourseCategoryNode->category.AddItem("C", 1000);
            CourseCategoryNode->category.AddItem("C++", 3000);
            CourseCategoryNode->category.AddItem("C Sharp/ C#", 3500);
            CourseCategoryNode->category.AddItem("Java", 4000);
            CourseCategoryNode->category.AddItem("Python", 3500);
            CourseCategoryNode->category.AddItem("HTML", 4200);
            CourseCategoryNode->category.AddItem("CSS", 3700);
        }
    }

    void ShowMenu() const
    {
        cout << "          Welcome to Our Shop            \n";
        cout << "                   Menu\n";
        categorytree.displaycategoriesinorder(categorytree.root);
        cout << "- View Cart\n";
        cout << "- Remove from Cart\n"; // New option
        cout << "- Checkout\n";
        cout << "- Show Menu\n"; // New option
    }

    void ShowItems(Category *category) const
    {
        cout << "\n- - - - - - - - - - - -\n Item Cost\n";
        Item *CurrentItem = category->items;
        int itemno = 1;
        while (CurrentItem != NULL)
        {
            cout << itemno << " - " << CurrentItem->name << " Rs." << CurrentItem->price << "/-\n";
            CurrentItem = CurrentItem->next;
            itemno++;
        }
    }
    void ViewCart(const Customer &customer) const
    {
        cout << "\n             Shopping Cart            \n";
        stack<CartItem> tempcart = customer.cart;
        while (!tempcart.empty())
        {
            CartItem CartItem = tempcart.top();
            tempcart.pop();
            cout << "Category: " << CartItem.category->name << endl;
            cout << "Item: " << CartItem.item->name << " - Rs." << CartItem.item->price << "/-\n";
        }
    }
    void EnqueueCheckout(Customer &customer)
    {
        while (!customer.cart.empty())
        {
            checkoutqueue.push(customer.cart.top());
            customer.cart.pop();
        }
    }
    void ProceedToCheckout(Customer &customer)
    {
        cout << "\n      Proceeding to Checkout      \n";
        double overallTotal = 0.0;
        queue<CartItem> tempqueue = checkoutqueue;
        while (!tempqueue.empty())
        {
            overallTotal += tempqueue.front().item->price;
            tempqueue.pop();
        }
        cout << "Overall Total: Rs." << overallTotal << endl;
        int paymentOpt;
        cout << "Select payment option (1: Credit Card, 2: Debit Card, 3: Cash): ";
        cin >> paymentOpt;
        Payment payment;
        if (paymentOpt == 1)
        {
            CreditCard creditcard = GetCreditCardDetails();
            payment = customer.MakeCreditCardPayment(overallTotal, creditcard);
        }
        else if (paymentOpt == 2)
        {
            DebitCard debitcard = GetDebitCardDetails();
            payment = customer.MakeDebitCardPayment(overallTotal, debitcard);
        }
        else if (paymentOpt == 3)
        {
            payment = customer.MakeCashPayment(overallTotal);
        }
        else
        {
            cout << "Invalid payment option\n";
            return;
        }
        paymentstack.push(payment);
        cout << "\n      Payment Details      \n";
        while (!paymentstack.empty())
        {
            Payment CurrentPayment = paymentstack.top();
            paymentstack.pop();
            cout << "Method: " << CurrentPayment.method << endl;
            cout << "Amount: Rs." << CurrentPayment.amount << "/-\n";
        }
        cout << "\nThank you for your purchase, " << customer.name << "! \n Have a great day!\n";
    }
    CreditCard GetCreditCardDetails() const
    {
        string CardNo, CardHolderName, expiryDate, cvv;
        cout << "\nEnter credit card number: ";
        cin >> CardNo;
        cout << "Enter cardholder name: ";
        cin.ignore();
        getline(cin, CardHolderName);
        cout << "Enter expiry date (MM/YYYY): ";
        cin >> expiryDate;
        cout << "Enter CVV: ";
        cin >> cvv;
        return CreditCard(CardNo, CardHolderName, expiryDate, cvv);
    }
    DebitCard GetDebitCardDetails() const
    {
        string CardNo, CardHolderName, expiryDate, cvv;
        cout << "\nEnter debit card number: ";
        cin >> CardNo;
        cout << "Enter cardholder name: ";
        cin.ignore();
        getline(cin, CardHolderName);
        cout << "Enter expiry date (MM/YYYY): ";
        cin >> expiryDate;
        cout << "Enter CVV: ";
        cin >> cvv;
        return DebitCard(CardNo, CardHolderName, expiryDate, cvv);
    }
};
int main()
{
    cout << "                Welcome to our Online Shop .\n";
    cout << "We are delighted to have you here.How can we help you?" << endl;
    cout << "Enter your name: ";
    string customername;
    getline(cin, customername);
    cout << "Enter your contact number: ";
    string ContactNo;
    getline(cin, ContactNo);
    cout << "Enter your address: ";
    string customeraddress;
    getline(cin, customeraddress);
    Customer customer(customername, ContactNo, customeraddress);
    Shop shop;
    shop.fillShop();
    int option;
    system("cls");
    while (true)
    {

        shop.ShowMenu();
        cout << "Please select an option to proceed further. If you choose to checkout, shopping will end,\n and a bill will be generated for the items bought so far...\n";
        cout << "Enter your choice \n 1 to Select Course \n 2 to Select Laptop \n 3 to Select Mobile \n 4 to view cart \n 5 to Remove from Cart\n 6 to checkout \n 0 to exit): ";
        cin >> option; 
        CategoryNode *categoryNode = NULL;
        switch (option)
        {
        case 0:
            cout << "Exiting the shop. Thank you for visiting!\n";
            return 0;
        case 1:
        case 2:
        case 3:
        {
            string categoryName;
            switch (option)
            {
            case 1:
                categoryName = "Course";
                break;
            case 2:
                categoryName = "Laptop";
                break;
            case 3:
                categoryName = "Mobile";
                break;
            }
            categoryNode = shop.categorytree.findcategory(shop.categorytree.root, categoryName);
            if (categoryNode != NULL)
            {
                shop.ShowItems(&(categoryNode->category));
                cout << "Enter the number of the item you want to purchase (0 to go back): ";
                int itemNumber;
                cin >> itemNumber;
                switch (itemNumber)
                {
                case 0:
                    cout << "Going back to category selection.\n";
                    break;
                case 1:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items);
                    break;
                case 2:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next);
                    break;
                case 3:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next->next);
                    break;
                case 4:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next->next->next);
                    break;
                case 5:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next->next->next->next);
                    break;
                case 6:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next->next->next->next->next);
                    break;
                case 7:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next->next->next->next->next->next);
                    break;
                case 8:
                    customer.AddToCart(&(categoryNode->category), categoryNode->category.items->next->next->next->next->next->next->next);
                    break;
                default:
                    cout << "Invalid item number. Please choose a valid number.\n";
                    break;
                }
            }
            else
            {
                cout << "Invalid category selection. Please try again.\n";
            }
            break;
        }
            system("cls");
        case 4:
            shop.ViewCart(customer);
            break;
         case 5:
            customer.RemoveFromCart();
            break;
        case 6:

            if (!customer.cart.empty())
            {
                shop.EnqueueCheckout(customer);
                shop.ProceedToCheckout(customer);
                customer.cart = stack<CartItem>();
                customer.PrintBill(shop.paymentstack);
            }
            else
            {
                cout << "Your cart is empty. Add items to the cart before checking out.\n";
            }
            break;
       
        }
    }
    while (option != 0)
        ;
    system("cls");
    return 0;
}
