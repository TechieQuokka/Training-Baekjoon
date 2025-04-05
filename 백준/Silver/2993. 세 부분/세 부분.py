data = input()

buffer = []

for row in range (len(data)):
    for column in range (row + 1, len(data) - 1):

        buffer.append (data[:row + 1][::-1] + data[row + 1:column + 1][::-1] + data[column + 1:][::-1])

buffer.sort()
print (buffer[0])