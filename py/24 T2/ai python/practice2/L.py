#     *
#   * * *
# * * * * *
#   * * *
#     *
def printup(x):
    times = int((x-1)/2)
    for i in range(times,0,-1) :
        print(" "*2*i,end="")
        for t in range(0,2*(times - i)):
            print("* ",end="")
        print("*")


def printmiddle(x):
    for i in range(1,x):
        print("* ",end="")
    print("*")

def printdown(x):
    times = int((x-1)/2)
    for i in range(0,times-1):
        print(" "*2*(i+1),end="")
        
        
        print("* "*(x-2*i-3),end="")
        print("*")


    print(" "*2*times,end="")
    print("*",end="")
      


def main():
    x=int(input())
    
    if x % 2 == 0 :
        raise ValueError
    elif x == 1 :
        print("*")
    else :
        printup(x)
        printmiddle(x)
        printdown(x)
main()
