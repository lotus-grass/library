const
     maxn=1000;
var
   n,m,ans,k:longint;
   a,now:array[1..maxn] of longint;
   link:array[1..maxn,1..2] of longint;
procedure setup;
begin
     assign(input,'winner.in');
     assign(output,'winner.out');
     reset(input);
     rewrite(output);
end;
procedure closeit;
begin
     close(input);
     close(output);
end;
procedure init;
var
   i,a1,a2:longint;
begin
     readln(n,m);
     for i:=1 to n do read(a[i]);
     for i:=1 to m do
     begin
        readln(a1,a2);
        link[i,1]:=a1;
        link[i,2]:=a2;
     end;
end;
procedure work;
var
   i,ans1,ans2:longint;
begin
     ans1:=0;ans2:=0;
     for i:=1 to n do now[i]:=0;
     for i:=1 to n do if now[i]+a[i]=1 then inc(ans1);
     for i:=1 to m do
      if now[link[i,1]]+now[link[i,2]]=1 then inc(ans1);
     for i:=1 to n do now[i]:=1;
     for i:=1 to n do if now[i]+a[i]=1 then inc(ans2);
     for i:=1 to m do
      if now[link[i,1]]+now[link[i,2]]=1 then inc(ans2);
     if ans1>ans2 then ans:=ans2
                  else ans:=ans1;
     ans2:=0;
     for k:=1 to 500000 div m do
     begin
       ans2:=0;
       for i:=1 to n do now[i]:=random(2);
     for i:=1 to n do if now[i]+a[i]=1 then inc(ans2);
     for i:=1 to m do
      if now[link[i,1]]+now[link[i,2]]=1 then inc(ans2);
      if ans2<ans then ans:=ans2;
     end;
     writeln(ans);
end;
begin
     setup;
     init;
     work;
     closeit;
end.