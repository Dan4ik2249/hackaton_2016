import csv

def main():
    newdict = dict()
    with open("data.csv", mode="r", encoding='utf-8') as file:
        data_csv = csv.reader(file, delimiter=',', quoting=csv.QUOTE_ALL, skipinitialspace='True')
        count = 0
        for line in data_csv:
            if count > 1:
                tmp = line[3].split(',')[0]
                if tmp in newdict:
                    newdict[tmp][0]+=1
                    if line[1] not in newdict[tmp]:
                        newdict[tmp].append(line[1])
                else:
                    newdict[tmp]=[1, line[1]]
            count+=1

        newdict=sorted(newdict.items(), key=lambda x: x[1][0], reverse=True)[0]
        print(newdict)
        res = newdict[1][1] + ";" + newdict[0]
        print(res)
        with open("key.txt", "w") as file_w:
            file_w.write(res)

if __name__=="__main__":
    main()
