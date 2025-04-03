number = int(input())
right = input()

left = right[:]
left = ''.join(reversed(left))

for _ in range (number):
    print (left, end = '')