#STRUCTURI DE CONTROL

#citirea unui intreg x
x=int(input("Introduceti un numar intreg"))
print(x)

#afiseaza "PAR" daca x este par si "IMPAR" altfel

if x%2==0:
    print("PAR")
else:
    print("IMPAR")

#lasa un rand liber
print("\n")

#daca x>0 calculeaza x!
#altfel, x<-10 calculeaza (-x) + (-x+1) + ....+(-2*x)

if x>0:
    fact=1
    for i in range(1,x+1):
        fact=fact*i
    print("x!= ", fact)
elif x<-10:
    sum=0
    for i in range(-x,-2*x+1):
        sum+=i
    print("(-x) + (-x+1) + ....+(-2*x)= ", sum)


#initializare lista
L=[1,3,5,7,9]


#afisam valorile din L - while
i=0
while i<len(L):
    print(L[i])
    i+=1

for a in L:
        print(a)












