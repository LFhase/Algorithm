a = input();
a = int(a)
x_i = 33.0
x_i1 = 33.0
th = 1e-3
delta = 100

while delta >=th:
    x_i1 = (x_i+a/x_i)/2.0
    delta = abs(x_i-x_i1)
    x_i = x_i1

print(int(x_i))
    