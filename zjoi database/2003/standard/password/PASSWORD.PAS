var
  c: array [1..20000] of Integer;
  S: String;
  p, a, b: Integer;
function Lowbit(x: Integer): Integer;
begin
  Lowbit := x and (x xor (x - 1));
end;

function Str2Int(S: String): Integer;
var
  Result, Code: Integer;
begin
  Val(S, Result, Code);
  Str2Int := Result;
end;

procedure Add(p: Word);
var
  t: Word;
begin
  t := p;
  repeat
    C[p] := C[p] xor t;
    Inc(p, Lowbit(p));
  until p > 20000;
end;

function Calc(a, b: Integer): Integer;
var
  Result: Integer;
begin
  Result := 0;
  repeat
    if a < b then
    begin
      Result := Result xor C[b];
      Dec(b, Lowbit(b));
    end
    else begin
      Result := Result xor C[a];
      Dec(a, Lowbit(a));
    end;
  until a = b;
  Calc := Result;
end;

begin
  Assign(Input, 'password.in');
  Reset(Input);
  Assign(Output, 'password.out');
  Rewrite(Output);
  repeat
    Readln(S);
    if (S[1] = 'A') or (S[1] = 'R') then
    begin
      if S[1] = 'A' then p := 5
      else p := 8;
      p := Str2Int(Copy(S, p, Length(S) - p + 1));
      Add(p);
    end
    else begin
      p := Pos('AND', S) + 4;
      a := Str2Int(Copy(S, 13, p - 18));
      b := Str2Int(Copy(S, p, Length(S) - p + 1));
      if a > b then Writeln(0)
      else Writeln(Calc(a - 1, b));
    end;
  until Eof;
  Close(Input);
  Close(Output);
end.