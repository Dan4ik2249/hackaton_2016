import hashlib

def main():
    newdict = dict()
    count = 0
    with open("data.csv", mode="r", encoding='utf-8') as file:
        for line in file:
            if count==0:
                print(line)
            else:
                line = line.rstrip().split(",", 2)
                tmp = line[1].strip().strip('"')
                if tmp in newdict:
                    newdict[tmp][1]+=1
                else:
                    newdict[tmp]=[line[2].split('" "')[1].strip('"'), 1]
            count+=1
    count = 0
    agent = ''
    ip = ''
    for key in newdict:
        if newdict[key][1] > count:
            count = newdict[key][1]
            agent = newdict[key][0]
            ip = key
    print(f'IP: {ip}, AGENT: {agent}, COUNT: {count}')

    with open("key.txt", "w") as file_w:
        file_w.write(hashlib.md5(agent.encode('utf-8')).hexdigest())
if __name__ == "__main__":
    main()
