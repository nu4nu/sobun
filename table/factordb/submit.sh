#!/bin/sh

#msg=`seq 696 1000 | awk '{for(i=3;i<9;i+=2)printf$0"%%5E210%%2B1+%%3D+"$0"%%5E"210/i"%%2B1%%0A"}'`
#msg=`seq 100 1000 | awk '{printf$0"%%5E130%%2B1%%3D"$0"%%5E"26"%%2B1%%0A"}'`
#msg=`seq 308 1000 | awk '{printf$0"%%5E130%%2B1%%3D"$0"%%5E"10"%%2B1%%0A"}'`
#msg=`seq 76 1000 | awk '{for(i=5;i<9;i+=2)printf$0"%%5E140%%2B1%%3D"$0"%%5E"140/i"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{for(i=3;i<20;i+=14)printf$0"%%5E153%%2B1%%3D"$0"%%5E"153/i"%%2B1%%0A"}'`
msg=`seq 872 1000 | awk '{for(i=3;i<19;i+=2)if(153%i==0)printf$0"%%5E153%%2B1%%3D"$0"%%5E"153/i"%%2B1%%0A"}'`
#msg=`seq 44 1000 | awk '{for(i=3;i<20;i+=10)printf$0"%%5E156%%2B1%%3D"$0"%%5E"156/i"%%2B1%%0A"}'`
#msg=`seq 950 1000 | awk '{for(i=3;i<9;i+=4)printf$0"%%5E168%%2B1%%3D"$0"%%5E"168/i"%%2B1%%0A"}'`
#msg=`seq 781 1000 | awk '{for(i=3;i<7;i+=2)printf$0"%%5E180%%2B1%%3D"$0"%%5E"180/i"%%2B1%%0A"}'`
#msg=`seq 796 1000 | awk '{for(i=3;i<15;i+=2)if(195%i==0)printf$0"%%5E195%%2B1%%3D"$0"%%5E"195/i"%%2B1%%0A"}'`
#msg=`seq 102 1000 | awk '{printf$0"%%5E125%%2D1%%3D"$0"%%5E"25"%%2D1%%0A";printf$0"%%5E125%%2B1%%3D"$0"%%5E"25"%%2B1%%0A"}'`
#msg=`seq 62 1000 | awk '{printf$0"%%5E112%%2B1%%3D"$0"%%5E"16"%%2B1%%0A";printf$0"%%5E144%%2B1%%3D"$0"%%5E"48"%%2B1%%0A"}'`
#msg=`seq 798 1000 | awk '{for(i=3;i<15;i+=2)if(195%i==0)printf$0"%%5E195%%2D1%%3D"$0"%%5E"195/i"%%2D1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E119%%2D1%%3D"$0"%%5E"17"%%2D1%%0A";printf$0"%%5E119%%2B1%%3D"$0"%%5E"17"%%2B1%%0A"}'`
#msg=`seq 822 1000 | awk '{for(i=3;i<20;i+=14)printf$0"%%5E153%%2D1%%3D"$0"%%5E"153/i"%%2D1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E104%%2B1%%3D"$0"%%5E"8"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E141%%2D1%%3D"$0"%%5E"47"%%2D1%%0A";printf$0"%%5E141%%2B1%%3D"$0"%%5E"47"%%2B1%%0A"}'`
#msg=`seq 74 1000 | awk '{printf$0"%%5E138%%2B1%%3D"$0"%%5E"46"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E115%%2D1%%3D"$0"%%5E"23"%%2D1%%0A";printf$0"%%5E115%%2B1%%3D"$0"%%5E"23"%%2B1%%0A"}'`
#msg=`seq 789 1000 | awk '{for(i=3;i<9;i+=4)printf$0"%%5E147%%2D1%%3D"$0"%%5E"147/i"%%2D1%%0A"}'`
#msg=`seq 789 1000 | awk '{for(i=3;i<9;i+=4)printf$0"%%5E147%%2B1%%3D"$0"%%5E"147/i"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E129%%2B1%%3D"$0"%%5E"43"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E129%%2D1%%3D"$0"%%5E"43"%%2D1%%0A"}'`
#msg=`seq 104 1000 | awk '{printf$0"%%5E98%%2B1%%3D"$0"%%5E"14"%%2B1%%0A"}'`
#msg=`seq 968 1000 | awk '{for(i=3;i<17;i+=2)if(165%i==0)printf$0"%%5E165%%2B1%%3D"$0"%%5E"165/i"%%2B1%%0A"}'`
#msg=`seq 970 1000 | awk '{for(i=3;i<17;i+=2)if(165%i==0)printf$0"%%5E165%%2D1%%3D"$0"%%5E"165/i"%%2D1%%0A"}'`
#msg=`seq 579 1000 | awk '{for(i=3;i<17;i+=2)if(150%i==0)printf$0"%%5E150%%2B1%%3D"$0"%%5E"150/i"%%2B1%%0A"}'`
#msg=`seq 88 1000 | awk '{for(i=3;i<13;i+=8)if(132%i==0)printf$0"%%5E132%%2B1%%3D"$0"%%5E"132/i"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E123%%2B1%%3D"$0"%%5E"41"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E123%%2D1%%3D"$0"%%5E"41"%%2D1%%0A"}'`
#msg=`seq 114 1000 | awk '{for(i=5;i<13;i+=6)if(110%i==0)printf$0"%%5E110%%2B1%%3D"$0"%%5E"110/i"%%2B1%%0A"}'`
#msg=`seq 119 1000 | awk '{printf$0"%%5E100%%2B1%%3D"$0"%%5E"20"%%2B1%%0A"}'`
#msg=`seq 159 1000 | awk '{printf$0"%%5E88%%2B1%%3D"$0"%%5E"8"%%2B1%%0A"}'`
#msg=`seq 716 1000 | awk '{for(i=3;i<17;i+=2)if(135%i==0)printf$0"%%5E135%%2B1%%3D"$0"%%5E"135/i"%%2B1%%0A"}'`
#msg=`seq 710 1000 | awk '{for(i=3;i<17;i+=2)if(135%i==0)printf$0"%%5E135%%2D1%%3D"$0"%%5E"135/i"%%2D1%%0A"}'`
#msg=`seq 644 1000 | awk '{for(i=3;i<11;i+=2)if(126%i==0)printf$0"%%5E126%%2B1%%3D"$0"%%5E"126/i"%%2B1%%0A"}'`
#msg=`seq 666 1000 | awk '{for(i=3;i<15;i+=2)if(117%i==0)printf$0"%%5E117%%2B1%%3D"$0"%%5E"117/i"%%2B1%%0A"}'`
#msg=`seq 662 1000 | awk '{for(i=3;i<15;i+=2)if(117%i==0)printf$0"%%5E117%%2D1%%3D"$0"%%5E"117/i"%%2D1%%0A"}'`
#msg=`seq 104 1000 | awk '{printf$0"%%5E114%%2B1%%3D"$0"%%5E"38"%%2B1%%0A"}'`
#msg=`seq 134 1000 | awk '{printf$0"%%5E111%%2B1%%3D"$0"%%5E"37"%%2B1%%0A"}'`
#msg=`seq 136 1000 | awk '{printf$0"%%5E111%%2D1%%3D"$0"%%5E"37"%%2D1%%0A"}'`
#msg=`seq 106 1000 | awk '{for(i=3;i<11;i+=6)if(108%i==0)printf$0"%%5E108%%2B1%%3D"$0"%%5E"108/i"%%2B1%%0A"}'`
#msg=`seq 139 1000 | awk '{printf$0"%%5E95%%2B1%%3D"$0"%%5E"19"%%2B1%%0A"}'`
#msg=`seq 138 1000 | awk '{printf$0"%%5E95%%2D1%%3D"$0"%%5E"19"%%2D1%%0A"}'`
#msg=`seq 155 1000 | awk '{printf$0"%%5E91%%2B1%%3D"$0"%%5E"13"%%2B1%%0A"}'`
#msg=`seq 173 1000 | awk '{printf$0"%%5E91%%2D1%%3D"$0"%%5E"13"%%2D1%%0A"}'`
#msg=`seq 516 1000 | awk '{for(i=3;i<17;i+=2)if(120%i==0)printf$0"%%5E120%%2B1%%3D"$0"%%5E"120/i"%%2B1%%0A"}'`
#msg=`seq 105 1000 | awk '{printf$0"%%5E102%%2B1%%3D"$0"%%5E"34"%%2B1%%0A"}'`
#msg=`seq 305 1000 | awk '{printf$0"%%5E96%%2B1%%3D"$0"%%5E"32"%%2B1%%0A"}'`
#msg=`seq 283 1000 | awk '{printf$0"%%5E85%%2B1%%3D"$0"%%5E"17"%%2B1%%0A"}'`
#msg=`seq 522 1000 | awk '{printf$0"%%5E85%%2D1%%3D"$0"%%5E"17"%%2D1%%0A"}'`
#msg=`seq 690 1000 | awk '{for(i=3;i<17;i+=2)if(99%i==0)printf$0"%%5E99%%2B1%%3D"$0"%%5E"99/i"%%2B1%%0A"}'`
#msg=`seq 600 1000 | awk '{for(i=3;i<17;i+=2)if(99%i==0)printf$0"%%5E99%%2D1%%3D"$0"%%5E"99/i"%%2D1%%0A"}'`
#msg=`seq 270 1000 | awk '{printf$0"%%5E93%%2B1%%3D"$0"%%5E"31"%%2B1%%0A"}'`
#msg=`seq 138 1000 | awk '{printf$0"%%5E93%%2D1%%3D"$0"%%5E"31"%%2D1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E77%%2B1%%3D"$0"%%5E"11"%%2B1%%0A"}'`
#msg=`seq 101 1000 | awk '{printf$0"%%5E77%%2D1%%3D"$0"%%5E"11"%%2D1%%0A"}'`
msg='report='$msg'&format=7'

len=`echo $msg | wc -c`
body=`cat <<EONU
POST /report.php HTTP/1.1
Host: factordb.com
Content-Type: application/x-www-form-urlencoded
Content-Length: $len

$msg
EONU`

echo "$body" | nc factordb.com 80

