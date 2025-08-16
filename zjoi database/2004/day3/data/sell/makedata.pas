program makedata;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  n = 50;
  maxs = 100;
  filename = 'sell.in5';

var
  i : longint;

begin
  randomize;
  assign(output, filename); rewrite(output);
  writeln(n);
  writeln(maxs);
  writeln(random(100)/10:0:1);
  for i := 1 to n do
    write(random(100)/10:0:1, ' ');
  writeln;
  for i := 1 to n do
    write(random(maxs)*2+1,' ');
  writeln;
  close(output);
end.


