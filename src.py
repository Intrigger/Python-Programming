import math
n = int(input())
if (n >= 0) and (math.sqrt(n).is_integer()):
    print(int(math.sqrt(n)))
    exit(0)
l = [n]
i = n
c = 1
'''
while not ((i >= 0) and math.sqrt(i).is_integer()) or (i < 0):
    i += (2 * c - 1)
    c += 1
print("Loop check: ", math.sqrt(i - n), math.sqrt(i))
print(l)'''

if (n == 0):
    print(0)
else:
    if n > 0:
        sqrt = int(math.sqrt(n))
        start = sqrt
        found = False
        x1, x2 = 0, 0
        while start >= 2:
            if n % start == 0:
                num = start * (start - 1)
                if ((n - num) >= start) and (n - num) % start == 0:
                    x1 = (((n - num) // start) - 1) // 2
                    x2 = (((n - num) // start + (2 * (start - 1))) - 1) // 2 + 1
                    if (x2**2 - x1**2 == n):
                        found = True
                        print(int(math.sqrt(n + x1**2)))
                        break
            start -= 1
        if not found:
            if n % 2 == 1:
                x1, x2 = (n - 1) // 2, (n - 1) // 2 + 1
                print(x2)
            else:
                print("none")
    else:
        n = abs(n)
        sqrt = int(math.sqrt(n))
        start = sqrt
        found = False
        x1, x2 = 0, 0
        while start >= 2:
            if n % start == 0:
                num = start * (start - 1)
                if ((n - num) >= start) and (n - num) % start == 0:
                    x1 = (((n - num) // start) - 1) // 2
                    x2 = (((n - num) // start + (2 * (start - 1))) - 1) // 2 + 1

                    if (x2 ** 2 - x1 ** 2 == n):
                        print(x1)
                        found = True
                        break
            start -= 1
        if not found:
            if n % 2 == 1:
                x1, x2 = (n - 1) // 2, (n - 1) // 2 + 1
                print(x1)
            else:
                print("none")