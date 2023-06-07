require"io/console"
_=[[_]*4]*4
t=->{_=_.transpose}
r=->{_.map! &:reverse}
f=->{_=_.map{|_|_=(_*?\s).gsub(/\b(\d+) +\1\b/){|_|_.to_i*2}.split;_[3]||=p;_}}
f[]
loop{(0while _[i=rand(4)][j=rand(4)];_[i][j]=[*[?2]*9,?4].sample)if$n!=_*?_
system"clear"
_.map{|_|puts"%5s"*4%_}
(c=STDIN.getch)[?q]|0
$n=_*?_
c==?s&&t[]+r[]+f[]+r[]+t[]
c==?d&&r[]+f[]+r[]
c==?w&&t[]+f[]+t[]
c==?a&&f[]}