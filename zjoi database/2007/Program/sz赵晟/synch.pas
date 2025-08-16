const inf='synch.in';
      ouf='synch.out';
      maxn=600000;

type uni=record
      be,en,l:longint;
         end;

var fa,ys:array[1..maxn] of longint;
    deadline,kk:array[1..maxn] of int64;
    a:array[1..2*maxn] of uni;
    n,s:longint;
    maxx,ans:int64;

procedure setup;
begin
     assign(input,inf);
     reset(input);
     assign(output,ouf);
     rewrite(output);
end;

procedure endit;
begin
     close(input);
     close(output);
end;

    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2].be;
         repeat
           while a[i].be<x do
            inc(i);
           while x<a[j].be do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i].be;
                a[i].be:=a[j].be;
                a[j].be:=y;
                y:=a[i].en;
                a[i].en:=a[j].en;
                a[j].en:=y;
                y:=a[i].l;
                a[i].l:=a[j].l;
                a[j].l:=y;
                y:=a[i].be;
                a[i].be:=a[j].be;
                a[j].be:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;

procedure build(x:longint);
var i:longint;
begin
     kk[x]:=10000000*10000000;
     for i:=ys[x] to ys[x+1]-1 do
     if a[i].en<>fa[x] then
     begin
          fa[a[i].en]:=x;
          deadline[a[i].en]:=deadline[x]+a[i].l;
          if deadline[a[i].en]>maxx then maxx:=deadline[a[i].en];
          build(a[i].en);
     end;
end;

procedure init;
var i,p:longint;
begin
     readln(n);
     readln(s);
     for i:=1 to n-1 do
     begin
          readln(a[i].be,a[i].en,a[i].l);
          a[i+n-1].be:=a[i].en;
          a[i+n-1].en:=a[i].be;
          a[i+n-1].l:=a[i].l;
     end;
     sort(1,2*n-2);
     p:=1;
     for i:=1 to n do
     begin
          ys[i]:=p;
          while (p<=2*n-2) and (a[p].be=i) do inc(p);
     end;
     ys[n+1]:=2*n-1;
     fa[s]:=0;
     deadline[s]:=0;
     maxx:=0;
     fillchar(kk,sizeof(kk),#100);
     build(s);
end;

function bt(x:longint):int64;
var i:longint;
    xx,t:int64;
begin
     if (ys[x]=ys[x+1]-1) and (x<>s) then
     begin
          exit(maxx-deadline[x]);
     end;
     ans:=0;xx:=maxlongint;
     for i:=ys[x] to ys[x+1]-1 do
     if (a[i].en<>fa[x]) then
     begin
          t:=bt(a[i].en);
          if t<xx then xx:=t;
          ans:=ans+t;
     end;
     ans:=ans-xx*(ys[x+1]-ys[x]);
     exit(xx);
end;

procedure work;
begin
     ans:=0;
     bt(s);
     writeln(ans);
end;

begin
     setup;
       init;
       work;
     endit;
end.