const
    maxn=1000000;
var
   n,s,l:longint;
   ans:int64;
   link:array[0..maxn,1..3] of longint;
   v:array[0..500000] of boolean;
   opt:array[0..500000] of int64;
   head:array[0..500000] of longint;
procedure setup;
begin
     assign(input,'synch.in');
     assign(output,'synch.out');
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
   i,a,b,t:longint;
begin
     fillchar(v,sizeof(v),false);
     readln(n);
     readln(s);
     l:=0;
     for i:=1 to n-1 do
      begin
           readln(a,b,t);
           inc(l);
           link[l,1]:=a;
           link[l,2]:=b;
           link[l,3]:=t;
           inc(l);
           link[l,1]:=b;
           link[l,2]:=a;
           link[l,3]:=t;
      end;
end;
procedure sort(l,r: longint);
      var
         i,j,x: longint;
         y:array[1..3] of longint;
      begin
         i:=l;
         j:=r;
         x:=link[(l+r) div 2,1];
         repeat
           while link[i,1]<x do
            inc(i);
           while x<link[j,1] do
            dec(j);
           if not(i>j) then
             begin
                y:=link[i];
                link[i]:=link[j];
                link[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
procedure prefix;
var
   i:longint;
begin
     link[0,1]:=0;
     for i:=1 to l do
     if link[i,1]<>link[i-1,1] then head[link[i,1]]:=i;
end;
function Dp(now:longint):longint;
var
   sum:int64;
   i:longint;
begin
     v[now]:=true;
     sum:=0;
     if head[now]<>0 then
  begin
     for i:=head[now] to l do
     if link[i,1]<>now then break
                       else
     if not(v[link[i,2]]) then
       begin
            if Dp(link[i,2])+link[i,3]>sum then sum:=link[i,3]+opt[link[i,3]];
       end;
  end
  else sum:=0;
  opt[link[now,1]]:=sum;
  Dp:=sum;
end;
procedure work(now:longint;last:int64);
var
   i:longint;
begin
     v[now]:=true;
     if head[now]<>0 then
      begin
         for i:=head[now] to l do
         if link[i,1]<>now then break
                          else if not(v[link[i,2]]) then
         begin
              inc(ans,opt[s]-last-opt[link[i,2]]-link[i,3]);
              work(link[i,2],opt[s]-opt[link[i,2]]);
         end;
      end;
end;
procedure print;
begin
    writeln(ans);
end;
begin
     setup;
     init;
     sort(1,l);
     prefix;
     v[s]:=true;
     Dp(s);
     fillchar(v,sizeof(v),false);
     v[s]:=true;
     work(s,0);
     print;
     closeit;
end.