{
外部评测程序的例子
}
{$N+}

var
  inp, out, std, log: string;

procedure init; {初始化变量}
begin
  inp := paramStr(1); {标准输入文件，如input.txt}
  out := paramStr(2); {被测输出，如output.txt}
  std := paramStr(3); {标准输出，如output.001}
  log := paramStr(4); {把测试结果输出到log}
end;

procedure print(const d: double); {输出测试结果，测试结果是一个0到1之间的实数}
var
  f: text;
begin
  assign(f, log);
  rewrite(f);
  writeln(f, d : 0 : 2);
  close(f);
  halt;
end;

procedure accept; {1表示全对}
begin
  print(1);
end;

procedure wrongAnswer; {0表示全错}
begin
  print(0);
end;

function fileExists(const name: string): boolean; {判断文件是否存在}
var
  f: file;
begin
  {$I-}
  assign(f, name);
  fileMode := 0;
  reset(f);
  close(f);
  {$I+}
  fileExists := (ioResult = 0) and (name <> '');
end;

function same(const out, std: string): boolean; {一个简单的比较过程，比较out和std两个文件是否基本相同}
const
  maxn = 100;
var
  fx : text;
  realans, ans : real;
  n, i, s : longint;
  c, storecost : real;
  buy, demand : array[0 .. maxn] of longint;
  cost : array[0 .. maxn] of real;
begin
  assign(fx, std); reset(fx); read(fx, realans); close(fx);
  assign(fx, inp); reset(fx);
  readln(fx, n); readln(fx, s); readln(fx, storecost);
  for i := 1 to n do read(fx, cost[i]);
  readln(fx);
  for i := 1 to n do read(fx, demand[i]);
  close(fx);
  assign(fx, out); reset(fx);
  readln(fx, ans);
  for i := 1 to n do read(fx, buy[i]);
  close(fx);
  same := false;
  if abs(ans - realans) > 1e-4 then exit;
  c := 0;
  s := 0;
  for i := 1 to n do begin
    s := s + buy[i];
    c := c + buy[i] * cost[i];
    if s < demand[i] then exit;
    s := s - demand[i];
    c := c + s * storecost;
  end;
  same := abs(ans - c) < 1e-4;
end;

function check: boolean; {简单的检测函数}
begin
  check := false;
  if not fileExists(out) then
    exit;
  if not fileExists(std) then
    exit;
  if not same(out, std) then
    exit;
  check := true;
end;

begin
  init;
  if check then
    accept
  else
    wrongAnswer;
end.
