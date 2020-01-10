import random
def algo(a, b, c):
    lenwrong = 1 + ((b - a) // 2) + ((b - a) % 2)

    if (a % 2 == 1) and (c % 2 == 0):
        res = lenwrong - 1
        return res

    #print("Len wrong: ", lenwrong)

    first = a + (c - (a % c))
    if (a % 2 == 0):
        if first % 2 == 1:
            first += c
    if (a % 2 == 1):
        if first % 2 == 0:
            first += c
    #print("First: ", first)

    if (c > b):
        return lenwrong - 1

    if (first > b):
        res = lenwrong - 1
        return res

    if ((first - 1) % 2 == 1) and (c % 2 == 0):
        first -= 1
        res = ((first - a) // 2) + ((first - a) % 2)
        #print("res1: ", res)
        res += ((b - first) // 2) + ((b - first) % 2) + 1
        return res - 1

    lenwrong2 = 1 + ((b - first) // 2) + ((b - first) % 2)

    #print("Lenwrong2: ", lenwrong2)

    full = lenwrong2 // c

    #print("Full c: ", full)
    if (full == 0):
        start = a
        res = 0
    else:
        start = first + full * (c * 2)
        start -= 1
        res = ((first - a) // 2) + ((first - a) % 2) + full * (c + 1)

    #print("Start: ", start)

    #print("Res first: ", res)
    while start <= b:
        if start + 2 <= b:
            if (start + 2) % c != 0:
                start += 2
            else:
                start += 1
        else:
            start += 1
        res += 1
    return res - 1

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
    return len(l) - 1
wrongans = 0
for i in range(100000):
    a = random.randint(1, 100)
    b = a + random.randint(1, 100)
    c = random.randint(1, 100)
    while (a % c == 0) or (b % c == 0):
        a = random.randint(1, 100)
        b = a + random.randint(1, 100)
        c = random.randint(1, 100)
    v = algo(a, b, c)
    v1 = algo1(a, b, c)
    if v != v1:
        print("a: ", a, " b: ", b, " c: ", c)
        print(v, " != ", v1, "right res: ", v1)
        wrongans += 1
print("Wrong answers: ", wrongans)