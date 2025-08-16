const maxn=500000;

type ptype=^ttt;
     ttt=record
           da,dis:longint;
           next:ptype;
         end;

var n,s:longint;
    a,b:array[1..maxn]of ptype;
    f:array[1..maxn,1..2]of longint;

procedure prepare;
var i,j,k,l:longint;
    p:ptype;
begin
     readln(n);
     readln(s);
     for i:=1 to n do
     begin
       new(p);
       p^.next:=nil;
       a[i]:=p;
       b[i]:=p;
     end;
     for k:=1 to n-1 do
     begin
       readln(i,j,l);
       new(p);
       p^.da:=j;
       p^.dis:=l;
       p^.next:=nil;
       b[i]^.next:=p;
       b[i]:=p;
       new(p);
       p^.da:=i;
       p^.dis:=l;
       p^.next:=nil;
       b[j]^.next:=p;
       b[j]:=p;
     end;
end;

procedure dfs(father,t:longint);
begin
     b[t]:=a[t]^.next;
     while b[t]<>nil do
     begin
       if b[t]^.da<>father then
       begin
         dfs(t,b[t]^.da);
         if f[b[t]^.da,2]+b[t]^.dis>f[t,2] then f[t,2]:=f[b[t]^.da,2]+b[t]^.dis;
         f[t,1]:=f[t,1]+f[b[t]^.da,1];
       end;
       b[t]:=b[t]^.next;
     end;
     b[t]:=a[t]^.next;
     while b[t]<>nil do
     begin
       if b[t]^.da<>father then
         f[t,1]:=f[t,1]+f[t,2]-f[b[t]^.da,2]-b[t]^.dis;
       b[t]:=b[t]^.next;
     end;
end;


begin
     assign(input,'synch.in');
     reset(input);
     assign(output,'synch.out');
     rewrite(output);
     prepare;
     fillchar(f,sizeof(f),0);
     dfs(0,s);
     writeln(f[s,1]);
     close(input);
     close(output);
end.