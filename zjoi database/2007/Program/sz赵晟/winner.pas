const inf='winner.in';
      ouf='winner.out';

var n,k:longint;

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

procedure work;
var t,i:longint;
begin
     readln(n);     k:=0;
     for i:=1 to n do
     begin
           read(t);
           inc(k,t);
     end;
     if k>n div 2 then writeln(n-k)
                  else writeln(k);
end;

begin
     setup;
       work;
     endit;
end.
