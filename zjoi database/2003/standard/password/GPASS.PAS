const
  N = 10000;
type
  ArrType = array [1..20000] of Integer;
var
  Count: ArrType;
  i, j, k, l: LongInt;
begin
  FillChar(Count, Sizeof(ArrType), 0);
  Randomize;
  Assign(Output, 'password.in4');
  Rewrite(Output);
  for i := 1 to N do
  begin
    j := Random(3);
    case j of
      0: begin
           k := Random(20000) + 1;
           Writeln('ADD ', k);
           Inc(Count[k]);
         end;
      1: begin
           for l := 1 to 10 do
           begin
             k := Random(20000) + 1;
             if Count[k] > 0 then
             begin
               Writeln('REMOVE ', k);
               Dec(Count[k]);
               Break;
             end;
           end;
         end;
      else begin
           j := Random(20000) + 1;
           k := Random(20001 - j) + j;
           Writeln('XOR BETWEEN ', j, ' AND ', k);
         end;
    end;
  end;
  Close(Output);
end.