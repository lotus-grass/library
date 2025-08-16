const
  fout='trouble9.in';
  n=19999;
var
  i:longint;
begin
  randomize;
  assign(output, fout); rewrite(output);
  writeln(n);
  for i := 1 to n do
    writeln(random(1000)+90000);
  close(output);
end.
