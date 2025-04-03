number = int(input())

result = [0] * number

increment = 1
left, right = 0, number - 1
while left < right:
    
    result[left], result[right] = increment, increment + 1
    if left % 2 == 0:
        result[left], result[right] = result[right], result[left]
    left, right = left + 1, right - 1
    increment += 2

if number % 2 == 1:
    result[number // 2] = number

for element in result:
    print(element, end = ' ')