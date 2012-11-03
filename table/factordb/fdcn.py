#!/usr/local/bin/python

import sys
import re
import mathutil

class Factor:
  def __init__(self):
    self.n = 0
    self.x = 0
    self.ps = []
    self.cs = []

  def add(self, f):
    if f == 1:
      return False
    for i in xrange(len(self.cs)):
      c = self.cs[i]
      if c % f == 0:
        self.fs.append(f)
        cof = c / f
        if mathutil.isprime(cof):
          self.fs.append(cof)
          del self.cs[i]
        else:
          self.cs[i] = cof
        return True
    return False

class CnFactor(Factor):
  def __init__(self, string):
    if string[1] == '0':
      None
    ls = string[1:].split('(')
    (self.n, self.x) = map(int, ls[0].split(' ')[0:2])
    cn = mathutil.cn(self.n, self.x)
    if mathutil.isprime(cn):
      self.fs = [cn]
      self.cs = []
    else:
      self.fs = []
      self.cs = [cn]

    map(self.add, map(int, ls[1][:-2].split(' ')))

  def out(self):
    self.fs.sort()
    cof = 1
    for c in self.cs:
      cof *= c
    if cof == 1:
      cof = self.fs[-1]
      flag = 'P'
      fl = ' '.join(map(str, self.fs[:-1]))
    else:
      flag = 'C'
      fl = ' '.join(map(str, self.fs))
    if fl == '':
      fl = '1'
    print '(%d %d (%s) (%s %d))' % (self.n, self.x, fl, flag, len(str(cof)))

class FdFactor(Factor):
  def __init__(self, string):
    ls = string.split(' = ')
    ns = re.split('([-+^])', ls[0])
    if ns[3] == '+':
      self.n = int(ns[2]) * 2
    else:
      self.n = int(ns[2])
    self.x = int(ns[0])

    self.fs = []
    self.cs = []
    for fl in ls[1].split('*'):
      if '^' in fl:
        (f, p) = map(int, fl.split('^'))
      else:
        (f, p) = (int(fl), 1)
      if(mathutil.isprime(f)):
        for _ in xrange(p):
          self.fs.append(f)
      else:
        for _ in xrange(p):
          self.cs.append(f)

def main():
  if len(sys.argv) < 3:
    print 'Usage:', sys.argv[0], 'fdfile cnfile'
    sys.exit()

  try:
    fdfile = open(sys.argv[1], 'rb')
  except IOError:
    print sys.argv[1], 'doesn\'t exist!'
    sys.exit()

  try:
    cnfile = open(sys.argv[2], 'rb')
  except IOError:
    print sys.argv[2], 'doesn\'t exist!'
    sys.exit()

  for fl in fdfile:
    cl = cnfile.readline()
    fd = FdFactor(fl)
    cn = CnFactor(cl)

    fd_cn = set(fd.fs) - set(cn.fs)
    found = False
    for f in fd_cn:
      if cn.add(f):
        found = True

#    if found:
#      cn.out()

    cn_fd = sorted(set(cn.fs) - set(fd.fs))
    for f in cn_fd:
      if fd.add(f):
        None
        #print fd.n, fd.x, f

    fd_cn_c = list(set(fd.cs) - set(cn.cs))

    if fd_cn_c != []:
      print fd.n, fd.x, fd_cn_c
      for n in xrange(1, fd.n+1, 2):
        if fd.n % n == 0:
          nn = fd.n / n
          cnc = mathutil.cn(nn, fd.x)
          for c in fd_cn_c:
            g = mathutil.gcd(c, cnc)
            if g == c:
              print fd.n, fd.x, nn, fd.x, '>', c
            elif g == cnc:
              print fd.n, fd.x, nn, fd.x, '<', c
            elif g > 1:
              print fd.n, fd.x, nn, fd.x, '|', c

  fdfile.close()
  cnfile.close()

if __name__ == '__main__':
  main()

