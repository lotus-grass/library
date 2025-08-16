var
 a1:array[1..120,0..120] of integer;
 c:array[1..120] of integer;
 used:array[1..120] of boolean;
 i,j,n,m,first,last:integer;
 find:boolean;
Procedure print(k:integer);
begin
 writeln(k);
 find:=true;
end;

Function bfs:boolean;
var i,j,open,close1:integer;
begin
 used[first]:=false;
 c[1]:=first;
 open:=1; close1:=1;
 while open<=close1  do
  begin
   for i:=1 to a1[c[open],0] do
    if (used[a1[c[open],i]]) then
     begin
      used[a1[c[open],i]]:=false;
      inc(close1); c[close1]:=a1[c[open],i];
      if a1[c[open],i]=last then
       begin
        bfs:=false;
        exit;
       end;
     end;
   inc(open);
  end;
 bfs:=true;
end;

Procedure cut(k:integer);
var i,j,l:integer;
begin
fillchar(used,sizeof(used),true);
used[k]:=false;
if bfs
 then
  begin
   print(k);
   exit;
  end;
end;

begin
while not seekeof do begin 
 readln(n);
 readln(i,j);
 find:=false;
 fillchar(a1,sizeof(a1),0);
 while i<>0 do
  begin
   inc(a1[i,0]); a1[i,a1[i,0]]:=j;
   inc(a1[j,0]); a1[j,a1[j,0]]:=i;
   readln(i,j);
  end;
 readln(first,last);
 if first<>last then for i:=1 to n do
  if (i<>last)and(i<>first)then begin cut(i); if find then break; end;
 if find=false then writeln('No solution');
end;
end.
