def quicksort(a):
    if len(a) <= 1:
        return a

    p = a[len(a) // 2]

    l = []
    m = []
    r = []

    for x in a:
        if x < p:
            l.append(x)
        elif x == p:
            m.append(x)
        else:
            r.append(x)

    return quicksort(l) + m + quicksort(r)


b = [3, 6, 8, 10, 1, 2, 1]
c = quicksort(b)
print(c)