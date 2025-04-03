number = int(input())
pivot = number - 1

table = [False] * 10000

buffer = [1]
for index in range (number - 1):

    data = buffer[index] + pivot
    if table[data] or data > number:
        data = abs(pivot - buffer[index])
    buffer.append (data)
    table[data] = True
    pivot -= 1

for element in buffer:
    print (element , end = ' ')