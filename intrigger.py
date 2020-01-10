def algo1(a, b, c):
    a2, b2, c2 = a, b, c
    l = [a2]
    while a2 < b2:
        if a2 + 2 <= b2:
            if (a2 + 2) % c != 0:
                a2 += 2
            else:
                a2+= 1
        else:
            a2 += 1
        l.append(a2)
    return len(l), l

def algo2(a, b, c):
    a2, b2, c2 = a, b, c
    l = [a2]
    while a2 < b:
        if a2 + 2 <= b:
            a2 += 2
        else:
            a2 += 1
        l.append(a2)
    return len(l), l

a, b, c = map(int, input().split(' '))

print("Wrong: ", algo2(a, b, c))

print("Right: ", algo1(a, b, c))

lenwrong = 1 + ((b - a) // 2) + ((b - a) % 2)

if (a % 2 == 1) and (c % 2 == 0):
    res = lenwrong - 1
    print("Res: ", res)
    exit(0)

print("Len wrong: ", lenwrong)

first = a + (c - (a % c))
if (a % 2 == 0):
    if first % 2 == 1:
        first += c
if (a % 2 == 1):
    if first % 2 == 0:
        first += c
print("First: ", first)

if (c > b):
    print("Result: ", lenwrong - 1)
    exit(0)

if (first > b):
    res = lenwrong - 1
    print("Result: ", res)
    exit(0)

if ((first - 1) % 2 == 1) and (c % 2 == 0):
    first -= 1
    res = ((first - a) // 2) + ((first - a) % 2)
    print("res1: ", res)
    res += ((b - first) // 2) + ((b - first) % 2) + 1
    print("Result: ", res - 1)
    exit(0)



lenwrong2 = 1 + ((b - first) // 2) + ((b - first) % 2)

print("Lenwrong2: ", lenwrong2)

full = lenwrong2 // c

print("Full c: ", full)
if (full == 0):
    start = a
    res = 0
else:
    start = first + full * (c * 2)
    start -= 1
    res = ((first - a) // 2) + ((first - a) % 2) + full * (c + 1)

print("Start: ", start)


print("Res first: ", res)
counter = 0
while start <= b:
    if start + 2 <= b:
        if (start + 2) % c != 0:
            start += 2
        else:
            start += 1
    else:
        start += 1
    res += 1
    counter += 1
print("Counter: ",counter)
print("Final result: ", res - 1)