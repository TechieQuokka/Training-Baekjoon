def GetNumberOfRouterInstallation (houses, distance):

    count = 1
    previous = houses[0]
    for house in houses:
        interval = house - previous
        if interval < distance: continue

        count += 1
        previous = house
    return count

def FindMinimumDistance (houses, numberOfDevice, left, right):

    middle = (left + right) // 2
    if left > right: return middle

    if GetNumberOfRouterInstallation (houses, middle) >= numberOfDevice:
        return FindMinimumDistance (houses, numberOfDevice, middle + 1, right)
    else:
        return FindMinimumDistance (houses, numberOfDevice, left, middle - 1)

count, number = map(int, input().split())
source = []
for _ in range (count):
    source.append (int(input()))

source.sort()

print (FindMinimumDistance (source, number, 0, source[count - 1]))