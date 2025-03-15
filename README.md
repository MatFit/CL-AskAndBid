# Bid2Buy
What is it - a homework assignment where we will create simple UI in the terminal to mimic the behavior
of buy and selling on a platform. There will be users who can buy and sell with their data being saved and loaded up
no matter how many times.

Squad : Tibbles, Mathis




Overview:
The program flow will start with csv files being loaded in. Ideally, in the Driver Run() method 
would a method called load() invoke the program to load in accounts from buyers.csv that would go into a 
vector of buyers, sellers.csv that would go into a vector of sellers, products.csv that loads in products up 
for sale associated with a seller, and bids.csv that loads in bids associated with buyers. Product and Bid 
objects would be instantiated and appended to their respective vectors. After load() has occurred, in 
Driver.Run() would we prompt the user to either login or create an account. If login, we invoke the 
Login() method, otherwise CreateAccount() method. The user will be saved under an active user attribute 
to the Driver class. From here, we can branch out the program flow to show the Buyer and Seller POV. 
If the client chooses to be a Buyer account, a dashboard of options invoked by 
activeUser.dashboard() should appear to give them options. It will follow as : viewing available products, 
placing/removing a bid on one of the products, overview of active bids, overview of products purchased. 
These will be handled by their respective methods in the Buyer class.  
Otherwise, if the client chooses to be a Seller account, a dashboard of options invoked by 
activeUser.dashboard() should appear to give them options . It will follow as : post a product, 
placing/removing the option to bid on their products, overview of their products sold/yet to be sold. These 
will be handled by their respective methods in the Seller class as well. 
Both accounts will also have the option to update their account information and look at their account 
balance.  
Whenever either a buyer finds a product for the price they are looking for or a seller finds a bid 
they are looking for, they will be handled by the class Manager. Here this class will have an overview of 
all bids and all products, matching them appropriately and mutating the respective parties. This Manager 
will attempt to mimic that of the Observer design pattern where the ‘subscribers’ would be all buyers and 
sellers and the ‘publisher’ would be Manager that will ‘notify’ –i.e. mutate the respective users once a 
match has been made. 



UML:
![uml_updated](https://github.com/user-attachments/assets/4ff96eda-0cb1-4d69-ab86-f2e83aab8032)
