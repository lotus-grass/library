const
  dr: array[1..8] of Integer = (1, 1, 1, -1, -1, -1, 0, 0);
  dc: array[1..8] of Integer = (1, 0, -1, 1, 0, -1, 1, -1);

type
  Board = array[1..8, 1..8] of Byte;

var
  i, j, k, t, n: Integer;
  S: String;
  b: array[0..4] of Board;
  Temp, Max, Turn: Integer;

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

function Count(var b: Board): Integer;
var
  i, j, bc, wc: Integer;
begin
  bc := 0;
  wc := 0;
  for i := 1 to 8 do
    for j := 1 to 8 do
      if b[i, j] = 1 then Inc(bc)
      else if b[i, j] = 2 then Inc(wc);
  Count := bc - wc;
end;

procedure Search(Depth, Turn: Integer);
var
  Flag: Integer;
begin
  if Depth > t then
  begin
    Temp := Count(b[t]);
    if Temp > Max then
      Max := Temp;
    Exit;
  end;
  Flag := 0;
  for i := 1 to 8 do
    for j := 1 to 8 do
      if CanPut(i, j, Turn, b[Depth - 1]) then
      begin
        Flag := 1;
        b[Depth] := b[Depth - 1];
        Put(i, j, Turn, b[Depth]);
        if Turn = 1 then Search(Depth + 1, 2)
        else Search(Depth + 1, 1);
      end;
  if Flag = 0 then
  begin
    b[Depth] := b[Depth - 1];
    if Turn = 1 then Search(Depth + 1, 2)
    else Search(Depth + 1, 1);
  end;
end;

begin
  Assign(Input, 'bw.in');
  Reset(Input);
  Assign(Output, 'bw.out');
  Rewrite(Output);
  Readln(n);
  for k := 1 to n do
  begin
    Readln(t);
    for i := 1 to 8 do
    begin
      Readln(S);
      for j := 1 to 8 do
        case S[j] of
          ' ': b[0, i, j] := 0;
          'B': b[0, i, j] := 1;
          'W': b[0, i, j] := 2;
        end;
    end;
    Turn := 0;
    for i := 1 to 8 do
      for j := 1 to 8 do
        if b[0, i, j] > 0 then Inc(Turn);
    if Turn and 1 = 0 then Turn := 1
    else Turn := 2;
    Max := -10000;
    Search(1, Turn);
    Writeln(Max);
  end;
  Close(Input);
  Close(Output);
end.