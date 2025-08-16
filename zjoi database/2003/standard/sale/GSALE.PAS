const
  N = 5;
  M = 10;
var
  i, j: Integer;
begin
  Randomize;
  Assign(Output, 'sale.int');
  Rewrite(Output);
  Writeln(N);
  for i := 1 to N do
  begin
    Writeln(1000000, ' ', 1000000);
    Writeln(M);
    for j := 1 to M - 1 do
      Write(LongInt(Random(100) + 1) * 10000, ' ');
    Writeln(LongInt(Random(100) + 1) * 10000);
  end;
  Close(Output);
end.