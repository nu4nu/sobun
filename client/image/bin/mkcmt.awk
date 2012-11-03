#!/bin/awk -f

BEGIN{
  np = ARGV[--ARGC]
}

function normalize(a){
  while(a ~ /^0.*:?..*:.*/){
    sub(/^0:?/, "", a)
  }
  return a
}

function encode(a,  b){
  b = sprintf("%02d", a % 60) b
  a = int(a / 60)
  b = sprintf(a < 60 ? "%d:" : "%02d:", a % 60) b
  a = int(a / 60)
  if(a == 0) return b
  b = sprintf(a < 24 ? "%d:" : "%02d:", a % 24) b
  a = int(a / 24)
  if(a == 0) return b
  b = a ":" b
  return b
}

function decode(a,  b){
  match(a, /[0-9]+$/)
  b += substr(a, RSTART, RLENGTH)
  if(RSTART <= 1) return b
  sub(/:[0-9]+$/, "", a)
  match(a, /[0-9]+$/)
  b += substr(a, RSTART, RLENGTH) * 60
  if(RSTART <= 1) return b
  sub(/:[0-9]+$/, "", a)
  match(a, /[0-9]+$/)
  b += substr(a, RSTART, RLENGTH) * 60 * 60
  if(RSTART <= 1) return b
  sub(/:[0-9]+$/, "", a)
  b += a * 60 * 60 * 24
  return b
}

/relation filtering/{
  state = 0
}
/linear algebra/{
  state = 1
}
/square root phase/{
  state = 2
}
/^#/{
  state = 3
}

state == 3 {
  if(/^[0-9]/){
    if(mini[$1] == 0 || mini[$1] > $2){
      mini[$1] = $2
    }
    if(maxi[$1] < $2){
      maxi[$1] = $2
    }
    nq[$1]++
    total[$1] += $3
    next
  }
  print
  if(/ time [0-9:]+/){
    sub(/.*time /, "")
    times[4] = normalize($0)
  }
}

/elapsed time [0-9:]+/{
  if(times[state] != ""){
    extra = extra "+ phase "state": "times[state]"\n"
  }
  sub(/.*time /, "")
  times[state] = normalize($0)
}
/added [0-9]+ free relations/{
  if(state == 0){
    sub(/.*added/, "free relations:")
    sub(/ free.*/, "")
    frel = $0
  }
}
/heaviest cycle: [0-9]+/{
  if(state == 0){
    sub(/.*cycle/, "cut")
    sub(/ rel.*/, "")
    cut = $0
  }
}
/dependency [0-9]+/{
  if(state == 2){
    sub(/.*dependency /, "")
    if($0 == 1){
      deps = " (1dep)"
    }else{
      deps = " ("$0"deps)"
    }
  }
}
/p[0-9]+ factor: [0-9]+/{
  if(state == 2){
    sub(/.*prp/, "P")
    sub(/factor:/, "=")
    factors = factors $0"\n"
  }
}

END{
  for(bits = 11; bits <= 16; bits++){
    if(bits in nq){
      maxi[bits]++
      _siever = bits"("mini[bits]"-"maxi[bits]")"
      _avgtime = nq[bits]" * "sprintf("%.1f", total[bits] / nq[bits] / np)"sec. ("mini[bits]"-"maxi[bits]")\n"
      if(siever == ""){
        siever = _siever
        avgtime = _avgtime
      }else{
        siever = siever"/"_siever
        avgtime = avgtime"      "_avgtime
      }
      if(mini[0] == 0 || mini[0] > mini[bits]){
        mini[0] = mini[bits]
      }
      if(maxi[0] < maxi[bits]){
        maxi[0] = maxi[bits]
      }
      total[0] += total[bits]
    }
  }
  if(index(siever, "/") == 0){
    sub(/\(.*/, "", siever)
  }
  total[0] = int(total[0] / np + 0.5)
  times[3] = encode(total[0])
  times[5] = encode(decode(times[0]) + decode(times[1]) + decode(times[2]) + total[0] + decode(times[4]))
  nf = length(times[5])
  printf "\n" \
         factors \
         "\n" \
         "siever: "siever"\n" \
         "sieving range: "mini[0]"-"maxi[0]"*10^4\n" \
         frel"\n" \
         "\n" \
         "sora: "avgtime \
         "\n" \
         cut"\n" \
         "\n"
  if(times[4] != ""){
    printf "polysel  : %"nf"s\n", times[4]
  }
  printf "latsieve : %"nf"s\n", times[3]
  printf "filtering: %"nf"s\n", times[0]
  printf "lanczos  : %"nf"s\n", times[1]
  printf "sqrt     : %"nf"s%s\n", times[2], deps
  printf "------------"
  for(i = 0; i < nf; i++){
    printf "-"
  }
  printf "\n" \
         "total    : %"nf"s\n", times[5] \
         extra
}

