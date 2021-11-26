
// ------------------------------------------------------------------------------
// Ladan Guled #300021664
// Sakeena Adinoyi #300121703
// -----------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>

#include "Bank.h"

using namespace std;

double DepositAccount::rate = 6.50;
double totalAccounts = 0.0;

//******************************************************************
// Basic functions of the BankAccount class
//******************************************************************
inline BankAccount::BankAccount()
{
    accountId = type = updateDate = 0;
    clientName = new char[1];
    balance = 0.0;
}

inline BankAccount::BankAccount(long id, int newType,
                                    char * name, long newDate, double newBalance):
                                    accountId(id), type(newType),
                                    updateDate(newDate), balance(newBalance)
{
     clientName = new char[strlen(name) + 1];
     strcpy(clientName, name);
}

inline BankAccount::~BankAccount()
{
     if (clientName)
     {
          delete [] clientName;
     }
}

inline void BankAccount::setAccountId(long account)
{
     accountId = account;
}

inline void BankAccount::setType(int newType)
{
     type = newType;
}

inline void BankAccount::setClientName(char * name)
{
     if (clientName)
     {
          delete [] clientName;
     }
     clientName = new char[strlen(name) + 1];
     strcpy(clientName, name);
}

inline void BankAccount::setUpdateDate(long newDate)
{
     updateDate = newDate;
}

inline void BankAccount::setBalance(double newBalance)
{
     balance = newBalance;
}

void BankAccount::print() 
{
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << accountId << "\t\t\t" << type << "\t" << updateDate << "\t\t" << balance;
}

//******************************************************************
// Basic functions of the DepositAccount class
//******************************************************************
inline DepositAccount::DepositAccount(long id, int newType, char * name,
                                    long newDate, double balanceArg, int nbyear) :
                                    BankAccount(id, newType, name,
                                    newDate, balanceArg), nbyears(nbyear)
{}

inline void DepositAccount::setNbYears(int nbyear)
{
     nbyears = nbyear;
}

void DepositAccount::print() 
{
    Bonus();
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\t" << nbyears << "\t\t" << rate << endl;
}

//******************************************************************
// Functions of the class DepositAccount. It allows to calculate
// the annual bonus on deposit accounts.
// Inputs: Nothing
// Outputs: Nothing
//******************************************************************
void DepositAccount::Bonus()
{
  setBalance(getBalance() + (getBalance()* getRate() * (getNbYears())/36000.00));
}



//******************************************************************
// Basic functions of the LoanAccount class
//******************************************************************
inline LoanAccount::LoanAccount(long id, int newType, char * name,
                                    long newDate, double newBalance, int nbyear,
                                    double newRate) : BankAccount(id, newType,
                                    name, newDate, newBalance), nbyears(nbyear), rate(newRate)
{ Bonus(); }

inline void LoanAccount::setNbYears(int nbyear)
{
     nbyears = nbyear;
}

inline void LoanAccount::setRate(double newRate)
{
     rate = newRate;
}

void LoanAccount::print() 
{
    BankAccount::print();
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\t" << nbyears << "\t\t" << rate << endl;
}

void LoanAccount::Bonus()
{
  setBalance(getBalance() + (getBalance()* getRate() * (getNbYears())/36000.00));
}

//******************************************************************
// Basic functions of the Transaction class
//******************************************************************
inline Transaction::Transaction(long idTr, int typeTr, long dateTr,
                                    int codeTr = 01, double amountTr):
                                    accountId(idTr), type(typeTr),
                                    date(dateTr), code(codeTr),
                                    amount(amountTr)
{ }

inline void Transaction::setAccountId(long compteTr)
{
     accountId = compteTr;
}

inline void Transaction::setType(int typeTr)
{
     type = typeTr;
}

inline void Transaction::setDate(long dateTr)
{
     date = dateTr;
}

inline void Transaction::setCode(int codeTr)
{
     code = codeTr;
}

inline void Transaction::setAmount(double amountTr)
{
     amount = amountTr;
}




//****************************************************************************
// Purpose: Sort a list of bank accounts in ascending order of ids and types.
//
// WARNING: This sort leaves the last account (of id 0) of the list which has 
// its position to assure the tests of end of list later !!!
//
// Inputs: listAccount(BankAccount *), a list of bank accounts.
// Outputs: listAccount(BankAccount *), sorted list of bank accounts.
//****************************************************************************
void sortAccounts(BankAccount ** list)
{
     void order(BankAccount** , BankAccount**);  //call to helper method
     int j, k;                      
    for(j=0; j<6-1; j++){ //TODO: check for n 
         for(k=j+1; k<6; k++){
              order(list+j, list+k); 
         }       
    }  
	
}

void order(BankAccount** p1, BankAccount** p2){
     if( (*p1)->getAccountId() > (*p2)->getAccountId())  {  
        BankAccount* tempptr = *p1;
        *p1 = *p2;  
        *p2 = tempptr;  
     }  
  }          

    
//******************************************************************
// Purpose: This function reads the file 'clients.txt' and builds 
// an array containing the different bank accounts of customers.
//
// Inputs: Nothing
// Output: listAccount(type: BankAccount *), the list of bank 
//         accounts read from the file 'clients.txt'.
//******************************************************************
BankAccount ** readAccounts()
{
    ifstream inputFile("clients.txt");	// Opening the input file
    if (!inputFile)            		// If the file is not found...
    {
        cout << "File not found !!!" << endl;
        exit(0);
    }

    BankAccount ** listAccounts = new BankAccount*[K_SizeMax];
    if (!listAccounts) {
        cout << "Full memory. !!!" << endl;
        return listAccounts;
    }

    BankAccount ** pAccount = listAccounts;
	 
    long accountRead, dateRead;
    int TypeRead, nbyearRead, counter = 0;
    double balanceRead, RateRead;
    char nameRead[60];
	 
    inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
    inputFile.getline(nameRead, 60);
	 
    while (inputFile && (counter < K_SizeMax - 1)){
       //check type of account
          if(TypeRead != 01 &&  TypeRead != 02){ //not checking or savings account
               if(TypeRead == 03){
                    DepositAccount *d = new DepositAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead, nbyearRead);
                    listAccounts[counter] = d;
               } 
               else{
                    LoanAccount *l = new LoanAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead, nbyearRead, RateRead);
                    listAccounts[counter] = l;
               }
          }
          else{
               if(TypeRead == 01){
                    BankAccount *a = new BankAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead);
                    listAccounts[counter] = a;
               }
               else{
                    BankAccount *b = new BankAccount(accountRead, TypeRead, nameRead, dateRead, balanceRead);
                    listAccounts[counter] = b;
               }
          }
          inputFile >> accountRead >> TypeRead >> dateRead >> balanceRead >> nbyearRead >> RateRead;
          inputFile.getline(nameRead, 60);
          pAccount++;
          counter++;
    }
     *pAccount = new BankAccount();
     return listAccounts;
}


//*****************************************************************************************
// Purpose: This function validates whether the transaction code 
//          corresponds to the correct account:
//              - 01 ==> account (01: Check, 02: Savings, 03: Deposit and 04: Loan)
//              - 02 ==> account (01: Check, 02: Savings)
//              - 03 ==> account (01: Check).
//
// Inputs: trans (Type: Transaction) an instance of the Transaction class.
// Outputs: true (Type bool) if the transaction matches one of the accounts listed above.
// false (Type bool) otherwise.
//*****************************************************************************************
Bool BankAccount::validateTransaction(const Transaction trans) const
{
    if ( ( (trans.getCode() == 02) && ( isDepositAccount() || isLoanAccount()) ) ||
         ( (trans.getCode() == 03) && ( isDepositAccount() || isLoanAccount() || isSavingsAccount() ) ) )
      {
       return FALSE;
      }
    else
      {
       return TRUE;
      }
        
}





//******************************************************************************
// Purpose: This function is used to execute the transaction already performed 
// (update the balance of an account).
//
// Inputs: trans (Transaction Type), instance of Transaction class
// Outputs: Nothing
//*******************************************************************************
void BankAccount::executeTransaction(const Transaction trans)
{
     if (validateTransaction(trans))
       {
         if (trans.getCode() == 01)    // Deposit
           { 
             setBalance(getBalance() + trans.getAmount());
           }
         else 
           { if (trans.getCode() == 02)    // Withdrawal
                {
                    
                  if (getBalance() >= trans.getAmount())
                     { setBalance(getBalance() - (trans.getAmount() + 0.50)); }
                  else {cout << " insufficient balance!! " << endl; }
                }
             else 			// Check
                {
                  if (getBalance() >= trans.getAmount())
                     { 
                       setBalance(getBalance() - trans.getAmount());
                     }
                  else {cout << " insufficient balance!! " << endl; }
                }
           }
                 
       }   
 
}

//***********************************************************************
// Purpose: This function is used to execute a read transaction
// (updating the balance of the loan account).
//
// Inputs: trans (Transaction Type), instance of the Transaction class
// Outputs: Nothing
//***********************************************************************
void LoanAccount::executeTransaction(const Transaction trans)
{
     if (validateTransaction(trans))
     {
        if (trans.getCode() == 01)    // Deposit
        {
          setBalance(getBalance() - trans.getAmount());
         
        }
     }
}





//*************************************************************************
// Purpose: This function allows to read the file 'transact.txt' 
//          and to update the accounts concerned by the transactions read.
//
// Inputs: listAccount (type BankAccount *), the list of bank accounts.
// Output: Nothing.
//*************************************************************************
void updateAccounts(BankAccount ** listAccounts) {
     ifstream inputFile("transact.txt");	// Opening the input file
     string line;
     while(getline(inputFile,line)){
          long trID=stol(line.substr(0,5));
          int trType=stoi(line.substr(6,8));
          long trDate=stol(line.substr(9,15));
          int trCode=stoi(line.substr(16,18));
          double trAmount=stod(line.substr(19, -1));
          Transaction t(trID, trType, trDate, trCode, trAmount);
     
          for (int i=0; i<6; i++){
               /*BankAccount* b=listAccounts[i];
               if ((*b).getAccountId()==trID && (*b).getType()==trType){
                    cout<<trID<<" "<<trType<<" "<<trDate<<" "<<trCode<<" "<<trAmount<<" "<<endl;
                    (*b).executeTransaction(t); //without dynamic cast
                    cout<<"siccessful transaction"<<endl;
                    (*b).print();
               }*/
               
               
               if ((*(listAccounts[i])).getAccountId()==trID && (*(listAccounts[i])).getType()==trType){
                    DepositAccount* d=dynamic_cast<DepositAccount*>(listAccounts[i]);
                    if (d!=nullptr){
                         (*d).executeTransaction(t);
                        
                    }else{
                       LoanAccount* l=dynamic_cast<LoanAccount*>(listAccounts[i]);
                       if (l!=nullptr){
                            (*l).executeTransaction(t);
                            
                       }else{
                            BankAccount* b=listAccounts[i];
                            (*b).executeTransaction(t); 
                           
                         
                       }  
                    }
                    
               }
               
               
          }
     }
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
}

//******************************************************************************
// Purpose: This function displays the list of bank accounts for all customers.
//
// Inputs: listAccount (type: BankAccount *), the list of bank accounts.
// Outputs: Nothing
//******************************************************************************
void displayAccounts(BankAccount ** listAccounts)
{
    cout << endl << endl << endl;
    
    Bool find[K_SizeMax];
    for(int k = 0; k < K_SizeMax; k++) {find[k] = FALSE;}

    cout << "                       THE REPORT OF THE BANK ACCOUNTS OF CLIENTS" << endl;
    cout << "                       ------------------------------------------" << endl << endl;
     
    int i = 0;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    for(int x=0; x<6; x++){
         if (!find[x]){
          long accountID=(*(listAccounts[x])).getAccountId();
          cout<<"Client Name: "<<(*(listAccounts[x])).getClientName()<<endl;
          cout << "Bank Account" << "\t\t" << "Type" << "\t" << "Update Date" << "\t" << "Balance"<< "\t\t" << "Nb. Years" << "\t" << "Rate" << endl;;
          cout << "------------" << "\t\t" << "----" << "\t" << "-----------" << "\t" << "-------"<< "\t\t" << "---------" << "\t" << "----" << endl;;
          i=x;
          while(accountID==(*(listAccounts[i])).getAccountId()){
               /*(*(listAccounts[i])).print(); //without dynamic cast
               cout<<endl;*/
                    DepositAccount* d=dynamic_cast<DepositAccount*>(listAccounts[i]);
                    if (d!=nullptr){
                         (*d).print();
                         totalAccounts+=(*d).getBalance();

                    }else{
                       LoanAccount* l=dynamic_cast<LoanAccount*>(listAccounts[i]);
                       if (l!=nullptr){
                            (*l).print();
                            totalAccounts+=(*l).getBalance();
                       }else{
                            BankAccount* b=listAccounts[i];
                            (*b).print();
                            totalAccounts+=(*b).getBalance();
                            cout<<endl;
                       }  
                    }
                    
                    find[i]=TRUE;
                    i++;
              
          }
          cout << "            " << "\t\t" << "    " << "\t" << "           " << "\t" << "-------"<<endl;
          cout<<"\t\t"<<"TOTAL ACCOUNTS: "<<totalAccounts<<endl<<endl;
          totalAccounts=0;
          
          
         }
         
    } 
    
	

	
	
}




int main()
{
   
    BankAccount ** list = readAccounts();
    
    sortAccounts(list);
    displayAccounts(list);
    
    updateAccounts(list);
    
    cout << endl << endl;
    cout << "               ************************************************" << endl;
    cout << "               * RE-DISPLAY OF DATA AFTER THE UPDATE *" << endl;
    cout << "               ************************************************" << endl;
    displayAccounts(list);
    cout << endl;

	system("PAUSE");
	return 0;
}
