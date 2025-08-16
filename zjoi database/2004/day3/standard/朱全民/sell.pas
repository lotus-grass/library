program sell;

const
  fin = 'sell.in';
  fout = 'sell.out';
  maxn = 55;
  maxs = 105;
  maxvalue = 300005;

var
  n, capacity : longint;
  storecost : real;
  demand : array[0 .. maxn] of longint;
  cost : array[0 .. maxn] of real;
  s : array[0 .. maxn, 0 .. maxs] of longint;
  f : array[0 .. maxn, 0 .. maxs] of real;

procedure getinfo;
var
  i, j : longint;
begin
  assign(input, fin); reset(input);
  readln(n); readln(capacity); readln(storecost);
  for i := 1 to n do
    read(cost[i]);
  readln;
  for i := 1 to n do
    read(demand[i]);
  close(input);
  for i := 0 to n do
    for j := 0 to capacity do f[i, j] := maxvalue;
  f[0, 0] := 0;
end;

procedure main;
var
  i, howmuch, buy, more : longint;
  v : real;
begin
  for i := 0 to n - 1 do
    for howmuch := 0 to capacity do if f[i, howmuch] <> maxvalue then
      for buy := 0 to capacity + demand[i + 1] - howmuch do begin
        more := howmuch + buy - demand[i + 1];
        if more < 0 then continue;
        v := f[i, howmuch] + howmuch * storecost + buy * cost[i + 1];
        if v < f[i + 1, more] then begin
          f[i + 1, more] := v;
          s[i + 1, more] := buy;
        end;
      end;
end;

procedure show(n : longint; remain : longint);
begin
  if n = 0 then exit;
  show(n - 1, demand[n] + remain - s[n, remain]); 
  write(s[n, remain], ' ');
end;

procedure print;
begin
  assign(output, fout); rewrite(output);
  writeln(f[n, 0] : 0 : 1);
  show(n, 0);
  writeln;
  close(output);
end;

begin
  getinfo;
  main;
  print;
end.







