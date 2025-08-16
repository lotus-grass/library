const
  fin = 'trouble.in';
  fout = 'trouble.out';
  maxn = 20010;

var
  res, n : longint;
  a : array[0 .. maxn] of longint;

procedure getinfo;
var
  i : longint;
begin
  assign(input, fin); reset(input);
  readln(n);
  for i := 1 to n do readln(a[i]);
  a[0] := a[n];
  close(input);
  res := 0;
  for i := 0 to n - 1 do
    if a[i] + a[i + 1] > res then res := a[i] + a[i + 1];
end;

procedure print;
begin
  assign(output, fout); rewrite(output);
  writeln(res);
  close(output);
end;

function min(a, b : longint) : longint;
begin
  if a < b then min := a else min := b;
end;

function max(a, b : longint) : longint;
begin
  if a > b then max := a else max := b;
end;

function check(m : longint) : boolean;
var
  l, p, occupy, i : longint;
begin
  check := false;
  occupy := a[1];
  for i := 2 to n do begin
    l := m - a[i - 1];
    p := a[1] - occupy;
    if not odd(i) then
      occupy := min(p, a[i])
    else
      occupy := max(0, a[i] - l + p);
  end;
  check := occupy = 0;
end;

procedure main;
var
  m, l, r : longint;
begin
  l := res; r := res * 2;
  while l <= r do begin
    m := (l + r) shr 1;
    if check(m) then
      r := m - 1
    else l := m + 1;
  end;
  res := l;
end;

begin
  getinfo;
  if odd(n) then
    main;
  print;
end.
