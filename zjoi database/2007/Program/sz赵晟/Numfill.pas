const inf='numfill.in';
      ouf='numfill.out';

var n:longint;
    pos:array[1..1001] of longint;
    used:array[1..1001] of boolean;

procedure setup;
begin
     assign(input,inf);
     reset(input);
     assign(output,ouf);
     rewrite(output);
end;

procedure endit;
begin
     close(input);
     close(output);
end;

procedure init;
var i:longint;
begin
     readln(n);
     fillchar(used,sizeof(used),0);
     fillchar(pos,sizeof(pos),0);
end;

procedure check;
var i:longint;
begin
     fillchar(used,sizeof(used),0);
     for i:=1 to n-1 do
     if used[abs(pos[i]-pos[i+1])] then
        exit
     else
        used[abs(pos[i]-pos[i+1])]:=true;
     if used[abs(pos[1]-pos[n])] then
        exit;
     writeln('Yes');
     for i:=1 to n-1 do
       write(pos[i],' ');
     writeln(pos[n]);
     endit;
     halt;
end;

procedure work;
var i:longint;
begin
     if (n mod 4=1) or (n mod 4=2) then
     begin
          writeln('No');
          endit;
          halt;
     end;
     pos[1]:=1;
     if n mod 2=1 then pos[n]:=n+1;
     for i:=1 to n div 2 do
          pos[i*2-1]:=i;
     for i:=n downto n div 2+1 do
          pos[(n-i)*2+2]:=i;
     for i:=n downto n div 2+1 do
     begin
          check;
          inc(pos[(n-i)*2+2]);
     end;
     writeln('No');
     endit;
end;

begin
     setup;
       init;
       work;
end.
