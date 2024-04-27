import csv

def Luna(num):
    summ = 0
    parity = len(num)%2
    for i in range(len(num)-1, -1, -1):
        dig = ord(num[i]) - ord('0')
        if i%2==parity:
            dig*=2
            if dig>9:
                dig-=9
        summ+=dig
    if summ % 10==0:
        return True
    else:
        return False

def main():
    newdict = dict()
    with open("data.csv", mode="r", encoding='utf-8') as file:
        data_csv = csv.reader(file, delimiter=',', quoting=csv.QUOTE_ALL, skipinitialspace='True')
        count = 0
        next(data_csv, None)
        for row in data_csv:
            if Luna(row[5]):
                newdict[row[5]] = row[0] + ";" + row[3]

    newdict = sorted(newdict.items())
    print(newdict[41])

    with open("key.txt", "w") as file_w:
        file_w.write(newdict[41][1])

if __name__=="__main__":
    main()
