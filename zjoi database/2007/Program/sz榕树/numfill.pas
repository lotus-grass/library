var n,i:longint;
    a:array[1..1000]of longint;

procedure work;
var i,j,k,m:longint;
begin
     m:=1;
     for i:=3 to n do
     if (i mod 4=0)or(i mod 4=3) then inc(m);
     a[1]:=1;
     a[2]:=m+1;
     if n mod 4=0 then k:=-1
     else k:=1;
     for i:=3 to n do
     begin
       a[i]:=a[i-1]+k;
       if k>0 then j:=-1
       else j:=1;
       k:=(abs(k)+1)*j;
       if abs(k)=m then k:=(abs(k)+1)*j;
     end;
end;

begin
     assign(input,'numfill.in');
     reset(input);
     assign(output,'numfill.out');
     rewrite(output);
     readln(n);
     if (n mod 4=1)or(n mod 4=2) then writeln('No')
     else
     begin
       work;
       writeln('Yes');
       for i:=1 to n-1 do write(a[i],' ');
       writeln(a[n]);
     end;
     close(input);
     close(output);
end.
