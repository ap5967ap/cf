from math import factorial


for i in range(1,10):
    len=2
    while True:
        a=int(str(i)*factorial(len))
        if a%9==0:
            print(i,len)
            break
        len+=1