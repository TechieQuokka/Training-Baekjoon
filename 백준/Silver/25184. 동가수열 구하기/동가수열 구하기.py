import math

number = int(input())

buffer = []

left, right = math.ceil(number / 2), number
for element in range (number // 2):

    buffer.append (left)
    buffer.append (right)

    left, right = left - 1, right - 1

if number % 2 == 1:
    buffer.append (1)

for element in buffer:
    print (element, end = ' ')