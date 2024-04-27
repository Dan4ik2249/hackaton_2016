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
		
def main():
    a = '0t'
    tmp = 0
    res = 0
    with open("task.txt") as f:
        for line in f:
            if a in line:
                res += int(line.split("t")[1], 13)
            else:
                res+=int(line, 7)

    
    with open("key.txt", "w") as f:
        f.write('0t'+TenToThir(res))

if __name__ == "__main__":
    main()
