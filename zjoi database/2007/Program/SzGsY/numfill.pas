var
   n,j:longint;
   a,b:array[-1000..1000] of longint;
procedure setup;
begin
     assign(input,'numfill.in');
     assign(output,'numfill.out');
     reset(input);
     rewrite(output);
end;
procedure closeit;
begin
     close(input);
     close(output);
end;
procedure work;
var
   i,left,right:longint;
begin
     a[1]:=1;
     a[n]:=n-1;
     left:=1;
     right:=n;
     for i:=1 to (n mod 4+(n div 4-1)*2-1) do
     if odd(i) then
      begin
           inc(left);
           a[left]:=n-i-1;
      end
      else
      begin
           dec(right);
           a[right]:=n-i-1;
      end;
    inc(left);
    a[left]:=n;
    i:=n-(i+3);
    if n mod 4=0 then
     begin
          left:=2;
          right:=1;
          for  j:=1 to i div 2 do
           begin
                dec(left);
                inc(right);
                b[left]:=j*2;
                b[right]:=b[left]+1;
           end;
     end
     else
     begin
          left:=2;
          right:=1;
          for j:=1 to i div 2 do
          begin
               dec(left);
               inc(right);
               b[right]:=j*2;
               b[left]:=b[right]+1;
          end;
     end;
     for i:=1 to n do
     if a[i]=0 then
     begin
         for j:=left to right do a[i+j-left]:=b[j];
         break;
     end;
     for i:=1 to n do b[a[i]]:=i;
     for i:=1 to n-2 do write(b[i],' ');
     writeln(b[n-1]);
end;
begin
     setup;
     readln(n);
     n:=n+1;
     if (n mod 4=2)or(n mod 4=3) then
     begin
        writeln('No');
        closeit;
        halt;
     end;
     writeln('Yes');
     if n=4 then
      begin
        writeln('1 3 4');
        closeit;
        halt;
      end;
     if n=5 then
       begin
         writeln('1 4 3 5');
         closeit;
         halt;
       end;
     work;
     closeit;
end.
