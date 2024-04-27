import csv

def main():
    newdict = dict()
    with open("data.csv", mode="r", encoding='utf-8') as file:
        data_csv = csv.reader(file, delimiter=',', quoting=csv.QUOTE_ALL, skipinitialspace='True')
        count = 0
        for line in data_csv:
            count+=1
            if count==1:
                continue
            tmp = line[2]
            if tmp in newdict:
                newdict[tmp][0]+=float(line[3])
                if line[1] not in newdict[tmp][1]:
                    newdict[tmp][1][line[1]]=line[3]
            else:
                newdict[tmp]=[float(line[3]), {line[1]:line[3]}]
            

        newdict=sorted(newdict.items(), key=lambda x: x[1][0], reverse=True)
        print(f'To: {newdict[0][0]}, sum: {newdict[0][1][0]}')
        print("COUNT of transfers: ", len(newdict[0][1][1]))
        print(f'To: {newdict[1][0]}, sum: {newdict[1][1][0]}')
        print("COUNT of transfers: ", len(newdict[1][1][1]))
        print(f'To: {newdict[2][0]}, sum: {newdict[2][1][0]}')
        print("COUNT of transfers: ", len(newdict[2][1][1]))
        res=newdict[0][0]
        newdict=sorted(newdict, key=lambda x: len(x[1][1]), reverse=True)
        print("sorting by transfers:",newdict[0][0], newdict[1][0], newdict[2][0])

        with open("key.txt", "w") as file_w:
            file_w.write(res)

if __name__=="__main__":
    main()
