const inf='chess.in';
      ouf='chess.out';
      maxn=2000;
var n,m:longint;
    ima,up:array[1..maxn,1..maxn] of longint;
    
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
var i,j:longint;
begin
     readln(n,m);
     for i:=1 to n do
       for j:=1 to m do
         read(ima[i][j]);
     fillchar(up,sizeof(up),0);
     for i:=1 to n do
         up[1][i]:=1;
     for i:=2 to n do
       for j:=1 to n do
       if ima[i-1][j]+ima[i][j]=1 then
          up[i][j]:=up[i-1][j]+1
                                  else
          up[i][j]:=1;
end;

function minx(a,b:longint):longint;
begin
     if a>b then exit(b) else exit(a);
end;

procedure work;
var maxa,maxq,t,i,j,t1,t2:longint;
begin
     maxa:=0;maxq:=0;
     for i:=1 to n do
     begin
          for j:=1 to n do
          begin
               t:=up[i][j];
               t1:=j-1;
               while (t1>0) and (up[i][t1]>=t) and (ima[i][t1]+ima[i][t1+1]=1) do dec(t1);
               inc(t1);
               t2:=j+1;
               while (t2<=n) and (up[i][t2]>=t) and (ima[i][t2]+ima[i][t2-1]=1) do inc(t2);
               if (t2-t1+1)*t>maxa then maxa:=(t2-t1+1)*t;
               if sqr(minx(t2-t1+1,t))>maxq then maxq:=sqr(minx(t2-t1+1,t));
          end;
     end;
     writeln(maxq);
     writeln(maxa);
end;

begin
     setup;
       init;
       work;
     endit;
end.