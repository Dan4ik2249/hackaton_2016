def TenToSeven(a):
    tmp = 0
    i = 0
    res = 0
    while a > 0:
        tmp = a%7
        a //= 7
        res = tmp*10**i + res
        i+=1
    return res 

def main():
    stack = []
    operand = ["#", "!", ">", "="]
    with open("task.txt") as f:
        for line in f:
            line = line.rstrip()
            if line not in operand:
                tmp = int(str(line), 7)
                stack.append(tmp)
            else:
                a = int(stack.pop())
                b = int(stack.pop())
                if line == "#":
                    res = ~(a&b)
                    stack.append(res)
                elif line == "!":
                    res = ~(a|b)
                    stack.append(res)
                elif line == ">":
                    res = ~b|a
                    stack.append(res)
                elif line == "=":
                    res = ~(a^b)
                    stack.append(res)

    with open("key.txt", "w") as f:
        f.write(str(TenToSeven(stack[0])))

if __name__ == "__main__":
    main()
