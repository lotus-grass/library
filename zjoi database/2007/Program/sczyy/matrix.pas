const maxn=200;
var i,j,k,n,test,tests:longint;
    g:array[1..maxn,1..maxn]of boolean;
function judge:boolean;
var t1,t2:longint;
begin
  for t1:=1 to n do
    begin
      for t2:=1 to n do
        if g[t1,t2] then break;
      if not g[t1,t2] then exit(false);
      for t2:=1 to n do
        if g[t2,t1] then break;
      if not g[t2,t1] then exit(false);
    end;
  exit(true);
end;
begin
  assign(input,'matrix.in');
  reset(input);
  assign(output,'matrix.out');
  rewrite(output);
  readln(tests);
  for test:=1 to tests do
    begin
      readln(n);
      for i:=1 to n do
        for j:=1 to n do
          begin
            read(k);
            g[i,j]:=k=1;
          end;
      if judge then writeln('Yes') else writeln('No');
    end;
  close(input);
  close(output);
end.