const change:array[1..8,1..2] of -1..1 = ((-1,0),(1,0),(0,-1),(0,1),(1,1),(1,-1),(-1,-1),(-1,1));
type
 ss=array[1..8,1..8] of -1..1;
var
 a:ss;
 max,n,i,j,k,t:integer;
 s:string;
Function yes(k:integer):boolean;
begin
 if (k>=1)and(k<=8) then yes:=true else yes:=false;
end;
Function ok(x,y,chess:integer):boolean;
var
 i,j,k:integer;
 flag,gotin:boolean;
begin
 flag:=false;
 for k:=1 to 8 do
  begin
   i:=x+change[k,1];
   j:=y+change[k,2]; gotin:=false;
   while yes(i)and yes(j)and(a[i,j]=1-chess) do
    begin
     i:=i+change[k,1];
     j:=j+change[k,2];
     gotin:=true;
    end;
   if gotin then
   if yes(i)and yes(j) then
    if a[i,j]=chess then
     begin
     flag:=true;  a[x,y]:=chess;
      i:=x+change[k,1];
      j:=y+change[k,2];
      while yes(i)and yes(j)and(a[i,j]=1-chess) do
        begin
         a[i,j]:=chess;
         i:=i+change[k,1];
         j:=j+change[k,2];
        end;
     end;
  end;
 ok:=flag;
end;

Function cha:integer;
var i,j,k:integer;
begin
k:=0;
 for i:=1 to 8 do
  for j:=1 to 8 do
   if a[i,j]=0 then dec(k)
   else if a[i,j]=1 then inc(k);
cha:=k;
end;

Procedure get(k:integer);
var
 temp:ss;
 i,j,chess:integer;
 flag:boolean;
begin
if k=t+1 then
 begin
  i:=cha;
  if i>max then
   max:=i;
  exit;
 end;
 flag:=true; temp:=a; chess:=k mod 2;
 for i:=1 to 8 do
  for j:=1 to 8 do
  if a[i,j]=-1 then
  if ok(i,j,chess) then
   begin
    get(k+1);
    flag:=false;
    a:=temp;
   end;
 if flag then get(k+1);
end;

begin
assign(input,'input.txt');
reset(input);
assign(output,'output.txt');
rewrite(output);
 readln(n);
 for k:=1 to n do
  begin
   readln(t);
   fillchar(a,sizeof(a),byte(-1));
   for i:=1 to 8 do
    begin
     readln(s);
     for j:=1 to length(s) do
      if s[j]='B' then a[i,j]:=1 else
      if s[j]='W' then a[i,j]:=0;
    end;
   max:=-64;
   get(1);
   writeln(max);
  end;
end.