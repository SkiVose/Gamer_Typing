import csv
import sys, os

originPath = 'D:/wordHub/temp.txt'
retPath = 'D:/wordHub/temp.csv'

def dealData():
    lines = []
    csvLines = []
    with open(originPath, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    for line in lines:
        line = line.rstrip('\n')
        line = line.replace('\t', ' ')
        tempLine = line.split(' ')
        print(tempLine)
        tmplist = [s for s in tempLine if len(s) > 0]

        data = {
            'word':f'{tmplist[0]}',
            'annotations':f'{tmplist[1]}'
        }
        # jsonLine = json.dumps(data, ensure_ascii=False)
        # print(jsonLine)

        csvLines.append(data)
        # print(tmpLine)

    # for line in csvLines:
    #     print(line)

    headers = ['word', 'annotations']

    with open(retPath, 'w', newline='') as f:
        f_csv = csv.DictWriter(f, headers)
        f_csv.writeheader()
        f_csv.writerows(csvLines)