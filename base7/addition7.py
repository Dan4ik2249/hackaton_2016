
def addition(a, b):
    res = 0
    tup = 0
    tdown = 0
    for i in range(max(len(str(a)), len(str(b)))+1):
        temp = a%10 + b%10 +tup
        a//=10
        b//=10
        tdown = temp%7
        tup = temp//7
        if (i == 0):
            res = tdown
        else:
            res = res + tdown*10**i

    return res
    

def main():
    a = 0
    b = 0

    with open("task.txt") as f:
        for line in f:
            a = int(line)
            b = addition(a,b)

    with open("key.txt", "w") as f:
        f.write(str(b))

    print(b)
    print(str(b))


if __name__ =="__main__":
    main();
