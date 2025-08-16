const maxn=1200;
var n,i:longint;
    a:array[1..maxn]of longint;
    point:array[1..2]of longint;
begin
assign(input,'numfill.in');
assign(output,'numfill.out');
reset(input);
rewrite(output);
  readln(n);
  if (n mod 4=1) or (n mod 4=2) then writeln('No') else
    begin
      writeln('Yes');
      point[1]:=1;
      point[2]:=n;
      fillchar(a,sizeof(a),0);
      for i:=1 to n div 2 do
        if i mod 2=1 then
          begin
            a[i]:=point[1];
            inc(point[1]);
          end else
          begin
            a[i]:=point[2];
            dec(point[2]);
          end;
      for i:=n div 2+1 to n-1 do
        if i mod 2=0 then
          begin
            a[i]:=point[1];
            inc(point[1]);
          end else
          begin
            a[i]:=point[2];
            dec(point[2]);
          end;
      a[n]:=n+1;
      for i:=1 to n do
        begin
          if i<>1 then write(' ');
          write(a[i],' ');
        end;
      writeln;
    end;
  close(input);
  close(output);
end.