const maxn=2000;

var n,m,i,j,k,max1,max2,min:longint;
    a,b,f:array[1..maxn,1..maxn]of longint;

function minum(x,y:longint):longint;
begin
     if x>y then exit(y)
     else exit(x);
end;

begin
     assign(input,'chess.in');
     reset(input);
     assign(output,'chess.out');
     rewrite(output);
     readln(n,m);
     fillchar(b,sizeof(b),0);
     for i:=1 to n do
       for j:=1 to m do
       begin
         read(a[i,j]);
         if (i>1)and(a[i,j]<>a[i-1,j]) then b[i,j]:=b[i-1,j]+1
         else b[i,j]:=1;
         f[i,j]:=b[i,j]
       end;
     max1:=0;
     max2:=0;
     for i:=1 to n do
     begin
       for j:=1 to m do
       begin
         min:=b[i,j];
         for k:=j-1 downto 1 do
         if a[i,k]<>a[i,k+1] then
         begin
           if min>b[i,k] then min:=b[i,k];
           if min*(j-k+1)>f[i,j] then f[i,j]:=min*(j-k+1);
           if minum(min,j-k+1)>max2 then max2:=minum(min,j-k+1);
         end
         else break;
         if f[i,j]>max1 then max1:=f[i,j];
       end;
     end;
     writeln(max2*max2);
     writeln(max1);
     close(input);
     close(output);
end.
