const
  dr: array[1..8] of Integer = (1, 1, 1, -1, -1, -1, 0, 0);
  dc: array[1..8] of Integer = (1, 0, -1, 1, 0, -1, 1, -1);
  N = 5;

type
  Board = array[1..8, 1..8] of Byte;
var
  i, j, k: Integer;
  b: Board;

function Valid(r, c: Integer): Boolean;
begin
  Valid := (r >= 1) and (r <= 8) and (c >= 1) and (c <= 8);
end;

function CanPut(r, c, color:Integer; var b: Board): Boolean;
var
  i, j, k, tr, tc: Integer;
begin
  if b[r, c] > 0 then
  begin
    CanPut := False;
    Exit;
  end;
  for i := 1 to 8 do
  begin
    k := 0;
    for j := 1 to 8 do
    begin
      tr := r + j * dr[i]; tc := c + j * dc[i];
      if not Valid(tr, tc) or (b[tr, tc] = 0) or (b[tr, tc] = color) then
      begin
        k := j;
        Break;
      end;
    end;
    tr := r + k * dr[i]; tc := c + k * dc[i];
    if (k > 1) and Valid(tr, tc) and (b[tr, tc] = color) then
    begin
      CanPut := True;
      Exit;
    end;
  end;
  CanPut := False;
end;

procedure Put(r, c, color: Integer; var b: Board);
var
  i, j, k, tr, tc: Integer;
begin
  for i := 1 to 8 do
  begin
    k := 0;
    for j := 1 to 8 do
    begin
      tr := r + j * dr[i]; tc := c + j * dc[i];
      if not Valid(tr, tc) or (b[tr, tc] = 0) or (b[tr, tc] = color) then
      begin
        k := j;
        Break;
      end;
    end;
    tr := r + k * dr[i]; tc := c + k * dc[i];
    if (k > 1) and Valid(tr, tc) and (b[tr, tc] = color) then
      for j := 1 to k - 1 do
        b[r + j * dr[i], c + j * dc[i]] := color;
  end;
  b[r, c] := color;
end;

procedure Generate(var b: Board);
var
  i, j, k, c: Integer;
  Buf: array[1..64, 1..2] of Integer;
  Len: Integer;
label Start;
begin
Start:
  FillChar(b, Sizeof(b), 0);
  b[4, 4] := 1;
  b[5, 5] := 1;
  b[4, 5] := 2;
  b[5, 4] := 2;
  for k := 1 to 1000 do
  begin
    c := k and 1;
    if c = 0 then c := 2;
    Len := 0;
    for i := 1 to 8 do
      for j := 1 to 8 do
        if CanPut(i, j, c, b) then
        begin
          Inc(Len);
          Buf[Len, 1] := i;
          Buf[Len, 2] := j;
        end;
    if Len = 0 then
    begin
      if k < 30 then Exit
      else Break;
    end;
    i := Random(Len) + 1;
    Put(Buf[i, 1], Buf[i, 2], c, b);
  end;
  goto Start;
end;

begin
  Randomize;
  Assign(Output, 'bw.in');
  Rewrite(Output);
  Writeln(N);
  for i := 1 to N do
  begin
    Writeln(Random(4) + 1);
    Generate(b);
    for j := 1 to 8 do
    begin
      for k := 1 to 8 do
        case b[j, k] of
          0: Write(' ');
          1: Write('B');
          2: Write('W');
        end;
      Writeln;
    end;
  end;
  Close(Output);
end.