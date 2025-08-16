const maxn=100;
      q:array[1..4]of char=('y','r','g','b');

var a:array[1..100,1..4]of longint;
    sum:longint;

procedure p1;
var i,j,k,n:longint;
    ch:char;
begin
     fillchar(a,sizeof(a),0);
     readln(n);
     for k:=1 to n do
     begin
       i:=0;
       repeat read(ch); until ch<>' ';
       while ch in['0'..'9'] do
       begin
         i:=i*10+ord(ch)-48;
         read(ch);
       end;
       for j:=1 to 4 do if q[j]=ch then break;
       inc(a[i,j]);
     end;
end;

procedure p2;
var i,j,k,l:longint;
begin
     sum:=0;
     for k:=maxn downto 1 do
     begin
       repeat
         j:=0;
         for i:=1 to 4 do
           if a[k,i]>0 then inc(j);
         if j>2 then
         for i:=1 to 4 do
           if a[k,i]>0 then
           begin
             dec(a[k,i]);
             inc(sum,k);
           end;
       until j<3;
       if k>2 then
       for j:=1 to 4 do
       repeat
         l:=k;
         while (l>0)and(a[l,j]>0) do dec(l);
         inc(l);
         if k-l>1 then
         for i:=l to k do
         begin
           inc(sum,i);
           dec(a[i,j]);
         end;
       until k-l<2;
     end;
end;

begin
     assign(input,'score.in');
     reset(input);
     assign(output,'score.out');
     rewrite(output);
     p1;
     p2;
     writeln(sum);
     close(input);
     close(output);
end.
