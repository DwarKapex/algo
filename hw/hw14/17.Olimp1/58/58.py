line = input()
n = int(line)
count = 0
x5 = 1
x8 = 1
x55 = 0
x88 = 0

n5 = n8 = n55 = n88 = 0
for i in range(2, n+1):
    n5 = x8 + x88
    n8 = x5 + x55
    n55 = x5
    n88 = x8
    x5 = n5
    x8 = n8
    x55=n55
    x88 = n88
    
print(x5+x8+x55+x88)