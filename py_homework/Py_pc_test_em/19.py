class BankAccount:
    def __init__(self,id,ba):
        self.account_id=id
        self.balance=ba
    def deposit(self,money):
        self.balance+=money
    def withdraw(self,money):
        if self.balance>=money:
            self.balance-=money
        else:
            print('余额不足')

acc = BankAccount("1001", 500)
acc.deposit(200)
acc.withdraw(100)
acc.withdraw(1000)
print(acc.balance)