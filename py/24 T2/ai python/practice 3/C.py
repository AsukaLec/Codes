def findPayment(loan, r, m):
    # 请在此添加代码，补全函数findPayment
    #********** Begin *********#
	return loan*r*((1+r)**m)/((1+r)**m-1)
    #********** End *********#

class Mortgage(object):
     def __init__(self, loan, annRate, months):
        # 请在此添加代码，补全函数__init__
        #********** Begin *********#
        self.loan = loan
        self.annRate = annRate
        self.months = months
        self.rate = annRate/100/12
        self.payment = findPayment(self.loan,self.rate,self.months)
        self.paid = [0]  
        self.owed = [loan]  

        
         #********** End *********#
        self.legend = None

     def makePayment(self):
        # 记录每月的还款情况
        self.paid.append(self.payment)
        interest = self.owed[-1] * self.rate
        principal = self.payment - interest
        self.owed.append(self.owed[-1] - principal)

     def getTotalPaid(self):
        # 计算到目前为止支付给银行的总金额
        return sum(self.paid)
 
     def __str__(self):
        return 'The Mortgage is {self.legend}, Loan is {self.loan}, Months is {self.months}, Rate is {self.rate:.2f}, Monthly payment is {self.payment:.2f}'.format(self=self)

if __name__=="__main__": 
    loan, annRate, months = [float(x) for x in input().split()]
    m1 = Mortgage(loan, annRate, months)
    print(m1)
    m1.makePayment()
    m1.makePayment()
    print('Two months payment is {:.2f}'.format(m1.getTotalPaid()))



# def findPayment(loan, r, m):
#     # 计算每月还款金额
#     return loan * (r * (1 + r)**m) / ((1 + r)**m - 1)

# class Mortgage(object):
#     def __init__(self, loan, annRate, months):
#         self.loan = loan
#         self.annRate = annRate
#         self.months = months
#         self.rate = annRate / 100 / 12  # 将年利率转换为月利率
#         self.payment = findPayment(loan, self.rate, months)
#         self.paid = [0]  # 已支付金额列表
#         self.owed = [loan]  # 剩余欠款列表
#         self.legend = None

#     def makePayment(self):
#         # 记录每月的还款情况
#         self.paid.append(self.payment)
#         interest = self.owed[-1] * self.rate
#         principal = self.payment - interest
#         self.owed.append(self.owed[-1] - principal)

#     def getTotalPaid(self):
#         # 计算到目前为止支付给银行的总金额
#         return sum(self.paid)

#     def __str__(self):
#         return 'The Mortgage is {self.legend}, Loan is {self.loan}, Months is {self.months}, Rate is {self.rate:.2f}, Monthly payment is {self.payment:.2f}'.format(self=self)
