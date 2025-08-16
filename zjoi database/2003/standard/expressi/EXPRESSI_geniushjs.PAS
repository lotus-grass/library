var
a:array[1..200,1..200] of char;
tot,n,i,first,last,j,m,sum,k,i1,i2,j1,j2:longint;
ch:char;
s:string;

Function kong(x1,x2,y1,y2:integer):boolean;
var i,j:integer;
begin
 for i:=x1 to x2 do
  for  j:=y1 to y2 do
   if a[j,i]='@' then
    begin
      kong:=false;
      exit;
    end;
 kong:=true;
end;

Function sijiao(x1,x2,y1,y2:integer):integer;
var i:integer;
begin
 i:=0;
 if a[y1,x1]='@' then inc(i);
 if a[y2,x1]='@' then inc(i);
 if a[y1,x2]='@' then inc(i);
 if a[y2,x2]='@' then inc(i);
 sijiao:=i;
end;

Procedure sibian(x1,x2,y1,y2:integer; var s:string);
var i,j:integer;
begin
s:='';
 for i:=x1 to x2 do
  if a[y1,i]<>'@' then
   begin s:=s+'1'; break; end;
 if a[y1,i]='@' then s:=s+'0';

 for i:=x1 to x2 do
  if a[y2,i]<>'@' then
   begin s:=s+'1'; break; end;
 if a[y2,i]='@' then s:=s+'0';

j:=0;
 for i:=y1 to y2 do
  if (a[i,x1]<>'@') then
   if i=y1 then inc(j)
  else if a[i-1,x1]='@' then inc(j);
s:=s+chr(j+ord('0'));

j:=0;
 for i:=y1 to y2 do
  if (a[i,x2]<>'@') then
   if i=y1 then inc(j)
  else if a[i-1,x2]='@' then inc(j);
s:=s+chr(j+ord('0'));
end;

Function check(x1,x2,y1,y2:integer):integer;
var i,j:integer;
begin
 for i:=x1 to x2 do
  for j:=y1 to y2 do
  if a[j,i]<>'@' then
   begin
    check:=j;
    exit;
   end;
 check:=0;
end;

Function dong(x1,x2,y1,y2:integer):integer;
var i,j,k,last:integer;
begin
k:=0;
 for j:=y1 to y2 do
  begin
  for i:=x1 to x2 do
  if a[j,i]<>'@' then break;
   if (a[j,i]<>'@') then
    if j<>last+1 then begin inc(k); last:=j; end
    else last:=j;
  end;
dong:=k;
end;


begin
assign(input,'expressi.in9');
reset(input);
assign(output,'output.txt');
rewrite(output);
for i:=1 to 200 do
 for j:=1 to 200 do
  a[i,j]:=' ';
i:=0; m:=0;
 while not(eof) do
  begin
  inc(i); j:=0;
   while not(eoln) do
    begin
     read(ch);
     inc(j); if j>m then m:=j;
     if ch='@' then a[i,j]:=ch;
    end;
   readln;
  end;
n:=i;
tot:=1; sum:=0; k:=0;
while tot<=m do
 begin
  while kong(tot,tot,1,n)and(tot<=m) do inc(tot);
  i1:=tot; if tot>m then break;
  while not(kong(tot,tot,1,n))and(tot<=m) do inc(tot);
  i2:=tot-1;
  j1:=1;
  while kong(i1,i2,j1,j1) do inc(j1);
  j2:=n;
  while kong(i1,i2,j2,j2) do dec(j2);
  j:=sijiao(i1,i2,j1,j2);
  case j of
   0:begin
      sum:=sum+k;
      k:=0;
     end;
   3:begin
      first:=dong(i1,i2,j1,j2);
      if first=1 then k:=k*10+7
      else k:=k*10+4;
     end;
   4:begin
      sibian(i1,i2,j1,j2,s);
      if s='0020' then k:=k*10+3
      else if s='0001' then k:=k*10+6
      else if s='0010' then k:=k*10+9
      else if s='0011' then
       begin
        first:=check(i1,i1,j1,j2);
        last:=check(i2,i2,j1,j2);
        if first<last then k:=k*10+2
        else k:=k*10+5;
       end
      else
       begin
        first:=dong(i1,i2,j1,j2);
        case first of
         0:k:=k*10+1;
         1:k:=k*10;
         2:k:=k*10+8;
        end;
       end;
     end;
  end;
 end;
 writeln(sum+k);
 close(output);
end.