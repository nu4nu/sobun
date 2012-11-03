import random

def isprime(n):
  if n == 2 or n == 3:
    return True
  if n < 2 or n & 1 == 0:
    return False

  d = n - 1
  s = 0
  while d & 1 == 0:
    d >>= 1
    s += 1

  for loop in xrange(50):
    a = random.randint(2, n-2)
    y = pow(a, d, n)
    if y == 1:
      continue
    for _ in xrange(s):
      if y == n-1:
        break
      y = y * y % n
    else:
      return False
  return True

def gcd(a, b):
  return a if b == 0 else gcd(b, a%b)

def phi(n):
  r = 1
  if n & 1 == 0:
    n >>= 1
    while n & 1 == 0:
      n >>= 1
      r += r
  p = 3
  while p * p <= n:
    if n % p == 0:
      n /= p
      r *= p-1
      while n % p == 0:
        n /= p
        r *= p
    p += 2
  if n > 1:
    r *= n-1
  return r

def cn(n, x):
  if n == 1:
    return x - 1
  elif n & 1 == 0:
    n >>= 1
    while n & 1 == 0:
      n >>= 1
      x *= x
    return cn(n, x * x) / cn(n, x)
  else:
    p = 3
    while p * p <= n:
      if n % p == 0:
        n /= p
        while n % p == 0:
          n /= p
          x **= p
        return cn(n, x ** p) / cn(n, x)
      p += 2
    return cn(1, x ** n) / cn(1, x)

