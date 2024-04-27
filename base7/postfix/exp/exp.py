symbols = ["#", "!", ">", "=", "(", ")"]
operand = symbols[:-2]

def TenToThir(a):
    tmp = 0
    res = ''
    while a > 0:
        tmp = a%13
        
        a //= 13
        if tmp > 9:
            tmp = chr(tmp+55)
        res = str(tmp) + res
    return res

def streak(a, b): #
    return ~(a&b)

def arrow(a, b): #!
    return ~(a|b)

def impl(a, b): #>
    return ~a|b

def eq(a, b): #=
    return ~(a^b)

def find_staple(mylist):
    staplelist = {}
    k = 0
    for i in range(len(mylist)):
        if mylist[i]=='(' or mylist[i]==')':
            staplelist[k]=[mylist[i], i]
            k+=1
    return staplelist

def helpme(li):
    a = '0t'
    for i in range(len(li)):
        if li[i] not in operand:
            if type(li[i])!=str:
                continue
            if a in li[i]:
                li[i] = int(li[i].split("t")[1], 13)
            else:
                li[i] = int(li[i], 7)
    res = int(li[0])
    for i in range(2, len(li), 2):
        if li[i-1] in operand:
            if li[i-1]=='#':
                res=streak(res,int(li[i]))
            elif li[i-1]=='!':
                res=arrow(res,int(li[i]))
            elif li[i-1]=='>':
                res=impl(res,int(li[i]))
            elif li[i-1]=='=':
                res=eq(res,int(li[i]))
            else:
                return
    return res

def func(stli, mylist):
    if len(stli)!=0:
        if stli[0][0]=='(' and stli[1][0]==')':
            start=stli[0][1]+1
            stop=stli[1][1]
            mylist.insert(start-1, helpme(mylist[start:stop]))
            del mylist[start:stop+2]
        elif stli[1][0]=='(' and stli[2][0]==')':
            start=stli[1][1]+1
            stop=stli[2][1]
            mylist.insert(start-1, helpme(mylist[start:stop]))
            del mylist[start:stop+2]
        stli = find_staple(mylist)
        func(stli, mylist)

    return mylist

def main():
    mylist = ['']
    
    with open("task.txt") as file:
        text = file.read().rstrip()

    k = 0
    for i in range(len(text)):
        if text[i] not in symbols:
            if k > len(mylist)-1:
                mylist.append("")
            mylist[k] = mylist[k] + text[i]
        else:
            if text[i-1] in symbols:
                mylist.append(text[i])
                k+=1
            else:
                mylist.append(text[i])
                k+=2

    for i in range(len(mylist)):
        if i+2 < len(mylist):
            if mylist[i]=='(' and mylist[i+2]==')':
                mylist.pop(i)
                mylist.pop(i+1)

    stli = find_staple(mylist)
    mylist = func(stli, mylist)
    res = helpme(mylist)
    print(res)
    print(TenToThir(res))

    with open("key.txt", "w") as f:
        f.write("0t"+TenToThir(res))

if __name__ == "__main__":
    main()
