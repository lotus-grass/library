const
 ch:array[2..9,1..4] of char=(('A','B','C',' '),('D','E','F',' '),
 ('G','H','I',' '),('J','K','L',' '),('M','N','O',' '),('P','Q','R','S'),
 ('T','U','V',' '),('W','X','Y','Z'));
 num:array[0..9]of integer=(0,0,3,3,3,3,3,4,3,4);
 fin='T9.in'; fou='t9.out';
var
 a:array[1..100] of string;
 b:array[1..100] of integer;
 ans:array[1..100] of string;
 s:string;
 i,n,tot,l:integer;

Procedure work1(k:integer);
var
 i,j:integer;
 flag:boolean;
begin
 for i:=1 to l do
  begin
   flag:=true;
    for j:=1 to num[b[i]] do
     if ch[b[i],j]=a[k][i] then
      begin
       flag:=false;
       break;
      end;
   if flag then exit;
  end;
 inc(tot);
 ans[tot]:=a[k];
end;

Procedure work2(k:integer);
var
 i,j,t:integer;
 flag:boolean;
begin
t:=0;
 for i:=1 to l do
  begin
   flag:=true;
    for j:=1 to num[b[i]] do
     if ch[b[i],j]=a[k][i] then
      begin
       flag:=false;
       break;
      end;
   if flag then inc(t);
   if t>1 then exit;
  end;
 if t=1 then
  begin
   inc(tot);
   ans[tot]:=a[k];
  end;
end;

Procedure print;
var i:integer;
begin
 for i:=1 to tot do
  writeln(ans[i]);
end;

Procedure sort;
var
 i,j:integer;
 s:string;
begin
 for i:=1 to tot-1 do
  for j:=i+1 to tot do
    if ans[i]>ans[j] then
     begin
      s:=ans[i];
      ans[i]:=ans[j];
      ans[j]:=s;
     end;
end;

begin
while not eof do
begin
 readln(n);
 for i:=1 to  n do readln(a[i]);
 readln(s);
  while s[length(s)]=' ' do delete(s,length(s),1);
  l:=length(s);
 for i:=1 to length(s) do b[i]:=ord(s[i])-ord('0');
 tot:=0;
 for i:=1 to n do if length(a[i])=l then work1(i);
 sort; print;
 tot:=0;
 for i:=1 to n do if length(a[i])>l then work1(i);
 sort; print;
 tot:=0;
 for i:=1 to n do if length(a[i])=l then work2(i);
 sort; print;
 tot:=0;
 for i:=1 to n do if length(a[i])>l then work2(i);
 sort; print;
end;
end.
