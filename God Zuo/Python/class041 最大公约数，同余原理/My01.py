def gcd(a,b):
    return a if b==0 else gcd(b,a%b)
def lcm(a,b):
    return a//gcd(a,b)*b

print(gcd(30,50))
print(lcm(30,50))