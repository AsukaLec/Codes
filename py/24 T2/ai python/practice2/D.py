def problem1():
    x=1
    ans1=0
    while(x<=999):
        ans1+=x*x
        x+=2
    return ans1

def problem2(x):
    if x<0 :
        print("无实数解")
    else :
        g=x/2
        while(abs(x-g*g)>0.000001):
            g=(g+x/g)/2
        return g

x=int(input())
print(problem1())
ans = problem2(x)
print("{:.10f}".format(ans))