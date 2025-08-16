const inf='score.in';
      ouf='score.out';

var inp:string;
    n,p,ans:longint;
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
var i,t:longint;
begin
     readln(n);
     readln(inp);
     p:=1;ans:=0;
     for i:=1 to n do
     begin
          t:=0;
          while (p<=length(inp)) and (not((inp[p]<='9') and (inp[p]>='0'))) do inc(p);
          while (p<=length(inp)) and (inp[p]<='9') and (inp[p]>='0') do
          begin
               t:=t*10+ord(inp[p])-48;
               inc(p);
          end;
          inc(ans,t);
     end;
     writeln(ans);
end;

begin
     setup;
       work;
     endit;
end.