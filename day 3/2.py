f = open("input")
numbers = list()
t = 0


for line in f.readlines():
    numbers.append(line)

most = numbers
least = numbers

def keep_commons(pos, numbers, is_most):
    selected = list()
    common = [0,0,0,0,0,0,0,0,0,0,0,0]
    total = 0


    for num in numbers:
        for i in range(0,12):       
            if (num[i] == '1'):
                common[i] += 1
        total +=1
    
    for i in range(0,12):
        if total-common[i] <= common[i]:
            common[i] = 1 if (is_most) else 0
        else:
            common[i] = 0 if (is_most) else 1
    
    for num in numbers:
        if str(common[pos]) == num[pos]:
            selected.append(num)

    return selected


while t < 12:
    if len(most) > 1:
        most = keep_commons(t, most, True)
    if len(least) > 1:
        least = keep_commons(t, least, False)
    t += 1

  

print(most)
print(least)

print(int(most[0], 2) * int(least[0], 2))